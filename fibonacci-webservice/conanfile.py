from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
import subprocess

class fibonacci_webserviceRecipe(ConanFile):
    def get_version_from_script(self):
        script_path = f"{self.recipe_folder}/get-version.sh"
        result = subprocess.run(
            ["bash", str(script_path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        
        if result.returncode != 0:
            raise RuntimeError(f"get-version.sh failed with exit code {result.returncode}: {result.stderr.strip()}")
        
        version = result.stdout.strip()
        if not version:
            raise RuntimeError("get-version.sh did not return a version string.")
        
        return version

    name = "fibonacci-webservice"

    @property
    def version(self):
        return self.get_version_from_script()

    package_type = "application"

    license = "MIT"
    author = "Blauwe Lucht sebastiaan@blauwe-lucht.nl"
    url = "https://github.com/blauwe-lucht/gitlab-nexus-cpp-conan-cmake-containers-demo"
    description = "Webservice to calculate Fibonacci numbers"
    topics = ("fibonacci", "webservice", "demo")

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self):
        self.requires("oatpp/1.3.0")
        self.requires("oatpp-swagger/1.3.0")
        self.requires("nlohmann_json/3.12.0")
        self.requires("fibonacci/1.0.2")

    def build_requirements(self):
        self.test_requires("gtest/1.14.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.preprocessor_definitions["__APP_VERSION__"] = f'"{self.version}"'
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

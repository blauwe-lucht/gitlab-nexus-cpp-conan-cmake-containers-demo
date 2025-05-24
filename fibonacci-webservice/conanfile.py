from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class fibonacci_webserviceRecipe(ConanFile):
    name = "fibonacci-webservice"
    version = "1.0.0"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "Blauwe Lucht sebastiaan@blauwe-lucht.nl"
    url = "https://github.com/blauwe-lucht/gitlab-nexus-cpp-conan-cmake-containers-demo"
    description = "Webservice to calculate Fibonacci numbers"
    topics = ("fibonacci", "webservice", "demo")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def requirements(self):
        self.requires("oatpp/1.3.0")
        self.requires("oatpp-swagger/1.3.0")
        self.requires("nlohmann_json/3.12.0")
        self.requires("fibonacci/1.0.1")

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

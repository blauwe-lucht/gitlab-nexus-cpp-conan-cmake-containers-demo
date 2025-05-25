from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class fibonacciRecipe(ConanFile):
    name = "fibonacci"
    version = "1.0.2"
    package_type = "library"

    # Optional metadata
    license = "MIT"
    author = "Blauwe Lucht sebastiaan@blauwe-lucht.nl"
    url = "https://github.com/blauwe-lucht/gitlab-nexus-cpp-conan-cmake-containers-demo"
    description = "Library to calculate Fibonacci numbers"
    topics = ("fibonacci", "library", "demo")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "test/*"

    def build_requirements(self):
        self.requires("gtest/1.14.0")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)
    
    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["fibonacci"]

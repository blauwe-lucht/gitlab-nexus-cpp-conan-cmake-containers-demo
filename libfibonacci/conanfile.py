from conan import ConanFile
from conan.tools.cmake import CMake

class LibFibonacciConan(ConanFile):
    name = "libfibonacci"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "src/*"
    generators = "CMakeToolchain", "CMakeDeps"
    test_requires = "gtest/1.14.0"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["libfibonacci"]

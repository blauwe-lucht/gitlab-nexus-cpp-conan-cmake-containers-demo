import os
from conan import ConanFile
from conan.tools.build import can_run


class fibonacci_webserviceTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires(self.tested_reference_str)

    def test(self):
        if can_run(self):
            self.run("fibonacci-webservice", env="conanrun")

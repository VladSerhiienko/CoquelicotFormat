from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy
import os

class CoquelicotFormat(ConanFile):
    name = "coquelicot_format"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "AutotoolsToolchain", "PkgConfigDeps", "XcodeDeps"

    exports_sources = "include/*", "CMakeLists.txt"
    no_copy_source = True

    def build_requirements(self):
        self.tool_requires("cmake/4.1.2")

    def layout(self):
        cmake_layout(self)

    def package(self):
        copy(self, "*.hpp", src=self.source_folder + "/include", dst=self.package_folder + "/include")
        copy(self, "*.h", src=self.source_folder + "/include", dst=self.package_folder + "/include")

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs = ["include"]


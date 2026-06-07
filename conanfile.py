from conan import ConanFile
from conan.tools.files import copy
import os

class CoquelicotFormat(ConanFile):
    name = "coquelicot_format"
    version = "1.0"
    package_type = "header-library"
    revision_mode = "hash"

    exports_sources = "include/*", "CMakeLists.txt", "LICENSE"
    no_copy_source = True

    def layout(self):
        self.folders.source = "."
        self.cpp.source.includedirs = ["include"]
        self.cpp.source.libdirs = []
        self.cpp.source.bindirs = []
        self.cpp.package.includedirs = ["include"]
        self.cpp.package.libdirs = []
        self.cpp.package.bindirs = []

    def package_id(self):
        self.info.clear()

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, "*.hpp", src=os.path.join(self.source_folder, "include"), dst=os.path.join(self.package_folder, "include"))
        copy(self, "*.h", src=os.path.join(self.source_folder, "include"), dst=os.path.join(self.package_folder, "include"))

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "coquelicot_format")
        self.cpp_info.set_property("cmake_target_name", "coquelicot_format::coquelicot_format")
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.includedirs = ["include"]

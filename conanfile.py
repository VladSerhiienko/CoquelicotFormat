from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class CoquelicotFormat(ConanFile):
    name = "coquelicot_format"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "AutotoolsToolchain", "PkgConfigDeps", "XcodeDeps"

    # https://docs.conan.io/2/tutorial/creating_packages/other_types_of_packages/header_only_packages.html
    # No settings/options are necessary, this is header only
    exports_sources = "include/*"
    # We can avoid copying the sources to the build folder in the cache
    no_copy_source = True
    
    def package(self):
        # This will also copy the "include" folder
        copy(self, "*.h", self.source_folder, self.package_folder)

    def package_info(self):
        # For header-only packages, libdirs and bindirs are not used
        # so it's necessary to set those as empty.
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
    
    def build_requirements(self):
        self.tool_requires("cmake/4.0.1")

    ''' https://github.com/conan-io/examples2/blob/main/tutorial/consuming_packages/conanfile_py/complete_conanfile.py '''
    def layout(self):
        cmake_layout(self)


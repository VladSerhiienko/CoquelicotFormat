from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class CoquelicotFormatTest(ConanFile):
    name = "coquelicot_format_test"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "AutotoolsToolchain", "PkgConfigDeps", "XcodeDeps"

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("catch2/3.8.1")

    def build_requirements(self):
        self.tool_requires("cmake/4.1.2")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake = CMake(self)
            # This will run the tests built with Catch2
            cmake.test()

    ''' https://github.com/conan-io/examples2/blob/main/tutorial/consuming_packages/conanfile_py/complete_conanfile.py '''
    def layout(self):
        cmake_layout(self)


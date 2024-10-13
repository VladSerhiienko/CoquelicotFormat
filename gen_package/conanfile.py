from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class CoquelicotFormatGen(ConanFile):
    name = "coquelicot_format_gen"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "AutotoolsToolchain", "PkgConfigDeps", "XcodeToolchain", "XcodeDeps"

    def build_requirements(self):
        self.tool_requires("cmake/3.29.3")
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    ''' https://github.com/conan-io/examples2/blob/main/tutorial/consuming_packages/conanfile_py/complete_conanfile.py '''
    def layout(self):
        cmake_layout(self)

import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class CoquelicotFormatTest(ConanFile):
    name = "coquelicot_format_test"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "AutotoolsToolchain", "PkgConfigDeps", "XcodeDeps"

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("catch2/3.4.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.29.3")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            cmake = CMake(self)
            cmake.test()  # This will run the tests built with Catch2

    ''' https://github.com/conan-io/examples2/blob/main/tutorial/consuming_packages/conanfile_py/complete_conanfile.py '''
    def layout(self):
        cmake_layout(self)

        if self.settings.os == "Windows":
            multi = True if self.settings.get_safe("compiler") == "msvc" else False
            if multi:
                self.folders.generators = "build_msvc_amd64"
                self.folders.build = "build_msvc_amd64"
            else:
                self.folders.generators = os.path.join("build_msvc_amd64", str(self.settings.build_type))
                self.folders.build = os.path.join("build_msvc_amd64", str(self.settings.build_type))

        elif self.settings.os == "Android":
            build_dir = "_".join(["build_android", str(self.settings.arch)])
            self.folders.generators = build_dir
            self.folders.build = build_dir

        elif self.settings.os == "Linux":
            build_dir = "_".join(["build_linux", str(self.settings.arch)])
            self.folders.generators = build_dir
            self.folders.build = build_dir

        elif self.settings.os == "iOS":
            build_dir = "_".join(["build_xcode_ios", str(self.settings.os.sdk), str(self.settings.arch)])
            self.folders.generators = build_dir
            self.folders.build = build_dir

        elif self.settings.os == "Macos":
            build_dir = "_".join(["build_xcode_macos", str(self.settings.arch)])
            self.folders.generators = build_dir
            self.folders.build = build_dir

        elif self.settings.os == "Emscripten":
            build_dir = "build_emscripten"
            self.folders.generators = build_dir
            self.folders.build = build_dir


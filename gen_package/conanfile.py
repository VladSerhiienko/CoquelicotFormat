import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout

class CoquelicotFormatGen(ConanFile):
    name = "CoquelicotFormatGen"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps", "AutotoolsToolchain", "PkgConfigDeps", "XcodeDeps"

    def build_requirements(self):
        self.tool_requires("cmake/3.29.3")
    
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


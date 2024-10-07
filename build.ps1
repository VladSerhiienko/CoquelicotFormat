
New-Item -ItemType Directory -Force -Path "build_msvc_amd64"
Set-Location -Path "build_msvc_amd64"

conan install .. --build=missing --profile:host=../profiles/msvc_amd64 --profile:build=../profiles/msvc_amd64 -s build_type=Debug
conan install .. --build=missing --profile:host=../profiles/msvc_amd64 --profile:build=../profiles/msvc_amd64 -s build_type=Release
conan create .. --build=missing --profile:host=../profiles/msvc_amd64 --profile:build=../profiles/msvc_amd64 -s build_type=Debug

cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"

Set-Location -Path ".."

conan install . --build=missing --profile:host=profiles/msvc_amd64 --profile:build=profiles/msvc_amd64 -s build_type=Debug
conan install . --build=missing --profile:host=profiles/msvc_amd64 --profile:build=profiles/msvc_amd64 -s build_type=Release
conan build . --build=missing --profile:host=profiles/msvc_amd64 --profile:build=profiles/msvc_amd64 -s build_type=Debug
conan build . --build=missing --profile:host=profiles/msvc_amd64 --profile:build=profiles/msvc_amd64 -s build_type=Release
conan create . --build=missing --profile:host=profiles/msvc_amd64 --profile:build=profiles/msvc_amd64 -s build_type=Debug
conan create . --build=missing --profile:host=profiles/msvc_amd64 --profile:build=profiles/msvc_amd64 -s build_type=Release

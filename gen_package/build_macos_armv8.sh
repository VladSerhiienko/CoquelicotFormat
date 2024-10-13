
conan install . --build=missing --profile:host=../profiles/macos_armv8 --profile:build=../profiles/macos_armv8 -s build_type=Debug
conan install . --build=missing --profile:host=../profiles/macos_armv8 --profile:build=../profiles/macos_armv8 -s build_type=Release
conan build . --build=missing --profile:host=../profiles/macos_armv8 --profile:build=../profiles/macos_armv8 -s build_type=Debug
conan build . --build=missing --profile:host=../profiles/macos_armv8 --profile:build=../profiles/macos_armv8 -s build_type=Release

./build/Release/CoquelicotFormatGen

for file in coquelicot_format*.h; do
    if [ -f "$file" ]; then
        cp "$file" ../include/coquelicot/
    else
        break
    fi
done


conan install . --build=missing --profile:host=../profiles/msvc_amd64 --profile:build=../profiles/msvc_amd64 -s build_type=Debug
conan install . --build=missing --profile:host=../profiles/msvc_amd64 --profile:build=../profiles/msvc_amd64 -s build_type=Release
conan build . --build=missing --profile:host=../profiles/msvc_amd64 --profile:build=../profiles/msvc_amd64 -s build_type=Debug
conan build . --build=missing --profile:host=../profiles/msvc_amd64 --profile:build=../profiles/msvc_amd64 -s build_type=Release

./build/Release/CoquelicotFormatGen.exe

$currentDir = Get-Location
$includeDir = Join-Path -Path $currentDir -ChildPath "../include/coquelicot"

Write-Output $currentDir
Write-Output $includeDir

# Find all files that match the pattern "format*.h" in the current directory
Get-ChildItem -Path $currentDir -Filter "tinyimageformat*.h" | ForEach-Object {
    Write-Output $_.FullName
    Copy-Item -Path $_.FullName -Destination $includeDir -Force
}
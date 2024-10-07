cmake_minimum_required(VERSION 3.22.1)

project(CoquelicotFormatTest LANGUAGES C CXX)

# Include Conan-generated files for dependencies
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Catch2 REQUIRED)
find_package(coquelicot_format REQUIRED)

file(GLOB_RECURSE CoquelicotFormatTestSrc src/*)
add_executable(CoquelicotFormatTest ${CoquelicotFormatTestSrc})
target_include_directories(CoquelicotFormatTest PUBLIC src)
target_link_libraries(CoquelicotFormatTest Catch2::Catch2WithMain coquelicot_format::coquelicot_format)

# Enable testing (CTest)
enable_testing()
include(CTest)
include(Catch)
catch_discover_tests(CoquelicotFormatTest)

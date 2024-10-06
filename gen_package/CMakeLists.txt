cmake_minimum_required(VERSION 3.22.1)

project(CoquelicotFormatGen LANGUAGES C CXX)

set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CoquelicotImageGenSrc src/*)
add_executable(CoquelicotFormatGen ${CoquelicotImageGenSrc})
target_include_directories(CoquelicotFormatGen PUBLIC src)

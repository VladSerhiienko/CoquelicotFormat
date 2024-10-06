cmake_minimum_required(VERSION 3.22.1)

project(CoquelicotFormat LANGUAGES C CXX)

set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CoquelicotImageSrc src/*)
file(GLOB_RECURSE CoquelicotImageInc include/*)
add_library(CoquelicotFormat STATIC ${CoquelicotImageSrc} ${CoquelicotImageInc})
target_include_directories(CoquelicotFormat PUBLIC include src)

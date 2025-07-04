cmake_minimum_required(VERSION 3.22.1)

project(CoquelicotFormat LANGUAGES C CXX)

# Enable C++17 standard
set(CMAKE_CXX_STANDARD 17)

add_library(coquelicot_format INTERFACE)
target_include_directories(coquelicot_format INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(coquelicot_format INTERFACE cxx_std_17)

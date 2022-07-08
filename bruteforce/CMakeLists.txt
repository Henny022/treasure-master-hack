cmake_minimum_required(VERSION 3.21)
project(bruteforce)

add_library(project_settings INTERFACE)
target_compile_options(project_settings INTERFACE -march=native)
target_compile_features(project_settings INTERFACE cxx_std_11)

add_subdirectory(common)
add_subdirectory(tm_8_test)
add_subdirectory(tm_avx2_test)
add_subdirectory(tm_avx512_test)

add_executable(tm_avx512_test main.cpp tm_avx512.cpp tm_avx512_test.cpp)
target_include_directories(tm_avx512_test PRIVATE .)
target_link_libraries(tm_avx512_test project_settings common)

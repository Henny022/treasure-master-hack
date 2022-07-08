add_executable(tm_avx2_test main.cpp tm_avx2.cpp tm_avx2_test.cpp)
target_include_directories(tm_avx2_test PRIVATE .)
target_link_libraries(tm_avx2_test project_settings common)

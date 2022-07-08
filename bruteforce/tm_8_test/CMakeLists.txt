add_executable(tm_8_test main.cpp tm_8.cpp tm_8_test.cpp)
target_include_directories(tm_8_test PRIVATE .)
target_link_libraries(tm_8_test project_settings common)

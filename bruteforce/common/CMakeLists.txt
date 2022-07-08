add_library(common STATIC rng.cpp)
target_include_directories(common PUBLIC .)
target_link_libraries(common PUBLIC project_settings)

add_executable(tm_mpi main.cpp)
target_include_directories(tm_mpi PRIVATE .)
target_link_libraries(tm_mpi project_settings)

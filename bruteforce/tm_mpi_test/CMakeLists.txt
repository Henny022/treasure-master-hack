add_executable(tm_mpi_test main.cpp tm_mpi.cpp tm_mpi_test.cpp)
target_include_directories(tm_mpi_test PRIVATE .)
target_link_libraries(tm_mpi_test project_settings)

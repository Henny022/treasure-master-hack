#ifndef BRUTEFORCE_TM_MPI_TEST_H
#define BRUTEFORCE_TM_MPI_TEST_H
#include <cstdint>
#include "../tm_mpi/rng.h"

class tm_mpi_test
{
  public:
    tm_mpi_test();

    void process_test_case(uint8_t *test_case, uint16_t *rng_seed,
                           int algorithm);
    void run_iterations(uint8_t *test_case, uint16_t *rng_seed, int algorithm,
                        int iterations);

    uint16_t rng_seed;

    rng_tables_t *rng_tables;
};

#endif // BRUTEFORCE_TM_MPI_TEST_H

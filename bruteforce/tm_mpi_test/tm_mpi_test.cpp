#include "tm_mpi_test.h"
#include <cstdint>
#include "tm_mpi.h"

tm_mpi_test::tm_mpi_test()
{
    this->rng_tables = generate_rng_tables();
}

void tm_mpi_test::process_test_case(uint8_t *test_case, uint16_t *rng_seed,
                                    int algorithm)
{
    alignas(64) uint8_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    this->rng_seed = *rng_seed;

    run_alg(algorithm, 1, (uint8_t *)working_code, this->rng_tables,
            &(this->rng_seed));

    for (int i = 0; i < 128; i++)
    {
        test_case[i] = (uint8_t)working_code[i];
    }

    *rng_seed = this->rng_seed;
}

void tm_mpi_test::run_iterations(uint8_t *test_case, uint16_t *rng_seed,
                                 int algorithm, int iterations)
{
    alignas(64) uint8_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    this->rng_seed = *rng_seed;

    run_alg(algorithm, iterations, (uint8_t *)working_code, this->rng_tables,
            &(this->rng_seed));
}
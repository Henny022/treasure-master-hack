#ifndef BRUTEFORCE_TM_AVX512_TEST_H
#define BRUTEFORCE_TM_AVX512_TEST_H
#include "data_sizes.h"

class tm_avx512_intrinsics_test
{
public:
    tm_avx512_intrinsics_test();

    void process_test_case(uint8 * test_case, uint16 *rng_seed, int algorithm);
    void run_iterations(uint8 * test_case, uint16 * rng_seed, int algorithm, int iterations);

    uint16 * rng_table;
    uint16 rng_seed;

    uint8 * regular_rng_values;

    uint8 * alg0_values;

    uint8 * alg6_values;

    uint8 * alg2_values_8;
    uint8 * alg5_values_8;

    uint16 *rng_seed_forward_1;
    uint16 *rng_seed_forward_128;

};

#endif //BRUTEFORCE_TM_AVX512_TEST_H

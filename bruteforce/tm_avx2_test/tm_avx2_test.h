#ifndef TM_AVX2_INTRINSICS_TEST_H
#define TM_AVX2_INTRINSICS_TEST_H
#include <cstdint>

class tm_avx2_intrinsics_test
{
  public:
    tm_avx2_intrinsics_test();

    void process_test_case(uint8_t *test_case, uint16_t *rng_seed,
                           int algorithm);
    void run_iterations(uint8_t *test_case, uint16_t *rng_seed, int algorithm,
                        int iterations);

    uint16_t *rng_table;
    uint16_t rng_seed;

    uint16_t *regular_rng_values;

    uint16_t *alg0_values;

    uint16_t *alg6_values;

    uint8_t *alg2_values_8;
    uint8_t *alg5_values_8;

    uint16_t *rng_seed_forward_1;
    uint16_t *rng_seed_forward_128;
};

#endif // TM_AVX2_INTRINSICS_TEST_H
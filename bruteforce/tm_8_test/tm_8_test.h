#ifndef TM_8_TEST_H
#define TM_8_TEST_H
#include <cstdint>

class tm_8_test
{
  public:
    // Seeded with 8 uint8_t values (4 key and 4 data bytes)
    tm_8_test();

    void process_test_case(uint8_t *test_case, uint16_t *rng_seed,
                           int algorithm);
    void run_iterations(uint8_t *test_case, uint16_t *rng_seed, int algorithm,
                        int iterations);

    uint16_t *rng_table;
    uint16_t rng_seed;

    uint8_t *regular_rng_values;

    uint8_t *alg0_values;

    uint8_t *alg6_values;

    uint8_t *alg4_values;

    uint8_t *alg2_values;

    uint8_t *alg5_values;

    uint16_t *rng_seed_forward_1;
    uint16_t *rng_seed_forward_128;
};

#endif // TM_8_TEST_H
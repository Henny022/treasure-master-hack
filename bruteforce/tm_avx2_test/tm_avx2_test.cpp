#include "tm_avx2_test.h"
#include <cstdint>
#include "alignment.h"
#include "rng.h"
#include "tm_avx2.h"

tm_avx2_intrinsics_test::tm_avx2_intrinsics_test()
{
    this->rng_table = new uint16_t[256 * 256];
    generate_rng_table(this->rng_table);

    regular_rng_values = (uint16_t *)aligned_malloc(
        0x10000 * 128 * 2, 32); // new uint16_t[0x10000 * 128];
    generate_regular_rng_values_16(regular_rng_values, rng_table);

    alg0_values = (uint16_t *)aligned_malloc(
        0x10000 * 128 * 2, 32); // new uint16_t[0x10000 * 128];
    generate_alg0_values_16(alg0_values, rng_table);

    alg6_values = (uint16_t *)aligned_malloc(
        0x10000 * 128 * 2, 32); // new uint16_t[0x10000 * 128];
    generate_alg6_values_16(alg6_values, rng_table);

    alg2_values_8 = (uint8_t *)aligned_malloc(
        0x10000 * 32, 32); // new uint64_t[0x10000 * 128];
    generate_alg2_values_256_16(alg2_values_8, rng_table);

    alg5_values_8 = (uint8_t *)aligned_malloc(
        0x10000 * 32, 32); // new uint64_t[0x10000 * 128];
    generate_alg5_values_256_16(alg5_values_8, rng_table);

    rng_seed_forward_1 = new uint16_t[256 * 256];
    generate_seed_forward_1(rng_seed_forward_1, rng_table);

    rng_seed_forward_128 = new uint16_t[256 * 256];
    generate_seed_forward_128(rng_seed_forward_128, rng_table);
}

void tm_avx2_intrinsics_test::process_test_case(uint8_t *test_case,
                                                uint16_t *rng_seed,
                                                int algorithm)
{
    ALIGNED(32) uint16_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    this->rng_seed = *rng_seed;

    run_alg(algorithm, 1, (uint8_t *)working_code,
            (uint8_t *)this->regular_rng_values, (uint8_t *)this->alg0_values,
            this->alg2_values_8, this->alg5_values_8,
            (uint8_t *)this->alg6_values, &(this->rng_seed), rng_seed_forward_1,
            rng_seed_forward_128);

    for (int i = 0; i < 128; i++)
    {
        test_case[i] = (uint8_t)working_code[i];
    }

    *rng_seed = this->rng_seed;
}

void tm_avx2_intrinsics_test::run_iterations(uint8_t *test_case,
                                             uint16_t *rng_seed, int algorithm,
                                             int iterations)
{
    ALIGNED(32) uint16_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    this->rng_seed = *rng_seed;

    run_alg(algorithm, iterations, (uint8_t *)working_code,
            (uint8_t *)this->regular_rng_values, (uint8_t *)this->alg0_values,
            this->alg2_values_8, this->alg5_values_8,
            (uint8_t *)this->alg6_values, &(this->rng_seed), rng_seed_forward_1,
            rng_seed_forward_128);
}
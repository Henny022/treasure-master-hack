#include "tm_128_8_test.h"
#include <cstdint>
#include "alignment.h"
#include "rng.h"
#include "tm_128_8.h"

tm_128_8_test::tm_128_8_test()
{
    this->rng_table = new uint16_t[256 * 256];
    generate_rng_table(this->rng_table);

    regular_rng_values = (uint8_t *)aligned_malloc(0x10000 * 128, 32);
    generate_regular_rng_values_8(regular_rng_values, rng_table);

    regular_rng_values_lo = (uint8_t *)aligned_malloc(0x10000 * 128, 32);
    generate_regular_rng_values_8_lo(regular_rng_values_lo, rng_table);

    regular_rng_values_hi = (uint8_t *)aligned_malloc(0x10000 * 128, 32);
    generate_regular_rng_values_8_hi(regular_rng_values_hi, rng_table);

    alg0_values = (uint8_t *)aligned_malloc(0x10000 * 128, 32);
    generate_alg0_values_8(alg0_values, rng_table);

    alg6_values = (uint8_t *)aligned_malloc(0x10000 * 128, 32);
    generate_alg6_values_8(alg6_values, rng_table);

    alg4_values_lo = (uint8_t *)aligned_malloc(0x10000 * 128, 32);
    generate_alg4_values_8_lo(alg4_values_lo, rng_table);

    alg4_values_hi = (uint8_t *)aligned_malloc(0x10000 * 128, 32);
    generate_alg4_values_8_hi(alg4_values_hi, rng_table);

    alg2_values = (uint8_t *)aligned_malloc(0x10000 * 16, 32);
    generate_alg2_values_128_8(alg2_values, rng_table);

    alg5_values = (uint8_t *)aligned_malloc(0x10000 * 16, 32);
    generate_alg5_values_128_8(alg5_values, rng_table);

    rng_seed_forward_1 = new uint16_t[256 * 256];
    generate_seed_forward_1(rng_seed_forward_1, rng_table);

    rng_seed_forward_128 = new uint16_t[256 * 256];
    generate_seed_forward_128(rng_seed_forward_128, rng_table);
}

void tm_128_8_test::process_test_case(uint8_t *test_case, uint16_t *rng_seed,
                                      int algorithm)
{
    ALIGNED(32) uint8_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    if (algorithm == 0)
    {
        alg0((uint8_t *)working_code, (uint8_t *)alg0_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 1)
    {
        alg1((uint8_t *)working_code, (uint8_t *)regular_rng_values_lo,
             (uint8_t *)regular_rng_values_hi, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 2)
    {
        alg2((uint8_t *)working_code, (uint8_t *)alg2_values, *rng_seed);
        *rng_seed = rng_seed_forward_1[*rng_seed];
    }
    else if (algorithm == 3)
    {
        alg3((uint8_t *)working_code, (uint8_t *)regular_rng_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 4)
    {
        alg1((uint8_t *)working_code, (uint8_t *)alg4_values_lo,
             (uint8_t *)alg4_values_hi, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 5)
    {
        alg5((uint8_t *)working_code, (uint8_t *)alg5_values, *rng_seed);
        *rng_seed = rng_seed_forward_1[*rng_seed];
    }
    else if (algorithm == 6)
    {
        alg6((uint8_t *)working_code, (uint8_t *)alg6_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 7)
    {
        alg7((uint8_t *)working_code);
    }

    for (int i = 0; i < 128; i++)
    {
        test_case[i] = working_code[i];
    }
}

void tm_128_8_test::run_iterations(uint8_t *test_case, uint16_t *rng_seed,
                                   int algorithm, int iterations)
{
    ALIGNED(32) uint8_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    if (algorithm == 0)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg0((uint8_t *)working_code, (uint8_t *)alg0_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 1)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg1((uint8_t *)working_code, (uint8_t *)regular_rng_values_lo,
                 (uint8_t *)regular_rng_values_hi, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 2)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg2((uint8_t *)working_code, (uint8_t *)alg2_values, *rng_seed);
            *rng_seed = rng_seed_forward_1[*rng_seed];
        }
    }
    else if (algorithm == 3)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg3((uint8_t *)working_code, (uint8_t *)regular_rng_values,
                 *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 4)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg1((uint8_t *)working_code, (uint8_t *)alg4_values_lo,
                 (uint8_t *)alg4_values_hi, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 5)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg5((uint8_t *)working_code, (uint8_t *)alg5_values, *rng_seed);
            *rng_seed = rng_seed_forward_1[*rng_seed];
        }
    }
    else if (algorithm == 6)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg6((uint8_t *)working_code, (uint8_t *)alg6_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 7)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg7((uint8_t *)working_code);
        }
    }
}
#include "tm_32_16_test.h"
#include <cstdint>
#include "rng.h"
#include "tm_32_16.h"

tm_32_16_test::tm_32_16_test()
{
    this->rng_table = new uint16_t[256 * 256];
    generate_rng_table(this->rng_table);

    regular_rng_values = new uint16_t[0x10000 * 128];
    generate_regular_rng_values_16(regular_rng_values, rng_table);

    alg0_values = new uint16_t[0x10000 * 128];
    generate_alg0_values_16(alg0_values, rng_table);

    alg6_values = new uint16_t[0x10000 * 128];
    generate_alg6_values_16(alg6_values, rng_table);

    alg4_values = new uint16_t[0x10000 * 128];
    generate_alg4_values_16(alg4_values, rng_table);

    alg2_values = new uint32_t[0x10000];
    generate_alg2_values_32_16(alg2_values, rng_table);

    alg5_values = new uint32_t[0x10000];
    generate_alg5_values_32_16(alg5_values, rng_table);

    rng_seed_forward_1 = new uint16_t[256 * 256];
    generate_seed_forward_1(rng_seed_forward_1, rng_table);

    rng_seed_forward_128 = new uint16_t[256 * 256];
    generate_seed_forward_128(rng_seed_forward_128, rng_table);
}

void tm_32_16_test::process_test_case(uint8_t *test_case, uint16_t *rng_seed,
                                      int algorithm)
{
    uint16_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    if (algorithm == 0)
    {
        alg0((uint32_t *)working_code, (uint32_t *)alg0_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 1)
    {
        alg1((uint32_t *)working_code, (uint32_t *)regular_rng_values,
             *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 2)
    {
        alg2((uint32_t *)working_code, (uint32_t *)alg2_values, *rng_seed);
        *rng_seed = rng_seed_forward_1[*rng_seed];
    }
    else if (algorithm == 3)
    {
        alg3((uint32_t *)working_code, (uint32_t *)regular_rng_values,
             *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 4)
    {
        alg1((uint32_t *)working_code, (uint32_t *)alg4_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 5)
    {
        alg5((uint32_t *)working_code, (uint32_t *)alg5_values, *rng_seed);
        *rng_seed = rng_seed_forward_1[*rng_seed];
    }
    else if (algorithm == 6)
    {
        alg6((uint32_t *)working_code, (uint32_t *)alg6_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 7)
    {
        alg7((uint32_t *)working_code);
    }

    for (int i = 0; i < 128; i++)
    {
        test_case[i] = (uint8_t)working_code[i];
    }
}

void tm_32_16_test::run_iterations(uint8_t *test_case, uint16_t *rng_seed,
                                   int algorithm, int iterations)
{
    uint16_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    if (algorithm == 0)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg0((uint32_t *)working_code, (uint32_t *)alg0_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 1)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg1((uint32_t *)working_code, (uint32_t *)regular_rng_values,
                 *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 2)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg2((uint32_t *)working_code, (uint32_t *)alg2_values, *rng_seed);
            *rng_seed = rng_seed_forward_1[*rng_seed];
        }
    }
    else if (algorithm == 3)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg3((uint32_t *)working_code, (uint32_t *)regular_rng_values,
                 *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 4)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg1((uint32_t *)working_code, (uint32_t *)alg4_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 5)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg5((uint32_t *)working_code, (uint32_t *)alg5_values, *rng_seed);
            *rng_seed = rng_seed_forward_1[*rng_seed];
        }
    }
    else if (algorithm == 6)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg6((uint32_t *)working_code, (uint32_t *)alg6_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 7)
    {
        for (int i = 0; i < iterations; i++)
        {
            alg7((uint32_t *)working_code);
        }
    }
}
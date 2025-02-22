#include "tm_8_test.h"
#include <cstdint>
#include "rng.h"
#include "tm_8.h"

tm_8_test::tm_8_test()
{
    rng_table = new uint16_t[256 * 256];
    generate_rng_table(this->rng_table);

    regular_rng_values = new uint8_t[0x10000 * 128];
    generate_regular_rng_values_8(regular_rng_values, rng_table);

    alg0_values = new uint8_t[0x10000 * 128];
    generate_alg0_values_8(alg0_values, rng_table);

    alg6_values = new uint8_t[0x10000 * 128];
    generate_alg6_values_8(alg6_values, rng_table);

    alg4_values = new uint8_t[0x10000 * 128];
    generate_alg4_values_8(alg4_values, rng_table);

    alg2_values = new uint8_t[0x10000];
    generate_alg2_values_8_8(alg2_values, rng_table);

    alg5_values = new uint8_t[0x10000];
    generate_alg5_values_8_8(alg5_values, rng_table);

    rng_seed_forward_1 = new uint16_t[256 * 256];
    generate_seed_forward_1(rng_seed_forward_1, rng_table);

    rng_seed_forward_128 = new uint16_t[256 * 256];
    generate_seed_forward_128(rng_seed_forward_128, rng_table);
}

void tm_8_test::process_test_case(uint8_t *test_case, uint16_t *rng_seed,
                                  int algorithm)
{
    uint8_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    if (algorithm == 0)
    {
        working_code_alg_0(working_code, alg0_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 1)
    {
        working_code_alg_1(working_code, regular_rng_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 2)
    {
        working_code_alg_2(working_code, alg2_values, *rng_seed);
        *rng_seed = rng_seed_forward_1[*rng_seed];
    }
    else if (algorithm == 3)
    {
        working_code_alg_3(working_code, regular_rng_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 4)
    {
        working_code_alg_1(working_code, alg4_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 5)
    {
        working_code_alg_5(working_code, alg5_values, *rng_seed);
        *rng_seed = rng_seed_forward_1[*rng_seed];
    }
    else if (algorithm == 6)
    {
        working_code_alg_6(working_code, alg6_values, *rng_seed);
        *rng_seed = rng_seed_forward_128[*rng_seed];
    }
    else if (algorithm == 7)
    {
        working_code_alg_7(working_code);
    }

    for (int i = 0; i < 128; i++)
    {
        test_case[i] = working_code[i];
    }
}

void tm_8_test::run_iterations(uint8_t *test_case, uint16_t *rng_seed,
                               int algorithm, int iterations)
{
    uint8_t working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    if (algorithm == 0)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_0(working_code, alg0_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 1)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_1(working_code, regular_rng_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 2)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_2(working_code, alg2_values, *rng_seed);
            *rng_seed = rng_seed_forward_1[*rng_seed];
        }
    }
    else if (algorithm == 3)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_3(working_code, regular_rng_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 4)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_1(working_code, alg4_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 5)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_5(working_code, alg5_values, *rng_seed);
            *rng_seed = rng_seed_forward_1[*rng_seed];
        }
    }
    else if (algorithm == 6)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_6(working_code, alg6_values, *rng_seed);
            *rng_seed = rng_seed_forward_128[*rng_seed];
        }
    }
    else if (algorithm == 7)
    {
        for (int i = 0; i < iterations; i++)
        {
            working_code_alg_7(working_code);
        }
    }
}
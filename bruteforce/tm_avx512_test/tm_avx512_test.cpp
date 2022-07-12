#include "data_sizes.h"
#include "alignment.h"
#include "tm_avx512_test.h"
#include "tm_avx512.h"
#include "rng.h"

tm_avx512_intrinsics_test::tm_avx512_intrinsics_test()
{
    this->rng_table = new uint16[256*256];
    generate_rng_table(this->rng_table);


    regular_rng_values = (uint8*)aligned_malloc(0x10000 * 128, 64); // new uint16[0x10000 * 128];
    generate_regular_rng_values_8(regular_rng_values, rng_table);

    alg0_values = (uint8*)aligned_malloc(0x10000 * 128, 64); //new uint16[0x10000 * 128];
    generate_alg0_values_8(alg0_values, rng_table);

    alg6_values = (uint8*)aligned_malloc(0x10000 * 128, 64); //new uint16[0x10000 * 128];
    generate_alg6_values_8(alg6_values, rng_table);

    alg2_values_8 = (uint8*)aligned_malloc(0x10000 * 64, 64); //new uint64[0x10000 * 128];
    generate_alg2_values_512_8(alg2_values_8, rng_table);

    alg5_values_8 = (uint8*)aligned_malloc(0x10000 * 64, 64); //new uint64[0x10000 * 128];
    generate_alg5_values_512_8(alg5_values_8, rng_table);

    rng_seed_forward_1 = new uint16[256*256];
    generate_seed_forward_1(rng_seed_forward_1, rng_table);

    rng_seed_forward_128 = new uint16[256*256];
    generate_seed_forward_128(rng_seed_forward_128, rng_table);
}

void tm_avx512_intrinsics_test::process_test_case(uint8 * test_case, uint16 * rng_seed, int algorithm)
{
    ALIGNED(64) uint8 working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    this->rng_seed = *rng_seed;

    run_alg(algorithm,1,(uint8*)working_code,(uint8*)this->regular_rng_values,(uint8*)this->alg0_values,this->alg2_values_8,this->alg5_values_8,(uint8*)this->alg6_values,&(this->rng_seed), rng_seed_forward_1, rng_seed_forward_128);

    for (int i = 0; i < 128; i++)
    {
        test_case[i] = (uint8)working_code[i];
    }

    *rng_seed = this->rng_seed;
}

void tm_avx512_intrinsics_test::run_iterations(uint8 * test_case, uint16 * rng_seed, int algorithm, int iterations)
{
    ALIGNED(64) uint8 working_code[128];

    for (int i = 0; i < 128; i++)
    {
        working_code[i] = test_case[i];
    }

    this->rng_seed = *rng_seed;

    run_alg(algorithm,iterations,(uint8*)working_code,(uint8*)this->regular_rng_values,(uint8*)this->alg0_values,this->alg2_values_8,this->alg5_values_8,(uint8*)this->alg6_values,&(this->rng_seed), rng_seed_forward_1, rng_seed_forward_128);
}
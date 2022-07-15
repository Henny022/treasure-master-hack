#ifndef BRUTEFORCE_RNG_H
#define BRUTEFORCE_RNG_H

#include <array>
#include <cstdint>
#include <immintrin.h>

using rng_table_t = std::array<uint16_t, 0x10000>;

static inline rng_table_t generate_rng_table()
{
    rng_table_t rng_table;
    for (int i = 0; i < 0x100; i++)
    {
        for (int j = 0; j < 0x100; j++)
        {
            unsigned int rngA = i;
            unsigned int rngB = j;

            uint8_t carry = 0;

            rngB = (rngB + rngA) & 0xFF;

            rngA = rngA + 0x89;
            carry = rngA > 0xFF ? 1 : 0;
            rngA = rngA & 0xFF;

            rngB = rngB + 0x2A + carry;
            carry = rngB > 0xFF ? 1 : 0;
            rngB = rngB & 0xFF;

            rngA = rngA + 0x21 + carry;
            carry = rngA > 0xFF ? 1 : 0;
            rngA = rngA & 0xFF;

            rngB = rngB + 0x43 + carry;
            carry = rngB > 0xFF ? 1 : 0;
            rngB = rngB & 0xFF;

            rng_table[(i * 0x100) + j] = (rngA << 8) | rngB;
        }
    }
    return rng_table;
}

static inline uint8_t run_rng(uint16_t &rng_seed, const rng_table_t &rng_table)
{
    uint16_t result = rng_table[rng_seed];
    rng_seed = result;

    return ((result >> 8) ^ (result)) & 0xFF;
}

using rng_vector_t = std::array<__m512i, 2>;

using rng_vectors_t = std::array<rng_vector_t, 0x10000>;
using rng_values_t = std::array<__m512i, 0x10000>;

static inline rng_vectors_t
generate_regular_rng_values(const rng_table_t &rng_table)
{
    rng_vectors_t regular_rng_values;
    uint16_t rng_seed;
    for (int i = 0; i < 0x10000; i++)
    {
        rng_seed = i;
        rng_vector_t rng_vector;
        auto *rng_vector_8 = (uint8_t *)&rng_vector;
        for (int j = 127; j >= 0; --j)
        {
            rng_vector_8[j] = run_rng(rng_seed, rng_table);
        }
        regular_rng_values[i] = rng_vector;
    }
    return regular_rng_values;
}

static inline rng_vectors_t generate_alg0_values(const rng_table_t &rng_table)
{
    rng_vectors_t alg0_values;
    uint16_t rng_seed;
    for (int i = 0; i < 0x10000; i++)
    {
        rng_seed = i;
        rng_vector_t rng_vector;
        auto *rng_vector_8 = (uint8_t *)&rng_vector;
        for (int j = 127; j >= 0; --j)
        {
            rng_vector_8[j] = (run_rng(rng_seed, rng_table) >> 7) & 0x01;
        }
        alg0_values[i] = rng_vector;
    }
    return alg0_values;
}

static inline rng_vectors_t generate_alg6_values(const rng_table_t &rng_table)
{
    rng_vectors_t alg6_values;
    uint16_t rng_seed;
    for (int i = 0; i < 0x10000; i++)
    {
        rng_seed = i;
        rng_vector_t rng_vector;
        auto *rng_vector_8 = (uint8_t *)&rng_vector;
        for (int j = 0; j < 128; j++)
        {
            rng_vector_8[j] = run_rng(rng_seed, rng_table) & 0x80;
        }
        alg6_values[i] = rng_vector;
    }
    return alg6_values;
}

static inline rng_values_t generate_alg2_values(const rng_table_t &rng_table)
{
    rng_values_t alg2_values;
    uint16_t rng_seed;
    for (int i = 0; i < 0x10000; i++)
    {
        rng_seed = i;
        alg2_values[i] =
            _mm512_set1_epi8((run_rng(rng_seed, rng_table) & 0x80) >> 7);
    }
    return alg2_values;
}

static inline rng_values_t generate_alg5_values(const rng_table_t &rng_table)
{
    rng_values_t alg5_values;
    uint16_t rng_seed;
    for (int i = 0; i < 0x10000; i++)
    {
        rng_seed = i;
        alg5_values[i] = _mm512_set1_epi8(run_rng(rng_seed, rng_table) & 0x80);
    }
    return alg5_values;
}

using rng_forward_table_t = std::array<uint16_t, 0x10000>;

static inline rng_forward_table_t
generate_seed_forward_128(const rng_table_t &rng_table)
{
    rng_forward_table_t values;
    uint16_t rng_seed;
    for (int i = 0; i < 0x10000; i++)
    {
        rng_seed = i;
        for (int j = 0; j < 128; j++)
        {
            rng_seed = rng_table[rng_seed];
        }
        values[i] = rng_seed;
    }
    return values;
}

struct rng_tables_t
{
    rng_table_t rng_table;
    rng_vectors_t regular;
    rng_vectors_t alg0;
    rng_vectors_t alg6;
    rng_values_t alg2;
    rng_values_t alg5;
    rng_forward_table_t forward_128;
};

static inline rng_tables_t *generate_rng_tables()
{
    auto *rng_tables = new rng_tables_t;
    rng_tables->rng_table = generate_rng_table();
    rng_tables->regular = generate_regular_rng_values(rng_tables->rng_table);
    rng_tables->alg0 = generate_alg0_values(rng_tables->rng_table);
    rng_tables->alg6 = generate_alg6_values(rng_tables->rng_table);
    rng_tables->alg2 = generate_alg2_values(rng_tables->rng_table);
    rng_tables->alg5 = generate_alg5_values(rng_tables->rng_table);
    rng_tables->forward_128 = generate_seed_forward_128(rng_tables->rng_table);
    return rng_tables;
}

#endif // BRUTEFORCE_RNG_H

#include "tm_64_8.h"
#include <cstdint>

void alg0(uint64_t *working_code, const uint64_t *alg0_values,
          const uint16_t rng_seed)
{
    for (int i = 0; i < 16; i++)
    {
        working_code[i] = ((working_code[i] << 1) & 0xFEFEFEFEFEFEFEFEull) |
                          alg0_values[(rng_seed * 128) / 8 + i];
    }
}

void alg1(uint64_t *working_code, const uint64_t *regular_rng_values_lo,
          const uint64_t *regular_rng_values_hi, const uint16_t rng_seed)
{
    for (int i = 0; i < 16; i++)
    {
        working_code[i] = (((working_code[i] & 0x00FF00FF00FF00FFull) +
                            regular_rng_values_lo[(rng_seed * 128) / 8 + i]) &
                           0x00FF00FF00FF00FFull) |
                          (((working_code[i] & 0xFF00FF00FF00FF00ull) +
                            regular_rng_values_hi[(rng_seed * 128) / 8 + i]) &
                           0xFF00FF00FF00FF00ull);
    }
}

void alg2(uint64_t *working_code, const uint64_t *alg2_values,
          const uint16_t rng_seed)
{
    uint64_t carry = alg2_values[rng_seed];
    for (int i = 15; i >= 0; i--)
    {
        uint64_t next_carry = (working_code[i] & 0x0000000000000001ull) << 56;

        carry = carry | ((working_code[i] & 0x0001000100010000ull) >> 8);
        working_code[i] = ((working_code[i] >> 1) & 0x007F007F007F007Full) |
                          ((working_code[i] << 1) & 0xFE00FE00FE00FE00ull) |
                          ((working_code[i] >> 8) & 0x0080008000800080ull) |
                          carry;

        carry = next_carry;
    }
}

void alg3(uint64_t *working_code, const uint64_t *regular_rng_values,
          const uint16_t rng_seed)
{
    for (int i = 0; i < 16; i++)
    {
        working_code[i] =
            working_code[i] ^ regular_rng_values[(rng_seed * 128) / 8 + i];
    }
}

void alg5(uint64_t *working_code, const uint64_t *alg5_values,
          const uint16_t rng_seed)
{
    uint64_t carry = alg5_values[rng_seed];
    for (int i = 15; i >= 0; i--)
    {
        uint64_t next_carry = (working_code[i] & 0x0000000000000080ull) << 56;

        carry = carry | ((working_code[i] & 0x0080008000800000ull) >> 8);
        working_code[i] = ((working_code[i] << 1) & 0x00FE00FE00FE00FEull) |
                          ((working_code[i] >> 1) & 0x7F007F007F007F00ull) |
                          ((working_code[i] >> 8) & 0x0001000100010001ull) |
                          carry;

        carry = next_carry;
    }
}

void alg6(uint64_t *working_code, const uint64_t *alg6_values,
          const uint16_t rng_seed)
{
    for (int i = 0; i < 16; i++)
    {
        working_code[i] = ((working_code[i] >> 1) & 0x7F7F7F7F7F7F7F7Full) |
                          alg6_values[(rng_seed * 128) / 8 + i];
    }
}

void alg7(uint64_t *working_code)
{
    for (int i = 0; i < 16; i++)
    {
        working_code[i] = working_code[i] ^ 0xFFFFFFFFFFFFFFFFull;
    }
}
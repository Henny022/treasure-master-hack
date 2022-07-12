#include <cstdint>

void alg0(uint32_t *working_code, const uint32_t *alg0_values,
          const uint16_t rng_seed)
{
    for (int i = 0; i < 64; i++)
    {
        working_code[i] =
            ((working_code[i] << 1) | alg0_values[(rng_seed * 128) / 2 + i]) &
            0xFF00FF;
    }
}

void alg1(uint32_t *working_code, const uint32_t *regular_rng_values,
          const uint16_t rng_seed)
{
    for (int i = 0; i < 64; i++)
    {
        working_code[i] =
            (working_code[i] + regular_rng_values[(rng_seed * 128) / 2 + i]) &
            0xFF00FF;
    }
}

void alg2(uint32_t *working_code, const uint32_t *alg2_values,
          const uint16_t rng_seed)
{
    uint32_t carry = alg2_values[rng_seed];
    for (int i = 63; i >= 0; i--)
    {
        uint32_t next_carry = (working_code[i] & 0x00000001) << 16;

        working_code[i] = (((working_code[i] & 0x000000FF) >> 1) & 0x7F) |
                          (((working_code[i] & 0x00FF0000) << 1) & 0x00FE0000) |
                          ((working_code[i] & 0x00800000) >> 16) | carry;

        carry = next_carry;
    }
}

void alg3(uint32_t *working_code, const uint32_t *regular_rng_values,
          const uint16_t rng_seed)
{
    for (int i = 0; i < 64; i++)
    {
        working_code[i] =
            working_code[i] ^ regular_rng_values[(rng_seed * 128) / 2 + i];
    }
}

void alg5(uint32_t *working_code, const uint32_t *alg5_values,
          const uint16_t rng_seed)
{
    uint32_t carry = alg5_values[rng_seed];
    for (int i = 63; i >= 0; i--)
    {
        uint32_t next_carry = (working_code[i] & 0x00000080) << 16;

        working_code[i] = (((working_code[i] & 0x000000FF) << 1) & 0xFE) |
                          (((working_code[i] & 0x00FF0000) >> 1) & 0x007F0000) |
                          ((working_code[i] & 0x00010000) >> 16) | carry;

        carry = next_carry;
    }
}

void alg6(uint32_t *working_code, const uint32_t *alg6_values,
          const uint16_t rng_seed)
{
    for (int i = 0; i < 64; i++)
    {
        working_code[i] =
            ((working_code[i] >> 1) | alg6_values[(rng_seed * 128) / 2 + i]) &
            0xFF00FF;
    }
}

void alg7(uint32_t *working_code)
{
    for (int i = 0; i < 64; i++)
    {
        working_code[i] = working_code[i] ^ 0xFF00FF;
    }
}

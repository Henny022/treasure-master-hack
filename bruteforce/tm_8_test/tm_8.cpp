#include <cstdint>

void working_code_alg_0(uint8_t *working_code, const uint8_t *alg0_values,
                        const uint16_t rng_seed)
{
    for (int i = 0; i < 128; i++)
    {
        working_code[i] =
            (working_code[i] << 1) | alg0_values[rng_seed * 128 + i];
    }
}

void working_code_alg_1(uint8_t *working_code,
                        const uint8_t *regular_rng_values,
                        const uint16_t rng_seed)
{
    for (int i = 0; i < 128; i++)
    {
        working_code[i] =
            working_code[i] + regular_rng_values[rng_seed * 128 + i];
    }
}

void working_code_alg_2(uint8_t *working_code, const uint8_t *alg2_values,
                        const uint16_t rng_seed)
{
    uint8_t carry = alg2_values[rng_seed];
    for (int i = 127; i >= 0; i -= 2)
    {
        uint8_t next_carry = working_code[i - 1] & 0x01;

        working_code[i - 1] =
            (working_code[i - 1] >> 1) | (working_code[i] & 0x80);
        working_code[i] = (working_code[i] << 1) | (carry & 0x01);

        carry = next_carry;
    }
}

void working_code_alg_3(uint8_t *working_code,
                        const uint8_t *regular_rng_values,
                        const uint16_t rng_seed)
{
    for (int i = 0; i < 128; i++)
    {
        working_code[i] =
            working_code[i] ^ regular_rng_values[rng_seed * 128 + i];
    }
}

void working_code_alg_5(uint8_t *working_code, const uint8_t *alg5_values,
                        const uint16_t rng_seed)
{
    uint8_t carry = alg5_values[rng_seed];

    for (int i = 127; i >= 0; i -= 2)
    {
        uint8_t next_carry = working_code[i - 1] & 0x80;

        working_code[i - 1] =
            (working_code[i - 1] << 1) | (working_code[i] & 0x01);
        working_code[i] = (working_code[i] >> 1) | carry;

        carry = next_carry;
    }
}

void working_code_alg_6(uint8_t *working_code, const uint8_t *alg6_values,
                        const uint16_t rng_seed)
{
    for (int i = 0; i < 128; i++)
    {
        working_code[i] =
            (working_code[i] >> 1) | alg6_values[rng_seed * 128 + i];
    }
}

void working_code_alg_7(uint8_t *working_code)
{
    for (int i = 0; i < 128; i++)
    {
        working_code[i] = working_code[i] ^ 0xFF;
    }
}

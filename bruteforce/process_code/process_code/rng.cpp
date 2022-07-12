#include "rng.h"
#include <cstdint>

uint16_t rng_table[0x100][0x100];

unsigned char rng_real(unsigned char *rng1, unsigned char *rng2)
{
    int rngA = *rng1;
    int rngB = *rng2;
    // LDA $0436
    // CLC
    unsigned char carry = 0;
    // ADC $0437
    // STA $0437
    // Basically, add rng1 and rng2 together w/o carry and store it to rng2
    rngB = (unsigned char)(rngB + rngA);

    // LDA #$89
    // CLC
    // ADC $0436
    // STA $0436
    // Basically, add #$89 to rng1, and remember the carry for the next addition
    rngA = rngA + 0x89;
    if (rngA > 0xFF)
    {
        carry = 1;
    }
    else
    {
        carry = 0;
    }
    rngA = (unsigned char)rngA;

    // LDA #$2A
    // ADC $0437 = #$AE
    // STA $0437 = #$AE
    rngB = rngB + 0x2A + carry;
    if (rngB > 0xFF)
    {
        carry = 1;
    }
    else
    {
        carry = 0;
    }
    rngB = (unsigned char)rngB;

    // LDA $0436 = #$71
    // ADC #$21
    // STA $0436 = #$71
    rngA = rngA + 0x21 + carry;
    if (rngA > 0xFF)
    {
        carry = 1;
    }
    else
    {
        carry = 0;
    }
    rngA = (unsigned char)rngA;

    // LDA $0437 = #$AE
    // ADC #$43
    // STA $0437 = #$AE
    rngB = rngB + 0x43 + carry;
    if (rngB > 0xFF)
    {
        carry = 1;
    }
    else
    {
        carry = 0;
    }
    rngB = (unsigned char)rngB;

    // EOR $0436 = #$71
    *rng1 = (unsigned char)rngA;
    *rng2 = (unsigned char)rngB;

    return *rng1 ^ *rng2;
}

void generate_rng_table()
{
    for (int i = 0; i < 0x100; i++)
    {
        for (int j = 0; j < 0x100; j++)
        {
            unsigned char rng1 = i;
            unsigned char rng2 = j;
            rng_real(&rng1, &rng2);
            rng_table[i][j] = rng1 << 8 | rng2;
        }
    }
}

uint8_t RNG::run()
{
    uint16_t result = rng_table[rng1][rng2];
    rng1 = (result >> 8) & 0xFF;
    rng2 = result & 0xFF;

    return rng1 ^ rng2;
}

void RNG::seed(uint8_t a, uint8_t b)
{
    rng1 = a;
    rng2 = b;
}
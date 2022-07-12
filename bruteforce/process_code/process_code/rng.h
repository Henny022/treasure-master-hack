#ifndef RNG_H
#define RNG_H
#include <cstdint>

extern uint16_t rng_table[0x100][0x100];

unsigned char rng_real(unsigned char *rng1, unsigned char *rng2);

void generate_rng_table();

class RNG
{
  public:
    RNG() : rng1(0), rng2(0){};
    RNG(uint8_t a, uint8_t b) : rng1(a), rng2(b){};

    uint8_t rng1;
    uint8_t rng2;

    uint8_t run();
    void seed(uint8_t rng1, uint8_t rng2);
};

#endif // RNG_H
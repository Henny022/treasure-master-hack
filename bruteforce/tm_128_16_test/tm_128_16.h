#ifndef TM_128_16_H
#define TM_128_16_H

#include <cstdint>

void alg0(uint8_t *working_code, const uint8_t *alg0_values,
          const uint16_t rng_seed);

void alg1(uint8_t *working_code, const uint8_t *regular_rng_values,
          const uint16_t rng_seed);

void alg2(uint8_t *working_code, const uint8_t *alg2_values,
          const uint16_t rng_seed);

void alg3(uint8_t *working_code, const uint8_t *regular_rng_values,
          const uint16_t rng_seed);

void alg5(uint8_t *working_code, const uint8_t *alg5_values,
          const uint16_t rng_seed);

void alg6(uint8_t *working_code, const uint8_t *alg6_values,
          const uint16_t rng_seed);

void alg7(uint8_t *working_code);

#endif // TM_128_16_H
#ifndef TM_32_16_H
#define TM_32_16_H

#include <cstdint>

void alg0(uint32_t *working_code, const uint32_t *alg0_values,
          const uint16_t rng_seed);

void alg1(uint32_t *working_code, const uint32_t *regular_rng_values,
          const uint16_t rng_seed);

void alg2(uint32_t *working_code, const uint32_t *alg2_values,
          const uint16_t rng_seed);

void alg3(uint32_t *working_code, const uint32_t *regular_rng_values,
          const uint16_t rng_seed);

void alg5(uint32_t *working_code, const uint32_t *alg5_values,
          const uint16_t rng_seed);

void alg6(uint32_t *working_code, const uint32_t *alg6_values,
          const uint16_t rng_seed);

void alg7(uint32_t *working_code);

#endif // TM_32_16_H
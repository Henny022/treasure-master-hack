#ifndef TM_64_16_H
#define TM_64_16_H

#include <cstdint>

void alg0(uint64_t *working_code, const uint64_t *alg0_values,
          const uint16_t rng_seed);

void alg1(uint64_t *working_code, const uint64_t *regular_rng_values,
          const uint16_t rng_seed);

void alg2(uint64_t *working_code, const uint64_t *alg2_values,
          const uint16_t rng_seed);

void alg3(uint64_t *working_code, const uint64_t *regular_rng_values,
          const uint16_t rng_seed);

void alg5(uint64_t *working_code, const uint64_t *alg5_values,
          const uint16_t rng_seed);

void alg6(uint64_t *working_code, const uint64_t *alg6_values,
          const uint16_t rng_seed);

void alg7(uint64_t *working_code);

#endif // TM_64_16_H
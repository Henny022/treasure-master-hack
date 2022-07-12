#ifndef RNG_H
#define RNG_H

#include <cstdint>

void generate_rng_table(uint16_t *rng_table);
uint8_t run_rng(uint16_t *rng_seed, uint16_t *rng_table);

void generate_regular_rng_values_8(uint8_t *regular_rng_values,
                                   uint16_t *rng_table);
void generate_regular_rng_values_16(uint16_t *regular_rng_values,
                                    uint16_t *rng_table);

void generate_regular_rng_values_8_lo(uint8_t *regular_rng_values_lo,
                                      uint16_t *rng_table);
void generate_regular_rng_values_8_hi(uint8_t *regular_rng_values_hi,
                                      uint16_t *rng_table);

void generate_alg0_values_8(uint8_t *alg0_values, uint16_t *rng_table);
void generate_alg0_values_16(uint16_t *alg0_values, uint16_t *rng_table);

void generate_alg6_values_8(uint8_t *alg6_values, uint16_t *rng_table);
void generate_alg6_values_16(uint16_t *alg6_values, uint16_t *rng_table);

void generate_alg4_values_8(uint8_t *alg4_values, uint16_t *rng_table);
void generate_alg4_values_8_lo(uint8_t *alg4_values_lo, uint16_t *rng_table);
void generate_alg4_values_8_hi(uint8_t *alg4_values_hi, uint16_t *rng_table);

void generate_alg4_values_16(uint16_t *alg4_values, uint16_t *rng_table);

void generate_alg2_values_8_8(uint8_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_32_8(uint32_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_32_16(uint32_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_64_8(uint64_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_64_16(uint64_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_128_8(uint8_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_128_16(uint8_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_256_8(uint8_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_256_16(uint8_t *alg2_values, uint16_t *rng_table);
void generate_alg2_values_512_8(uint8_t *alg2_values, uint16_t *rng_table);

void generate_alg5_values_8_8(uint8_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_32_8(uint32_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_32_16(uint32_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_64_8(uint64_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_64_16(uint64_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_128_8(uint8_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_128_16(uint8_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_256_8(uint8_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_256_16(uint8_t *alg5_values, uint16_t *rng_table);
void generate_alg5_values_512_8(uint8_t *alg5_values, uint16_t *rng_table);

void generate_seed_forward_1(uint16_t *values, uint16_t *rng_table);
void generate_seed_forward_128(uint16_t *values, uint16_t *rng_table);

#endif // RNG_H
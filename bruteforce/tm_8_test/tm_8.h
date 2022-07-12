#ifndef TM_8_H
#define TM_8_H

#include <cstdint>

void working_code_alg_0(uint8_t *working_code, const uint8_t *alg0_values,
                        const uint16_t rng_seed);

void working_code_alg_1(uint8_t *working_code,
                        const uint8_t *regular_rng_values,
                        const uint16_t rng_seed);

void working_code_alg_2(uint8_t *working_code, const uint8_t *alg2_values,
                        const uint16_t rng_seed);

void working_code_alg_3(uint8_t *working_code,
                        const uint8_t *regular_rng_values,
                        const uint16_t rng_seed);

void working_code_alg_5(uint8_t *working_code, const uint8_t *alg5_values,
                        const uint16_t rng_seed);

void working_code_alg_6(uint8_t *working_code, const uint8_t *alg6_values,
                        const uint16_t rng_seed);

void working_code_alg_7(uint8_t *working_code);

#endif // TM_8_H
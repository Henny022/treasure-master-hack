#ifndef TM_AVX_INTRINSICS_H
#define TM_AVX_INTRINSICS_H

#include <emmintrin.h> //SSE2
#include <mmintrin.h>  //MMX
#include <nmmintrin.h> //SSE4.2
#include <pmmintrin.h> //SSE3
#include <smmintrin.h> //SSE4.1
#include <tmmintrin.h> //SSSE3
#include <xmmintrin.h> //SSE
//#include <ammintrin.h> //SSE4A
#include <immintrin.h> //AVX
//#include <zmmintrin.h> //AVX512

#include <cstdint>

void run_alg(int alg_id, int iterations, uint8_t *working_code,
             uint8_t *regular_rng_values, uint8_t *alg0_values,
             uint8_t *alg2_values, uint8_t *alg5_values, uint8_t *alg6_values,
             uint16_t *rng_seed, uint16_t *rng_forward_1,
             uint16_t *rng_forward_128);

#endif // TM_AVX_INTRINSICS_H
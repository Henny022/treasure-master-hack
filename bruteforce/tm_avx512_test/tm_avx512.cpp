#include "tm_avx512.h"

#include <mmintrin.h>  //MMX
#include <xmmintrin.h> //SSE
#include <emmintrin.h> //SSE2
#include <pmmintrin.h> //SSE3
#include <tmmintrin.h> //SSSE3
#include <smmintrin.h> //SSE4.1
#include <nmmintrin.h> //SSE4.2
//#include <ammintrin.h> //SSE4A
#include <immintrin.h> //AVX
//#include <zmmintrin.h> //AVX512

static const __m512i sll_mask = _mm512_set1_epi8(0xFE);
static const __m512i srl_mask = _mm512_set1_epi8(0x7F);

static const __m512i mask_even = _mm512_set1_epi16(0x00ff);
static const __m512i mask_odd = _mm512_set1_epi16(0xff00);

static const __m512i carry_permutation = _mm512_set_epi8(
        0x40, 0x3f,0x3e, 0x3d, 0x3c, 0x3b, 0x3a, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31,
        0x30, 0x2f,0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21,
        0x20, 0x1f,0x1e, 0x1d, 0x1c, 0x1b, 0x1a, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11,
        0x10, 0x0f,0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01
);

static const __m512i carry_mask_l = _mm512_set1_epi8(0x01);
static const __m512i carry_mask_r = _mm512_set1_epi8(0x80);

void run_alg(int alg_id, int iterations, uint8 *working_code, uint8 *regular_rng_values, uint8 *alg0_values,
             uint8 *alg2_values, uint8 *alg5_values, uint8 *alg6_values, uint16 *rng_seed, uint16 *rng_forward_1,
             uint16 *rng_forward_128)
{
    __m512i lo = ((__m512i*)working_code)[0];
    __m512i hi = ((__m512i*)working_code)[1];

    if (alg_id == 0)
    {
        for (int j = 0; j < iterations; j++)
        {
            auto *rng = (__m512i*)(alg0_values + ((*rng_seed) * 128 * 2));

            lo = _mm512_add_epi8(lo, lo);
            hi = _mm512_add_epi8(hi, hi);
            lo = lo | rng[0];
            hi = hi | rng[1];

            *rng_seed = rng_forward_128[*rng_seed];
        }
    }
    else if (alg_id == 1)
    {
        for (int j = 0; j < iterations; j++)
        {
            auto *rng = (__m512i*)(regular_rng_values + ((*rng_seed) * 128 * 2));

            lo = _mm512_add_epi8(lo, rng[0]);
            hi = _mm512_add_epi8(hi, rng[1]);

            *rng_seed = rng_forward_128[*rng_seed];
        }
    }
    else if (alg_id == 2)
    {
        for (int j = 0; j < iterations; j++)
        {
            auto *rng = (__m512i*)(alg2_values + ((*rng_seed) * 128 * 2));

            __m512i even_lo = _mm512_slli_epi16(lo & mask_even, 1) & mask_even;
            __m512i even_hi = _mm512_slli_epi16(hi & mask_even, 1) & mask_even;
            __m512i odd_lo = _mm512_srli_epi16(lo & mask_odd, 1) & mask_odd;
            __m512i odd_hi = _mm512_srli_epi16(hi & mask_odd, 1) & mask_odd;

            __m512i carry_lo = _mm512_permutex2var_epi8(lo, carry_permutation, hi);
            __m512i carry_hi = _mm512_permutex2var_epi8(hi, carry_permutation, *rng);

            even_lo = even_lo | (carry_lo & carry_mask_l);
            even_hi = even_hi | (carry_hi & carry_mask_l);

            odd_lo = odd_lo | (carry_lo & carry_mask_r);
            odd_hi = odd_hi | (carry_hi & carry_mask_r);

            lo = even_lo | odd_lo;
            hi = even_hi | odd_hi;

            *rng_seed = rng_forward_1[*rng_seed];
        }
    }
    else if (alg_id == 3)
    {
        for (int j = 0; j < iterations; j++)
        {
            auto *rng = (__m512i*)(regular_rng_values + ((*rng_seed) * 128 * 2));

            lo = lo ^ rng[0];
            hi = hi ^ rng[1];

            *rng_seed = rng_forward_128[*rng_seed];
        }
    }
    else if (alg_id == 4)
    {
        for (int j = 0; j < iterations; j++)
        {
            auto *rng = (__m512i*)(regular_rng_values + ((*rng_seed) * 128 * 2));

            lo = _mm512_sub_epi8(lo, rng[0]);
            hi = _mm512_sub_epi8(hi, rng[1]);

            *rng_seed = rng_forward_128[*rng_seed];
        }
    }
    else if (alg_id == 5)
    {
        for (int j = 0; j < iterations; j++)
        {
            auto *rng = (__m512i*)(alg5_values + ((*rng_seed) * 128 * 2));

            __m512i even_lo = _mm512_srli_epi16(lo & mask_even, 1) & mask_even;
            __m512i even_hi = _mm512_srli_epi16(hi & mask_even, 1) & mask_even;
            __m512i odd_lo = _mm512_slli_epi16(lo & mask_odd, 1) & mask_odd;
            __m512i odd_hi = _mm512_slli_epi16(hi & mask_odd, 1) & mask_odd;

            __m512i carry_lo = _mm512_permutex2var_epi8(lo, carry_permutation, hi);
            __m512i carry_hi = _mm512_permutex2var_epi8(hi, carry_permutation, *rng);

            even_lo = even_lo | (carry_lo & carry_mask_r);
            even_hi = even_hi | (carry_hi & carry_mask_r);

            odd_lo = odd_lo | (carry_lo & carry_mask_l);
            odd_hi = odd_hi | (carry_hi & carry_mask_l);

            lo = even_lo | odd_lo;
            hi = even_hi | odd_hi;

            *rng_seed = rng_forward_1[*rng_seed];
        }
    }
    else if (alg_id == 6)
    {
        for (int j = 0; j < iterations; j++)
        {
            auto *rng = (__m512i*)(alg6_values + ((*rng_seed) * 128 * 2));

            lo = _mm512_srli_epi16(lo, 1);
            lo = lo & srl_mask;
            hi = _mm512_srli_epi16(hi, 1);
            hi = hi & srl_mask;
            lo = lo | rng[0];
            hi = hi | rng[1];

            *rng_seed = rng_forward_128[*rng_seed];
        }
    }
    else if (alg_id == 7)
    {
        for (int j = 0; j < iterations; j++)
        {
            lo = ~lo;
            hi = ~hi;
        }
    }

    ((__m512i*)working_code)[0] = lo;
    ((__m512i*)working_code)[1] = hi;
}

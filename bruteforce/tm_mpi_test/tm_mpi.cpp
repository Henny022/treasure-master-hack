#include "tm_mpi.h"
#include "../tm_mpi/implementation.h"

void run_alg(int alg_id, int iterations, uint8_t *working_code,
             rng_tables_t *rng_tables, uint16_t *rng_seed)
{
    __m512i lo = ((__m512i *)working_code)[0];
    __m512i hi = ((__m512i *)working_code)[1];

    switch (alg_id)
    {
    case 0:
        for (int i = 0; i < iterations; ++i)
        {
            lo = _mm512_add_epi8(lo, lo);
            hi = _mm512_add_epi8(hi, hi);
            lo = lo | rng_tables->alg0[*rng_seed][0];
            hi = hi | rng_tables->alg0[*rng_seed][1];
            *rng_seed = rng_tables->forward_128[*rng_seed];
        }
        break;
    case 1:
        for (int i = 0; i < iterations; ++i)
        {
            lo = _mm512_add_epi8(lo, rng_tables->regular[*rng_seed][0]);
            hi = _mm512_add_epi8(hi, rng_tables->regular[*rng_seed][1]);
            *rng_seed = rng_tables->forward_128[*rng_seed];
        }
        break;
    case 2:
    {
        for (int i = 0; i < iterations; ++i)
        {
            __m512i even_lo = _mm512_srli_epi16(lo & mask_even, 1) & mask_even;
            __m512i even_hi = _mm512_srli_epi16(hi & mask_even, 1) & mask_even;
            __m512i odd_lo = _mm512_slli_epi16(lo & mask_odd, 1) & mask_odd;
            __m512i odd_hi = _mm512_slli_epi16(hi & mask_odd, 1) & mask_odd;

            __m512i carry_lo =
                _mm512_permutex2var_epi8(lo, carry_permutation, hi);
            __m512i carry_hi = _mm512_permutex2var_epi8(
                hi, carry_permutation, rng_tables->alg2[*rng_seed]);

            even_lo = even_lo | (carry_lo & carry_mask_r & mask_even);
            even_hi = even_hi | (carry_hi & carry_mask_r & mask_even);

            odd_lo = odd_lo | (carry_lo & carry_mask_l & mask_odd);
            odd_hi = odd_hi | (carry_hi & carry_mask_l & mask_odd);

            lo = even_lo | odd_lo;
            hi = even_hi | odd_hi;

            *rng_seed = rng_tables->rng_table[*rng_seed];
        }
        break;
    }
    case 3:
        for (int i = 0; i < iterations; ++i)
        {
            lo = lo ^ rng_tables->regular[*rng_seed][0];
            hi = hi ^ rng_tables->regular[*rng_seed][1];
            *rng_seed = rng_tables->forward_128[*rng_seed];
        }
        break;
    case 4:
        for (int i = 0; i < iterations; ++i)
        {
            lo = _mm512_sub_epi8(lo, rng_tables->regular[*rng_seed][0]);
            hi = _mm512_sub_epi8(hi, rng_tables->regular[*rng_seed][1]);
            *rng_seed = rng_tables->forward_128[*rng_seed];
        }
        break;
    case 5:
    {
        for (int i = 0; i < iterations; ++i)
        {
            __m512i even_lo = _mm512_slli_epi16(lo & mask_even, 1) & mask_even;
            __m512i even_hi = _mm512_slli_epi16(hi & mask_even, 1) & mask_even;
            __m512i odd_lo = _mm512_srli_epi16(lo & mask_odd, 1) & mask_odd;
            __m512i odd_hi = _mm512_srli_epi16(hi & mask_odd, 1) & mask_odd;

            __m512i carry_lo =
                _mm512_permutex2var_epi8(lo, carry_permutation, hi);
            __m512i carry_hi = _mm512_permutex2var_epi8(
                hi, carry_permutation, rng_tables->alg5[*rng_seed]);

            even_lo = even_lo | (carry_lo & carry_mask_l & mask_even);
            even_hi = even_hi | (carry_hi & carry_mask_l & mask_even);

            odd_lo = odd_lo | (carry_lo & carry_mask_r & mask_odd);
            odd_hi = odd_hi | (carry_hi & carry_mask_r & mask_odd);

            lo = even_lo | odd_lo;
            hi = even_hi | odd_hi;
            *rng_seed = rng_tables->rng_table[*rng_seed];
        }
        break;
    }
    case 6:
        for (int i = 0; i < iterations; ++i)
        {
            lo = _mm512_srli_epi16(lo, 1);
            lo = lo & srl_mask;
            hi = _mm512_srli_epi16(hi, 1);
            hi = hi & srl_mask;
            lo = lo | rng_tables->alg6[*rng_seed][0];
            hi = hi | rng_tables->alg6[*rng_seed][1];
            *rng_seed = rng_tables->forward_128[*rng_seed];
        }
        break;
    case 7:
        for (int i = 0; i < iterations; ++i)
        {
            lo = ~lo;
            hi = ~hi;
        }
        break;
    default:
        break;
    }

    ((__m512i *)working_code)[0] = lo;
    ((__m512i *)working_code)[1] = hi;
}

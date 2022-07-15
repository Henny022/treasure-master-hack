#include <cstdio>
#include "implementation.h"
#include "rng.h"
#include "schedule.h"

union working_code_t
{
    uint8_t u8[128];
    __m512i zmm[2];
};

void run_once(const uint8_t IV[8],
              const std::array<key_schedule_entry, 27> &schedule_entries,
              const rng_tables_t &rng_tables)
{
    working_code_t working_code;

    for (int i = 0; i < 8; ++i)
    {
        working_code.u8[i] = IV[i];
    }

    uint16_t rng_seed = (working_code.u8[0] << 8) | working_code.u8[1];

    for (int i = 8; i < 128; ++i)
    {
        working_code.u8[i] =
            working_code.u8[i - 8] + run_rng(rng_seed, rng_tables.rng_table);
    }

    for (const auto &entry : schedule_entries)
    {
        rng_seed = entry.rng_seed;
        uint16_t nibble_selector = entry.nibble_selector;

        __m512i lo = working_code.zmm[0];
        __m512i hi = working_code.zmm[1];

        for (int i = 0; i < 16; ++i)
        {
            working_code.zmm[0] = lo;
            uint8_t current_byte = working_code.u8[i];
            if (nibble_selector & 0x8000)
            {
                current_byte = current_byte >> 4;
            }
            nibble_selector = nibble_selector << 1;

            auto algorithm = (current_byte >> 1) & 0x07;

            switch (algorithm)
            {
            case 0:
                working_code.zmm[0] = _mm512_add_epi8(lo, lo);
                hi = _mm512_add_epi8(hi, hi);
                lo = lo | rng_tables.alg0[rng_seed][0];
                hi = hi | rng_tables.alg0[rng_seed][1];
                rng_seed = rng_tables.forward_128[rng_seed];
                break;
            case 1:
                lo = _mm512_add_epi8(lo, rng_tables.regular[rng_seed][0]);
                hi = _mm512_add_epi8(hi, rng_tables.regular[rng_seed][1]);
                rng_seed = rng_tables.forward_128[rng_seed];
                break;
            case 2:
            {
                __m512i even_lo =
                    _mm512_srli_epi16(lo & mask_even, 1) & mask_even;
                __m512i even_hi =
                    _mm512_srli_epi16(hi & mask_even, 1) & mask_even;
                __m512i odd_lo = _mm512_slli_epi16(lo & mask_odd, 1) & mask_odd;
                __m512i odd_hi = _mm512_slli_epi16(hi & mask_odd, 1) & mask_odd;

                __m512i carry_lo =
                    _mm512_permutex2var_epi8(lo, carry_permutation, hi);
                __m512i carry_hi = _mm512_permutex2var_epi8(
                    hi, carry_permutation, rng_tables.alg2[rng_seed]);

                even_lo = even_lo | (carry_lo & carry_mask_r & mask_even);
                even_hi = even_hi | (carry_hi & carry_mask_r & mask_even);

                odd_lo = odd_lo | (carry_lo & carry_mask_l & mask_odd);
                odd_hi = odd_hi | (carry_hi & carry_mask_l & mask_odd);

                lo = even_lo | odd_lo;
                hi = even_hi | odd_hi;

                rng_seed = rng_tables.rng_table[rng_seed];
                break;
            }
            case 3:
                lo = lo ^ rng_tables.regular[rng_seed][0];
                hi = hi ^ rng_tables.regular[rng_seed][1];
                rng_seed = rng_tables.forward_128[rng_seed];
                break;
            case 4:
                lo = _mm512_sub_epi8(lo, rng_tables.regular[rng_seed][0]);
                hi = _mm512_sub_epi8(hi, rng_tables.regular[rng_seed][1]);
                rng_seed = rng_tables.forward_128[rng_seed];
                break;
            case 5:
            {
                __m512i even_lo =
                    _mm512_slli_epi16(lo & mask_even, 1) & mask_even;
                __m512i even_hi =
                    _mm512_slli_epi16(hi & mask_even, 1) & mask_even;
                __m512i odd_lo = _mm512_srli_epi16(lo & mask_odd, 1) & mask_odd;
                __m512i odd_hi = _mm512_srli_epi16(hi & mask_odd, 1) & mask_odd;

                __m512i carry_lo =
                    _mm512_permutex2var_epi8(lo, carry_permutation, hi);
                __m512i carry_hi = _mm512_permutex2var_epi8(
                    hi, carry_permutation, rng_tables.alg5[rng_seed]);

                even_lo = even_lo | (carry_lo & carry_mask_l & mask_even);
                even_hi = even_hi | (carry_hi & carry_mask_l & mask_even);

                odd_lo = odd_lo | (carry_lo & carry_mask_r & mask_odd);
                odd_hi = odd_hi | (carry_hi & carry_mask_r & mask_odd);

                lo = even_lo | odd_lo;
                hi = even_hi | odd_hi;
                rng_seed = rng_tables.rng_table[rng_seed];
                break;
            }
            case 6:
                lo = _mm512_srli_epi16(lo, 1);
                lo = lo & srl_mask;
                hi = _mm512_srli_epi16(hi, 1);
                hi = hi & srl_mask;
                lo = lo | rng_tables.alg6[rng_seed][0];
                hi = hi | rng_tables.alg6[rng_seed][1];
                rng_seed = rng_tables.forward_128[rng_seed];
                break;
            case 7:
                lo = ~lo;
                hi = ~hi;
                break;
            default:
                break;
            }
        }
        working_code.zmm[0] = lo;
        working_code.zmm[1] = hi;
    }
    // checksum result vector
    uint16_t sum = 0;
    for (unsigned char i : working_code.u8)
    {
        sum += i;
    }

    if (sum != 0x41D7)
    {
        return;
    }
    printf("good sum 1: %2x %2x %2x %2x %2x %2x %2x %2x", IV[0], IV[1], IV[2],
           IV[3], IV[4], IV[5], IV[6], IV[7]);
    // decrypt
    // checksum code
    // heuristics
}

void run(const uint8_t IV[8], const rng_tables_t &rng_tables)
{
    auto schedule_entries = generate_schedule(IV);

    for (int byte7 = 0; byte7 < 256; ++byte7)
    {
        for (int byte6 = 0; byte6 < 256; ++byte6)
        {
            for (int byte5 = 0; byte5 < 256; ++byte5)
            {
                uint8_t local_IV[8];
                for (int i = 0; i < 5; ++i)
                {
                    local_IV[i] = IV[i];
                }
                local_IV[5] = byte5;
                local_IV[6] = byte6;
                local_IV[7] = byte7;
                run_once(local_IV, schedule_entries, rng_tables);
            }
        }
    }
}

int main()
{
    auto rng_tables = generate_rng_tables();
    uint8_t IV[8]{0x2C, 0xA5, 0xB4, 0x2D, 0x00};
    run(IV, *rng_tables);
}
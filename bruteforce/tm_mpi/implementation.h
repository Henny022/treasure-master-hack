#ifndef BRUTEFORCE_IMPLEMENTATION_H
#define BRUTEFORCE_IMPLEMENTATION_H

#include <cstdint>
#include <immintrin.h>

static const __m512i sll_mask = _mm512_set1_epi8(0xFE);
static const __m512i srl_mask = _mm512_set1_epi8(0x7F);

static const __m512i mask_even = _mm512_set1_epi16(0x00ff);
static const __m512i mask_odd = _mm512_set1_epi16(0xff00);

static const __m512i carry_permutation = _mm512_set_epi8(
    0x40, 0x3f, 0x3e, 0x3d, 0x3c, 0x3b, 0x3a, 0x39, 0x38, 0x37, 0x36, 0x35,
    0x34, 0x33, 0x32, 0x31, 0x30, 0x2f, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x29,
    0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 0x1f, 0x1e, 0x1d,
    0x1c, 0x1b, 0x1a, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11,
    0x10, 0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06, 0x05,
    0x04, 0x03, 0x02, 0x01);

static const __m512i carry_mask_l = _mm512_set1_epi8(0x01);
static const __m512i carry_mask_r = _mm512_set1_epi8(0x80);

#endif // BRUTEFORCE_IMPLEMENTATION_H

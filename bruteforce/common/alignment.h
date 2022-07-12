#ifndef ALIGNMENT_H
#define ALIGNMENT_H
#include <cstdint>

#if defined(_MSC_VER)
#define ALIGNED(x) __declspec(align(x))
#else
#if defined(__GNUC__)
#define ALIGNED(x) __attribute__((aligned(x)))
#endif
#endif

// void * aligned_malloc(int byte_count, int align_size);
void *aligned_malloc(int byte_count, int align_size)
{
    uint8_t *new_array = new uint8_t[byte_count + align_size];
    int mod = ((uint64_t)new_array) % align_size;
    int remainder = align_size - mod;
    uint64_t result = (uint64_t)new_array + (uint64_t)remainder;
    return (void *)(result);
}

#endif // ALIGNMENT_H
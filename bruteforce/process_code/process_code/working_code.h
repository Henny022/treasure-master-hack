#ifndef WORKING_CODE_H
#define WORKING_CODE_H
#include <cstdint>
#include "key_schedule.h"
#include "rng.h"

class working_code
{
  public:
    // Seeded with 8 uint8_t values (4 key and 4 data bytes)
    working_code(uint8_t value[8]);

    // Backup the starting value for later
    uint8_t starting_value[8];

    // Store/retrieve the working code as different data sizes
    union
    {
        uint8_t as_uint8[128];
        uint16_t as_uint16[64];
        uint32_t as_uint32[32];
        uint64_t as_uint64[16];
    } working_code_data;

    RNG rng;

    void process_map_exit(uint8_t map_number,
                          key_schedule_entry schedule_entry);

    void process_working_code(uint8_t map_number,
                              key_schedule_entry schedule_entry);

    void working_code_algorithm(uint8_t algorithm_number, uint8_t map_number);

    void display_working_code();

    bool operator==(const working_code &other) const;
    bool operator<(const working_code &other) const;
};

#endif // WORKING_CODE_H
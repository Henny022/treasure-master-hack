#ifndef KEY_SCHEDULE_H
#define KEY_SCHEDULE_H
#include <cstdint>

typedef struct
{
    uint8_t rng1;
    uint8_t rng2;
    uint16_t nibble_selector;
} key_schedule_entry;

typedef union
{
    uint8_t as_uint8[4];
    uint16_t as_uint16[2];
    uint32_t as_uint32;
} key_schedule_data;

key_schedule_entry
generate_schedule_entry(uint8_t map, key_schedule_data *current_schedule_data,
                        uint8_t algorithm);
key_schedule_entry
generate_schedule_entry(uint8_t map, key_schedule_data *current_schedule_data);

void key_schedule_algorithm(uint8_t map,
                            key_schedule_data *current_schedule_data,
                            uint8_t algorithm);

void key_schedule_algorithm_0(uint8_t map,
                              key_schedule_data *current_schedule_data);
void key_schedule_algorithm_1(uint8_t map,
                              key_schedule_data *current_schedule_data);
void key_schedule_algorithm_2(uint8_t map,
                              key_schedule_data *current_schedule_data);
void key_schedule_algorithm_3(uint8_t map,
                              key_schedule_data *current_schedule_data);
void key_schedule_algorithm_4(uint8_t map,
                              key_schedule_data *current_schedule_data);
void key_schedule_algorithm_5(uint8_t map,
                              key_schedule_data *current_schedule_data);
void key_schedule_algorithm_6(uint8_t map,
                              key_schedule_data *current_schedule_data);
void key_schedule_algorithm_7(uint8_t map,
                              key_schedule_data *current_schedule_data);

#endif // KEY_SCHEDULE_H
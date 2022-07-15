#ifndef BRUTEFORCE_SCHEDULE_H
#define BRUTEFORCE_SCHEDULE_H

#include <array>
#include <cstdint>

struct key_schedule_entry
{
    uint16_t rng_seed;
    uint16_t nibble_selector;
};

static const int map_list[26] = {
    0x00, 0x02, 0x05, 0x04, 0x03, 0x1D, 0x1C, 0x1E, 0x1B,
    0x07, 0x08, 0x06, 0x09, 0x0C, 0x20, 0x21, 0x22, 0x23,
    0x24, 0x25, 0x26, 0x0E, 0x0F, 0x10, 0x12, 0x11,
};

static inline void key_schedule_algorithm_0(uint8_t map,
                                            uint8_t current_schedule_data[4])
{
    unsigned char temp = map ^ current_schedule_data[1];
    unsigned char carry = (((int)temp + current_schedule_data[0]) >> 8) & 0x01;
    temp = temp + current_schedule_data[0];
    unsigned char next_carry =
        (((int)temp - current_schedule_data[2] - (1 - carry)) < 0 ? 0 : 1);
    temp = temp - current_schedule_data[2] - (1 - carry);
    carry = next_carry;

    unsigned char rolling_sum = temp;

    for (char i = 3; i >= 0; i--)
    {
        unsigned char next_carry =
            (((int)rolling_sum + current_schedule_data[i] + carry) >> 8) & 0x01;
        rolling_sum += current_schedule_data[i] + carry;
        current_schedule_data[i] = rolling_sum;

        carry = next_carry;
    }
}

static inline void key_schedule_algorithm_1(uint8_t map,
                                            uint8_t current_schedule_data[4])
{
    unsigned char carry = 1;
    unsigned char rolling_sum = map;

    for (char i = 3; i >= 0; i--)
    {
        unsigned char next_carry =
            (((int)rolling_sum + current_schedule_data[i] + carry) >> 8) & 0x01;
        rolling_sum += current_schedule_data[i] + carry;
        current_schedule_data[i] = rolling_sum;

        carry = next_carry;
    }
}

static inline void key_schedule_algorithm_2(uint8_t map,
                                            uint8_t current_schedule_data[4])
{
    // Add the map number to the first byte
    current_schedule_data[0] += map;

    unsigned char temp[4];
    temp[0] = current_schedule_data[0];
    temp[1] = current_schedule_data[1];
    temp[2] = current_schedule_data[2];
    temp[3] = current_schedule_data[3];

    // Reverse the code:
    current_schedule_data[0] = temp[3];
    current_schedule_data[1] = temp[2];
    current_schedule_data[2] = temp[1];
    current_schedule_data[3] = temp[0];
}

static inline void key_schedule_algorithm_3(uint8_t map,
                                            uint8_t current_schedule_data[4])
{
    // Run alg 2 first
    key_schedule_algorithm_2(map, current_schedule_data);
    // display_code_backup(code_backup);
    //  Then alg 1
    key_schedule_algorithm_1(map, current_schedule_data);
}

void key_schedule_algorithm_4(uint8_t map, uint8_t current_schedule_data[4])
{
    // Run alg 2 first
    key_schedule_algorithm_2(map, current_schedule_data);
    // display_code_backup(code_backup);
    //  Then alg 1
    key_schedule_algorithm_0(map, current_schedule_data);
}

static inline void key_schedule_algorithm_5(uint8_t map,
                                            uint8_t current_schedule_data[4])
{
    // Do an ASL on the map number
    unsigned char temp = map << 1;

    // EOR #$FF
    temp = temp ^ 0xFF;
    temp = temp + current_schedule_data[0];
    temp = temp - map;
    current_schedule_data[0] = temp;

    unsigned char temp2[4];
    temp2[1] = current_schedule_data[1];
    temp2[2] = current_schedule_data[2];
    temp2[3] = current_schedule_data[3];

    current_schedule_data[1] = temp2[3];
    current_schedule_data[2] = temp2[1];
    current_schedule_data[3] = temp2[2];
}

static inline void key_schedule_algorithm_6(uint8_t map,
                                            uint8_t current_schedule_data[4])
{
    // Run alg 2 first
    key_schedule_algorithm_5(map, current_schedule_data);

    // Then alg 1
    key_schedule_algorithm_1(map, current_schedule_data);
}

static inline void key_schedule_algorithm_7(uint8_t map,
                                            uint8_t current_schedule_data[4])
{
    // Run alg 2 first
    key_schedule_algorithm_5(map, current_schedule_data);

    // Then alg 1
    key_schedule_algorithm_0(map, current_schedule_data);
}

static inline void key_schedule_algorithm(uint8_t map,
                                          uint8_t current_schedule_data[4],
                                          uint8_t algorithm)
{
    switch (algorithm)
    {
    case 0:
        key_schedule_algorithm_0(map, current_schedule_data);
        break;
    case 1:
        key_schedule_algorithm_1(map, current_schedule_data);
        break;
    case 2:
        key_schedule_algorithm_2(map, current_schedule_data);
        break;
    case 3:
        key_schedule_algorithm_3(map, current_schedule_data);
        break;
    case 4:
        key_schedule_algorithm_4(map, current_schedule_data);
        break;
    case 5:
        key_schedule_algorithm_5(map, current_schedule_data);
        break;
    case 6:
        key_schedule_algorithm_6(map, current_schedule_data);
        break;
    case 7:
        key_schedule_algorithm_7(map, current_schedule_data);
        break;
    default:
        break;
    }
}

static inline key_schedule_entry
generate_schedule_entry(uint8_t map, uint8_t current_schedule_data[4],
                        uint8_t algorithm)
{
    key_schedule_algorithm(map, current_schedule_data, algorithm);

    key_schedule_entry result;
    result.rng_seed =
        (current_schedule_data[0] << 8) | current_schedule_data[1];
    result.nibble_selector =
        (current_schedule_data[3] << 8) | current_schedule_data[2];

    return result;
}

static inline key_schedule_entry
generate_schedule_entry(uint8_t map, uint8_t current_schedule_data[4])
{
    unsigned char algorithm_number;

    // Special case for 0x1B
    if (map == 0x1B)
    {
        algorithm_number = 6;
        generate_schedule_entry(map, current_schedule_data, algorithm_number);
    }

    // Special case
    if (map == 0x06)
    {
        algorithm_number = 0;
    }
    else
    {
        algorithm_number =
            (current_schedule_data[(map >> 4) & 0x03] >> 2) & 0x07;
    }

    return generate_schedule_entry(map, current_schedule_data,
                                   algorithm_number);
}

static inline std::array<key_schedule_entry, 27>
generate_schedule(const uint8_t IV[8])
{
    uint8_t schedule_data[4];
    for (int i = 0; i < 4; ++i)
    {
        schedule_data[i] = IV[i];
    }
    std::array<key_schedule_entry, 27> schedule_entries{};

    int schedule_counter = 0;
    for (int map : map_list)
    {
        schedule_entries[schedule_counter++] =
            generate_schedule_entry(map, schedule_data);

        if (map == 0x22)
        {
            schedule_entries[schedule_counter++] =
                generate_schedule_entry(map, schedule_data, 4);
        }
    }
    return schedule_entries;
}

#endif // BRUTEFORCE_SCHEDULE_H

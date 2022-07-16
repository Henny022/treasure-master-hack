#ifndef VERIFY_H
#define VERIFY_H
#include <cstdint>

#define OP_JAM 0x01
#define OP_ILLEGAL 0x02
#define OP_NOP2 0x04
#define OP_NOP 0x08
#define OP_JUMP 0x10

extern const uint8_t carnival_world_working_code[];
extern const uint8_t carnival_code_decrypted_machine_code[];

extern const int carnival_code_length;
extern const uint8_t carnival_code[];

extern const int other_world_code_length;
extern const uint8_t other_world_code[];

extern const uint8_t opcode_bytes_used[];
extern const uint8_t opcode_type[];

uint8_t *decrypt_memory(const uint8_t *working_code, const uint8_t *memory,
                        int length);
uint8_t *encrypt_memory(const uint8_t *block, const uint8_t *xor_block,
                        int length);
bool verify_checksum(const uint8_t *memory, int length);

bool compare_working_code(const uint8_t *block1, const uint8_t *block2);

struct machine_code_properties
{
    bool first_byte_is_valid;
    bool first_bytes_to_jump_valid;
    bool all_bytes_valid;

    bool uses_illegal_opcodes;
    bool uses_nop;
    bool uses_unofficial_nops;
    bool uses_jam;

    machine_code_properties()
        : first_byte_is_valid(false), first_bytes_to_jump_valid(false),
          all_bytes_valid(false), uses_illegal_opcodes(false), uses_nop(false),
          uses_unofficial_nops(false), uses_jam(false)
    {
    }
};

machine_code_properties check_machine_code(const uint8_t *memory, int length);

void output_stats(const uint8_t in_progress[128], const uint8_t IV[8]);
void output_machine_code_stats(const uint8_t *decrypted_memory, int length);

#endif // VERIFY_H
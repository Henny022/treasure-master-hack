#include "verify.h"
#include <cstdint>
#include <cstdio>

const uint8_t carnival_world_working_code[0x80] = {
    0xFD, 0x22, 0x3C, 0x40, 0x77, 0xEB, 0xD4, 0xEF, 0x9C, 0x44, 0x93, 0x1C,
    0xD7, 0xF8, 0x10, 0x97, 0x14, 0x93, 0x84, 0x22, 0xDD, 0xE3, 0x3E, 0x77,
    0x5C, 0x47, 0x11, 0x31, 0xAA, 0xD9, 0xF1, 0x97, 0xE2, 0x44, 0x4E, 0x78,
    0x05, 0x25, 0xCD, 0xBF, 0xAE, 0xED, 0xCA, 0xD6, 0x1F, 0xD9, 0x30, 0x4D,
    0x88, 0x18, 0xB2, 0x89, 0xF6, 0x70, 0x43, 0xFE, 0x56, 0x3E, 0xF3, 0x1B,
    0x7C, 0xA0, 0xF7, 0xF8, 0xDF, 0xF5, 0x3C, 0xC7, 0xE9, 0xD5, 0x24, 0x0E,
    0xDA, 0xA9, 0xB0, 0xAA, 0x86, 0x51, 0x1F, 0x8F, 0x4A, 0xEF, 0x8C, 0x81,
    0xF8, 0x80, 0x4F, 0x8F, 0x54, 0xF2, 0x8C, 0x14, 0x9C, 0xFA, 0xFE, 0xCF,
    0x03, 0x82, 0x96, 0x4E, 0x82, 0x4C, 0x4A, 0x72, 0x1C, 0x52, 0x2C, 0xDE,
    0x0F, 0x94, 0x58, 0xC2, 0xD6, 0x99, 0x36, 0x7F, 0xA3, 0xF0, 0xD1, 0x29,
    0xD0, 0x93, 0xBF, 0x42, 0xCF, 0x3D, 0xD2, 0x56};

const uint8_t carnival_code_decrypted_machine_code[0x80] = {
    0xA2, 0x05, 0xEC, 0x51, 0x04, 0xF0, 0x03, 0x20, 0x88, 0xED, 0xA9, 0x00,
    0x85, 0x3F, 0xA5, 0xFC, 0xC9, 0x02, 0xD0, 0x14, 0xA0, 0x0F, 0x20, 0x7F,
    0xAF, 0xB0, 0x0D, 0xA5, 0xD4, 0xD0, 0x09, 0xAD, 0x68, 0x05, 0x18, 0x69,
    0x10, 0x8D, 0x68, 0x05, 0x4C, 0x35, 0xB5, 0xA0, 0x00, 0x20, 0xB6, 0x88,
    0x4C, 0x35, 0xB5, 0xA0, 0x01, 0x20, 0xB6, 0x88, 0x8A, 0xF0, 0x20, 0xA0,
    0x02, 0xDD, 0xA0, 0x03, 0x20, 0xB6, 0x88, 0xAD, 0x58, 0x05, 0xC9, 0xF0,
    0x90, 0x11, 0xA2, 0x12, 0xBD, 0x8B, 0xB9, 0x9D, 0x57, 0x01, 0xCA, 0x10,
    0xF7, 0x20, 0x52, 0x89, 0x4C, 0xEE, 0x81, 0xA5, 0x48, 0x29, 0x07, 0xD0,
    0x0C, 0xAD, 0x0B, 0x01, 0xAE, 0x0A, 0x01, 0x8E, 0x0B, 0x01, 0x8D, 0x0A,
    0x01, 0x4C, 0x35, 0xB5, 0xC9, 0x2D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const int carnival_code_length = 0x72;
const uint8_t carnival_code[0x72] = {
    0xF4, 0xD7, 0xD1, 0x9E, 0x46, 0x4F, 0x90, 0xF0, 0xA1, 0x3C, 0x59, 0xA3,
    0xFA, 0x09, 0x3C, 0x2A, 0x0B, 0x5A, 0x44, 0x1B, 0x7E, 0x23, 0x72, 0x63,
    0xDD, 0xFA, 0x41, 0x27, 0x9A, 0x46, 0x8B, 0xAE, 0xA7, 0xFB, 0xE2, 0xF5,
    0x04, 0x01, 0x9A, 0x51, 0xC3, 0x7A, 0x35, 0x58, 0x81, 0xAC, 0x59, 0xC2,
    0xC3, 0x2A, 0xE4, 0x26, 0xAB, 0x90, 0x1F, 0x52, 0x84, 0xD4, 0xF5, 0x49,
    0xC5, 0xE1, 0x55, 0xDC, 0xD8, 0x41, 0x28, 0xD1, 0x43, 0xF6, 0xF7, 0xA6,
    0x6E, 0x52, 0xD2, 0xE4, 0x34, 0x39, 0xA1, 0x15, 0x1A, 0x31, 0x13, 0x0F,
    0x21, 0xEA, 0xBF, 0x27, 0xF3, 0x23, 0xA4, 0xA0, 0x30, 0x67, 0x43, 0x32,
    0x9B, 0x5C, 0xD2, 0xAB, 0x9F, 0x1B, 0x46, 0xD2, 0x7C, 0x3F, 0x6E, 0xD7,
    0x23, 0xC8, 0xA6, 0xA1, 0x5E, 0x3D};

const int other_world_code_length = 0x53;
const uint8_t other_world_code[0x53] = {
    0x50, 0xF1, 0xFB, 0x44, 0xBD, 0xC1, 0xB1, 0x5E, 0xE4, 0x18, 0x03, 0x52,
    0x1A, 0x1C, 0x93, 0x36, 0x6E, 0x2D, 0x2B, 0x2B, 0xB9, 0x5A, 0xA1, 0x58,
    0x7B, 0x32, 0xDB, 0x9A, 0xA3, 0x49, 0x40, 0x12, 0x06, 0x9C, 0xBB, 0x49,
    0xAE, 0xB3, 0xFF, 0x67, 0xF0, 0xD2, 0x8F, 0x6E, 0x45, 0xB7, 0xE5, 0x9A,
    0x80, 0xAB, 0xFF, 0xD3, 0x98, 0x9A, 0x94, 0x0A, 0x72, 0x81, 0xCF, 0x0A,
    0xFF, 0xFB, 0x54, 0xD9, 0x0C, 0xE3, 0x22, 0xF1, 0xE2, 0xD2, 0xF4, 0xC7,
    0x86, 0x81, 0x90, 0x0B, 0x04, 0xD2, 0x44, 0x66, 0xC1, 0x68, 0xCA};

const uint8_t opcode_bytes_used[0x100] = {
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0, 2, 2, 0, 0, 2, 2, 2, 0,
    1, 3, 1, 0, 2, 3, 3, 0, 3, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 2, 3, 3, 0, 1, 2, 0, 0, 2, 2, 2, 0,
    1, 2, 1, 0, 3, 3, 3, 0, 2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 2, 3, 3, 0,
    1, 2, 0, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0, 2, 2, 0, 0, 2, 2, 2, 0,
    1, 3, 1, 0, 2, 3, 3, 0, 2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 0, 3, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0,
    1, 2, 1, 0, 3, 3, 3, 0, 2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 3, 3, 3, 0,
    2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0, 2, 2, 0, 0, 2, 2, 2, 0,
    1, 3, 1, 0, 2, 3, 3, 0, 2, 2, 2, 0, 2, 2, 2, 0, 1, 2, 1, 0, 3, 3, 3, 0,
    2, 2, 0, 0, 2, 2, 2, 0, 1, 3, 1, 0, 2, 3, 3, 0};

const uint8_t opcode_type[0x100] = {
    0,          0,          OP_JAM,     OP_ILLEGAL, OP_NOP2, 0,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    OP_NOP2,    0,          0,          OP_ILLEGAL, OP_JUMP, 0,
    OP_JAM,     OP_ILLEGAL, OP_NOP2,    0,          0,       OP_ILLEGAL,
    0,          0,          OP_NOP2,    OP_ILLEGAL, OP_NOP2, 0,
    0,          OP_ILLEGAL, OP_JUMP,    0,          OP_JAM,  OP_ILLEGAL,
    0,          0,          0,          OP_ILLEGAL, 0,       0,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    OP_JUMP,    0,          OP_JAM,     OP_ILLEGAL, OP_NOP2, 0,
    0,          OP_ILLEGAL, 0,          0,          OP_NOP2, OP_ILLEGAL,
    OP_NOP2,    0,          0,          OP_ILLEGAL, OP_JUMP, 0,
    OP_JAM,     OP_ILLEGAL, OP_NOP2,    0,          0,       OP_ILLEGAL,
    0,          0,          0,          OP_ILLEGAL, OP_JUMP, 0,
    0,          OP_ILLEGAL, OP_JUMP,    0,          OP_JAM,  OP_ILLEGAL,
    OP_NOP2,    0,          0,          OP_ILLEGAL, 0,       0,
    OP_NOP2,    OP_ILLEGAL, OP_NOP2,    0,          0,       OP_ILLEGAL,
    OP_JUMP,    0,          OP_JAM,     OP_ILLEGAL, OP_NOP2, 0,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    OP_JUMP,    0,          0,          OP_ILLEGAL, OP_JUMP, 0,
    OP_JAM,     OP_ILLEGAL, OP_NOP2,    0,          0,       OP_ILLEGAL,
    0,          0,          OP_NOP2,    OP_ILLEGAL, OP_NOP2, 0,
    0,          OP_ILLEGAL, OP_NOP2,    0,          OP_NOP2, OP_ILLEGAL,
    0,          0,          0,          OP_ILLEGAL, 0,       OP_NOP2,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    OP_JUMP,    0,          OP_JAM,     OP_ILLEGAL, 0,       0,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    OP_ILLEGAL, 0,          OP_ILLEGAL, OP_ILLEGAL, 0,       0,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    0,          0,          0,          OP_ILLEGAL, 0,       0,
    0,          OP_ILLEGAL, OP_JUMP,    0,          OP_JAM,  OP_ILLEGAL,
    0,          0,          0,          OP_ILLEGAL, 0,       0,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    0,          0,          OP_NOP2,    OP_ILLEGAL, 0,       0,
    0,          OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    0,          0,          0,          OP_ILLEGAL, OP_JUMP, 0,
    OP_JAM,     OP_ILLEGAL, OP_NOP2,    0,          0,       OP_ILLEGAL,
    0,          0,          OP_NOP2,    OP_ILLEGAL, OP_NOP2, 0,
    0,          OP_ILLEGAL, 0,          0,          OP_NOP2, OP_ILLEGAL,
    0,          0,          0,          OP_ILLEGAL, 0,       0,
    OP_NOP,     OP_ILLEGAL, 0,          0,          0,       OP_ILLEGAL,
    OP_JUMP,    0,          OP_JAM,     OP_ILLEGAL, OP_NOP2, 0,
    0,          OP_ILLEGAL, 0,          0,          OP_NOP2, OP_ILLEGAL,
    OP_NOP2,    0,          0,          OP_ILLEGAL};

uint8_t *decrypt_memory(const uint8_t working_code[128],
                        const uint8_t *encrypted_memory, int length)
{
    auto *decrypted_memory = new uint8_t[128];
    for (int i = 0; i < length; i++)
    {
        decrypted_memory[i] = encrypted_memory[i] ^ working_code[127 - i];
    }

    for (int i = length; i < 128; i++)
    {
        decrypted_memory[i] = 0;
    }

    return decrypted_memory;
}

uint8_t *encrypt_memory(const uint8_t *block, const uint8_t *xor_block,
                        int length)
{
    // Swap the block around
    uint8_t swapped[0x80];
    for (int i = 0; i < 128; i++)
    {
        swapped[i] = block[127 - i];
    }

    // Get the checkum value needed
    uint16_t sum = 0;
    for (int i = 0; i < length - 2; i++)
    {
        sum += block[i];
    }

    swapped[128 - length] = (sum >> 8) & 0xFF;
    swapped[128 - length + 1] = sum & 0xFF;

    uint8_t *encrypted_memory =
        decrypt_memory(swapped, other_world_code, other_world_code_length);

    return encrypted_memory;
}

bool verify_checksum(const uint8_t *memory, int length)
{
    // TODO: idea: if memory[length-1] > (((length-2) * 0xFF) >> 8) then
    // immediate failure. Checkum value is too big

    uint16_t sum = 0;
    for (int i = 0; i < length - 2; i++)
    {
        sum += memory[i];
    }

    return (memory[length - 1] == ((sum >> 8) & 0xFF)) &&
           (memory[length - 2] == (sum & 0xFF));
}

bool compare_working_code(const uint8_t block1[128], const uint8_t block2[128])
{
    for (int i = 0; i < 128; i++)
    {
        if (block1[i] != block2[i])
            return false;
    }

    return true;
}

machine_code_properties check_machine_code(const uint8_t *memory, int length)
{
    // check for JAM (immediate failure)
    // check for illegal opcodes (immediate failure)
    // check for NOP
    // Is the first section, up to the first jump of any kind, valid machine
    // code? is the whole chunk (except for checksum value) valid machine code?
    // (later) do alyosha's jump-in points line up?

    machine_code_properties result;

    bool first_jump_found = false;

    for (int i = 0; i < length - 2; i++)
    {
        if (opcode_type[memory[i]] & OP_JAM)
        {
            result.uses_jam = true;
            break;
        }
        else if (opcode_type[memory[i]] & OP_ILLEGAL)
        {
            result.uses_illegal_opcodes = true;
            break;
        }
        else if (opcode_type[memory[i]] & OP_NOP2)
        {
            result.uses_unofficial_nops = true;
        }
        else if (opcode_type[memory[i]] & OP_NOP)
        {
            result.uses_nop = true;
        }
        else if (opcode_type[memory[i]] & OP_JUMP && !first_jump_found)
        {
            result.first_bytes_to_jump_valid = true;
            first_jump_found = true;
        }

        if (i == 0)
        {
            result.first_byte_is_valid = true;
        }

        i += opcode_bytes_used[memory[i]] - 1;
    }

    if (!result.uses_illegal_opcodes && !result.uses_jam)
    {
        result.all_bytes_valid = true;
    }

    return result;
}

void output_stats(const uint8_t in_progress[128], const uint8_t IV[8])
{
    char output[123 + 20]; // 20 extra byte in case I misscounted
    output[0] = ',';
    uint8_t *decrypted_memory =
        decrypt_memory(in_progress, carnival_code, carnival_code_length);
    bool carnival_world_passed = false;
    bool other_world_passed = false;

    if (verify_checksum(decrypted_memory, carnival_code_length))
    {
        carnival_world_passed = true;
        sprintf(output + 1, "%02X%02X%02X%02X%02X%02X%02X%02X,", IV[0], IV[1],
                IV[2], IV[3], IV[4], IV[5], IV[6], IV[7]);

        sprintf(output + 18, "car,");

        if (compare_working_code(in_progress, carnival_world_working_code))
        {
            sprintf(output + 22, "wcm  ,");
        }
        else
        {
            sprintf(output + 22, "     ,");
        }

        if (compare_working_code(decrypted_memory,
                                 carnival_code_decrypted_machine_code))
        {
            sprintf(output + 28, "mcm  ,");
        }
        else
        {
            sprintf(output + 28, "     ,");
        }

        output_machine_code_stats(decrypted_memory, carnival_code_length,
                                  output + 34);
    }
    delete[] decrypted_memory;

    decrypted_memory =
        decrypt_memory(in_progress, other_world_code, other_world_code_length);
    if (verify_checksum(decrypted_memory, other_world_code_length))
    {
        other_world_passed = true;

        if (!carnival_world_passed)
        {
            sprintf(output + 1,
                    "%02X%02X%02X%02X%02X%02X%02X%02X                          "
                    "                                  ",
                    IV[0], IV[1], IV[2], IV[3], IV[4], IV[5], IV[6], IV[7]);
        }
        sprintf(output + 76, "oth,");

        output_machine_code_stats(decrypted_memory, other_world_code_length,
                                  output + 80);
    }
    delete[] decrypted_memory;

    if (carnival_world_passed || other_world_passed)
    {
        printf("%s\n", output);
    }
}

void output_machine_code_stats(const uint8_t *decrypted_memory, int length,
                               char *output)
{
    machine_code_properties machine_code_stats =
        check_machine_code(decrypted_memory, length);
    if (machine_code_stats.all_bytes_valid)
    {
        sprintf(output, "ABV! ,");
    }
    else
    {
        sprintf(output, "     ,");
    }

    if (machine_code_stats.first_bytes_to_jump_valid)
    {
        sprintf(output + 6, "TJ   ,");
    }
    else
    {
        sprintf(output + 6, "     ,");
    }

    if (machine_code_stats.first_byte_is_valid)
    {
        sprintf(output + 12, "FB   ,");
    }
    else
    {
        sprintf(output + 12, "     ,");
    }

    if (machine_code_stats.uses_illegal_opcodes)
    {
        sprintf(output + 18, "ILL  ,");
    }
    else
    {
        sprintf(output + 18, "     ,");
    }

    if (machine_code_stats.uses_jam)
    {
        sprintf(output + 24, "JAM  ,");
    }
    else
    {
        sprintf(output + 24, "     ,");
    }

    if (machine_code_stats.uses_nop)
    {
        sprintf(output + 30, "NOP  ,");
    }
    else
    {
        sprintf(output + 30, "     ,");
    }

    if (machine_code_stats.uses_unofficial_nops)
    {
        sprintf(output + 36, "NP2  ,");
    }
    else
    {
        sprintf(output + 36, "     ,");
    }
}
/**
 * Dynamixel Support Library
 *
 * Based on http://support.robotis.com/en/product/dynamixel_pro/communication/instruction_status_packet.htm
 * http://support.robotis.com/en/techsupport_eng.htm#product/dynamixel2/communication/xl-320.htm
 * http://www.trossenrobotics.com/dynamixel-xl-320-robot-actuator
 *
 */


#include "dynamixel.hpp"

#include <stdlib.h>
#include <stdint.h>

#define MAX_PARAMS      16
#define HEADER_SIZE     (sizeof(struct dynamixel_header_s))
#define CRC_SIZE        2
#define PACKET_OVERHEAD (HEADER_SIZE + CRC_SIZE)
#define MINIMUM_LENGTH  11


extern "C" {

    /**
     * Dynamixel base packet structure
     * This depends on the architecture being little endian.
     */
    struct dynamixel_header_s {
        uint8_t header[3];                  //!< Always 0xFF, 0xFF, 0xFD for Protocol 2.0
        uint8_t reserved;
        uint8_t id;                         //!< Dynamixel ID, 0xFE for broadcast
        uint16_t len;                       //!< Length following packet id field
        uint8_t instruction;                //!< Instruction to effect
    } __attribute((packed));

    typedef struct dynamixel_header_s dynamixel_header_t;

    struct dynamixel_instruction_ping_s {
    } __attribute((packed));

    struct dynamixel_instruction_s {
        union {
            struct dynamixel_instruction_ping_s ping;

        };
    } __attribute((packed));

    struct dynamixel_status_ping_s {
        uint16_t model;
        uint8_t firmware;
    } __attribute((packed));

    struct dynamixel_status_s {
        uint8_t error;
        union {
            struct dynamixel_status_ping_s ping;

        };
    } __attribute((packed));

    struct dynamixel_message_s {
        struct dynamixel_header_s;
        union {
            struct dynamixel_instruction_s instruction;
            struct dynamixel_status_s status;
        };
        uint16_t crc;
    };

    enum {
        PKT_INDEX_HEADER0 = 0,
        PKT_INDEX_HEADER1 = 1,
        PKT_INDEX_HEADER2 = 2,
        PKT_INDEX_RESERVED = 3,
        PKT_INDEX_ID = 4,
        PKT_INDEX_LENGTH_L = 5,
        PKT_INDEX_LENGTH_H = 6,
        PKT_INDEX_INSTRUCTION = 7,
    } pkt_index_e;

}

namespace Dynamixel
{

#define CRC16 0x8005

uint16_t ComputeCRC(uint16_t size, uint8_t *data)
{
    uint16_t out = 0;
    int bits_read = 0, bit_flag;

    /* Sanity check: */
    if (data == NULL)
        return 0;

    while (size > 0) {
        bit_flag = out >> 15;

        /* Get next bit: */
        out <<= 1;
        out |= (*data >> (7 - bits_read)) & 1;

        /* Increment bit counter: */
        bits_read++;
        if (bits_read > 7) {
            bits_read = 0;
            data++;
            size--;
        }

        /* Cycle check: */
        if (bit_flag)
            out ^= CRC16;

    }
    return out;
}

int Manager::BuildPacket(uint8_t id, uint8_t instruction, uint8_t param_count, uint8_t *params,
    uint8_t max_len, uint8_t* length, uint8_t* packet)
{

    // Check we have enough space to build the packet
    if((PACKET_OVERHEAD + param_count) > max_len) {
        return ERRNUM_DATA_LENGTH;
    }

    uint16_t packet_length = 1 + param_count + CRC_SIZE;
    *length = HEADER_SIZE + param_count + CRC_SIZE;

    // Build header
    packet[PKT_INDEX_HEADER0] = 0xFF;
    packet[PKT_INDEX_HEADER1] = 0xFF;
    packet[PKT_INDEX_HEADER2] = 0xFD;
    packet[PKT_INDEX_RESERVED] = 0x00;
    packet[PKT_INDEX_ID] = id;
    packet[PKT_INDEX_LENGTH_L] = packet_length & 0xFF;
    packet[PKT_INDEX_LENGTH_H] = (packet_length >> 8) & 0xFF;

    // Set instruction
    packet[PKT_INDEX_INSTRUCTION] = instruction;

    // Load params
    for (int i = 0; i < param_count; i++) {
        packet[HEADER_SIZE + i] = params[i];
    }

    // Compute CRC
    uint16_t crc = ComputeCRC(HEADER_SIZE + param_count, packet);

    packet[HEADER_SIZE + param_count] = crc & 0xFF;
    packet[HEADER_SIZE + param_count + 1] = (crc >> 8) & 0xFF;

    return 0;
}

int ParseStatusPacket(uint8_t length, uint8_t* packet, uint8_t *id, uint8_t *instruction, 
    uint8_t max_params, uint8_t *param_count, uint8_t *params)
{
    // Check for header match
    if ((packet[0] != 0xFF) | (packet[0] != 0xFF) | (packet[0] != 0xFD)) {
        return -1;
    }

    // Parse header into c struct
    struct dynamixel_header_s *header = (struct dynamixel_header_s*) packet;

    // Check CRC
    uint16_t crc = ComputeCRC(length, packet);

    // Read components
    uint16_t pkt_length     = header->len;
    uint8_t error           = packet[HEADER_SIZE];

    *id              = header->id;
    *instruction     = header->instruction;

    // Return error response from servo
    if ((error & 0x80) != 0) {
        return -(error & ~0x80);
    }

    // TODO: parse message

}

}


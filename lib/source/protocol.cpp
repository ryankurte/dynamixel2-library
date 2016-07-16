
#include "dynamixel/protocol.hpp"

#include <stdint.h>
#include <stdlib.h>

#include "dynamixel/dynamixel_defs.h"
#include "dynamixel/dynamixel_proto.h"

namespace Dynamixel
{

uint16_t Protocol::ComputeCRC(uint16_t length, uint8_t *data)
{
    uint16_t i, j;
    uint16_t crc_accum = 0;
    uint16_t crc_table[256] = {
        0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
        0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
        0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
        0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
        0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
        0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
        0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
        0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
        0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
        0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
        0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
        0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
        0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
        0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
        0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
        0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
        0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
        0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
        0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
        0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
        0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
        0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
        0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
        0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
        0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
        0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
        0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
        0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
        0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
        0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
        0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
        0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
    };

    for (j = 0; j < length; j++) {
        i = ((uint16_t)(crc_accum >> 8) ^ data[j]) & 0xFF;
        crc_accum = (crc_accum << 8) ^ crc_table[i];
    }

    return crc_accum;
}

int Protocol::BuildPing(uint8_t id, uint8_t max_len, uint8_t* length, uint8_t* packet)
{
    return Protocol::BuildPacket(id, DX_INSTR_PING, 0, NULL, max_len, length, packet);
}

int Protocol::ParsePingResponse(uint8_t length, uint8_t* packet, uint8_t* error,
                                uint8_t *id, uint16_t *model, uint8_t* firmware)
{
    uint8_t data[4];
    uint8_t param_count;
    int res;

    res = Protocol::ParseStatusPacket(length, packet, id, error,
                                      sizeof(data), &param_count, data);

    if ((res >= 0) && (param_count == 3)) {
        *model = (data[0] << 8) | data[1];
        *firmware = data[2];
    }

    return res;
}



int Protocol::BuildWrite(uint8_t id, uint16_t addr, uint8_t data_count, uint8_t* data,
                         uint8_t max_len, uint8_t* length, uint8_t* packet)
{

    uint8_t packed_data[data_count + 2];

    // Pack data with reg address (LSB first)
    packed_data[0] = addr & 0xFF;
    packed_data[1] = (addr >> 8) & 0xFF;

    for (int i = 0; i < data_count; i++) {
        packed_data[i + 2] = data[i];
    }

    return Protocol::BuildPacket(id, DX_INSTR_WRITE, data_count + 2, packed_data, max_len, length, packet);
}

int Protocol::BuildPacket(uint8_t id, uint8_t instruction, uint8_t param_count, uint8_t *params,
                          uint8_t max_len, uint8_t* length, uint8_t* packet)
{

    // Check we have enough space to build the packet
    if ((PACKET_OVERHEAD + param_count) > max_len) {
        return DX_ERRNUM_DATA_LENGTH;
    }

    uint16_t packet_length = 1 + param_count + CRC_SIZE;
    *length = HEADER_SIZE + packet_length;

    // Build header
    packet[PKT_INDEX_HEADER0] = 0xFF;
    packet[PKT_INDEX_HEADER1] = 0xFF;
    packet[PKT_INDEX_HEADER2] = 0xFD;
    packet[PKT_INDEX_RESERVED] = 0x00;
    packet[PKT_INDEX_ID] = id;
    packet[PKT_INDEX_LENGTH_L] = packet_length & 0xFF;
    packet[PKT_INDEX_LENGTH_H] = (packet_length >> 8) & 0xFF;

    // Set instruction (header + 1)
    packet[PKT_INDEX_INSTRUCTION] = instruction;

    // Load params
    for (int i = 0; i < param_count; i++) {
        packet[HEADER_SIZE + i + 1] = params[i];
    }

    // Compute CRC
    uint16_t crc = Protocol::ComputeCRC(HEADER_SIZE + param_count + 1, packet);

    packet[HEADER_SIZE + param_count + 1] = crc & 0xFF;
    packet[HEADER_SIZE + param_count + 2] = (crc >> 8) & 0xFF;

    return 0;
}

int Protocol::ParseStatusPacket(uint8_t length, uint8_t* packet, uint8_t *id, uint8_t* error,
                                uint8_t max_params, uint8_t *param_count, uint8_t *params)
{
    // Check for header match
    if ((packet[0] != 0xFF) | (packet[1] != 0xFF) | (packet[2] != 0xFD)) {
        return -1;
    }

    // Check CRC across whole packet
    uint16_t crc = (packet[length - 1] << 8) | packet[length - 2];
    uint16_t crc_check = ComputeCRC(length - CRC_SIZE, packet);

    if (crc != crc_check) {
        return -2;  //TODO ERROR_CRC
    }

    // Fetch packet length
    int packet_length = ((uint16_t)packet[PKT_INDEX_LENGTH_H] << 8) | packet[PKT_INDEX_LENGTH_L];

    //TODO: check for packet length mismatch

    if (packet[PKT_INDEX_INSTRUCTION] != 0x55) {
        return -3; // TODO: error, not a status packet
    }

    *id = packet[PKT_INDEX_ID];
    *error = packet[HEADER_SIZE + 1];

    *param_count = packet_length - CRC_SIZE - 2;

    if (*param_count > max_params) {
        return -4; // TODO: error too many params
    }

    for (int i = 0; i < *param_count; i++) {
        params[i] = packet[HEADER_SIZE + 2 + i];
    }

    //*instruction     = header->instruction;
#if 0
    // Return error response from servo
    if ((error & 0x80) != 0) {
        return -(error & ~0x80);
    }
#endif
    // TODO: parse message

    return 0;

}

}


#ifndef DYNAMIXEL_PROTO_H
#define DYNAMIXEL_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_PARAMS      16
#define HEADER_SIZE     (sizeof(struct dynamixel_header_s))
#define CRC_SIZE        2
#define PACKET_OVERHEAD (HEADER_SIZE + CRC_SIZE)
#define MINIMUM_LENGTH  11

/**
 * Dynamixel base packet structure
 * This depends on the architecture being little endian.
 */
struct dynamixel_header_s {
    uint8_t header[3];                  //!< Always 0xFF, 0xFF, 0xFD for Protocol 2.0
    uint8_t reserved;
    uint8_t id;                         //!< Dynamixel ID, 0xFE for broadcast
    uint16_t len;                       //!< Length following packet id field
} __attribute((packed));

typedef struct dynamixel_header_s dynamixel_header_t;

enum pkt_index_e {
    PKT_INDEX_HEADER0       = 0,
    PKT_INDEX_HEADER1       = 1,
    PKT_INDEX_HEADER2       = 2,
    PKT_INDEX_RESERVED      = 3,
    PKT_INDEX_ID            = 4,
    PKT_INDEX_LENGTH_L      = 5,
    PKT_INDEX_LENGTH_H      = 6,
    PKT_INDEX_INSTRUCTION   = 7
};

int DXL_build_ping_req(uint8_t id, uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_parse_ping_resp(uint8_t length, uint8_t* packet, uint8_t* error,
                        uint8_t *id, uint16_t *model, uint8_t* firmware);

int DXL_build_read_req(uint8_t id, uint16_t read_addr, uint16_t read_len,
                       uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_parse_read_resp(uint8_t length, uint8_t* packet, uint8_t* id, uint8_t* error,
                        uint8_t max_len, uint8_t *read_len, uint8_t* read_data);

int DXL_build_write_req(uint8_t id, uint16_t addr, uint8_t data_count, uint8_t* data,
                      uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_parse_write_resp(uint8_t length, uint8_t* packet, uint8_t* id, uint8_t* error);

int DXL_build_reg_write_req(uint8_t id, uint16_t addr, uint8_t data_count, uint8_t* data,
                         uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_parse_reg_write_resp(uint8_t length, uint8_t* packet, uint8_t* id, uint8_t* error);

int DXL_build_action_req(uint8_t id, uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_build_factory_rst_req(uint8_t id, uint8_t reset_mode, uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_build_reboot_req(uint8_t id, uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_build_sync_read_req(uint8_t id, uint16_t read_addr, uint16_t read_len, uint8_t num_ids, uint8_t* read_ids,
                         uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_build_sync_write_req(uint8_t id, uint16_t write_addr, uint16_t write_len, uint8_t num_writes, uint8_t* write_ids,
                          uint8_t* write_data, uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_build_pkt(uint8_t id, uint8_t instruction, uint8_t param_count, uint8_t *params,
                uint8_t max_len, uint8_t* length, uint8_t* packet);

int DXL_parse_status_pkt(uint8_t length, uint8_t* packet, uint8_t *id, uint8_t* error,
                      uint8_t max_params, uint8_t *param_count, uint8_t *params);

uint16_t DXL_compute_crc(uint16_t length, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif
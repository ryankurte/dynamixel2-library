
#ifndef DYNAMIXEL_PROTO_H
#define DYNAMIXEL_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
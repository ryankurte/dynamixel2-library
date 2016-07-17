
#pragma once

#include <stdint.h>

#include "dynamixel/dynamixel_proto.h"
#include "dynamixel/dynamixel_defs.h"

namespace Dynamixel
{

class Protocol
{
public:

    static int BuildPingRequest(uint8_t id, uint8_t max_len, uint8_t* length, uint8_t* packet);

    static int ParsePingResponse(uint8_t length, uint8_t* packet, uint8_t* error,
                                 uint8_t *id, uint16_t *model, uint8_t* firmware);

    static int BuildReadRequest(uint8_t id, uint16_t read_addr, uint16_t read_len,
                         uint8_t max_len, uint8_t* length, uint8_t* packet);

    static int ParseReadResponse(uint8_t length, uint8_t* packet, uint8_t* id, uint8_t* error,
                                uint8_t max_len, uint8_t *read_len, uint8_t* read_data);

    static int BuildWriteRequest(uint8_t id, uint16_t addr, uint8_t data_count, uint8_t* data,
                          uint8_t max_len, uint8_t* length, uint8_t* packet);

    static int ParseStatusPacket(uint8_t length, uint8_t* packet, uint8_t *id, uint8_t* error,
                                 uint8_t max_params, uint8_t *param_count, uint8_t *params);

    static uint16_t ComputeCRC(uint16_t length, uint8_t *data);

private:

    static int BuildPacket(uint8_t id, uint8_t instruction, uint8_t param_count, uint8_t *params,
                           uint8_t max_len, uint8_t* length, uint8_t* packet);

};

}
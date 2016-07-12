
#pragma once

#include <stdint.h>

#include "SerialInterface.hpp"

#include "dynamixel_defs.h"
#include "dynamixel_proto.h"

namespace Dynamixel
{

class Manager
{
public:

    Manager(SerialInterface* si)
    {
        _si = si;
    }

    int Tick(uint32_t time_ms)
    {


        return 0;
    }

    static uint16_t ComputeCRC(uint16_t length, uint8_t *data);

    int BuildPing(uint8_t id);

    int BuildWrite(uint8_t id, uint16_t addr, uint8_t data_count, uint8_t* data,
                        uint8_t max_len, uint8_t* length, uint8_t* packet);

    int BuildPacket(uint8_t id, uint8_t instruction, uint8_t param_count, uint8_t *params,
                    uint8_t max_len, uint8_t* length, uint8_t* packet);

private:
    SerialInterface* _si;
    uint32_t _last_update;
};

}



#pragma once

#include <stdint.h>

#include "SerialInterface.hpp"

#include "dynamixel_defs.h"


namespace Dynamixel
{

class Dynamixel
{
public:

    Dynamixel(SerialInterface* si)
    {
        _si = si;
    }

    int Tick(uint32_t time_ms)
    {

        return 0;
    }


private:
    SerialInterface* _si;
    uint32_t _last_update;
};

}


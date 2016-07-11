
#pragma once

#include <stdint.h>


#pragma once

namespace Dynamixel
{

class SerialInterface
{
    virtual int Available() = 0;
    virtual void Put(char* c) = 0;
    virtual char Get() = 0;
};

class Manager
{
public:

    enum ManagerState {
        INIT,
        IDLE,
        SEND,
        WAIT,
        RECEIVE
    };

    Manager(SerialInterface* si)
    {
        _si = si;
        _state = IDLE;
    }

    bool IsBusy() {
        return (_state == IDLE) ? false : true;
    }

    int Tick(uint32_t time_ms)
    {


        return 0;
    }

    int BuildPacket(uint8_t id, uint8_t instruction, uint8_t param_count, uint8_t *params,
                    uint8_t max_len, uint8_t* length, uint8_t* packet);

private:
    SerialInterface* _si;
    uint32_t _last_update;
    ManagerState _state;

};

}


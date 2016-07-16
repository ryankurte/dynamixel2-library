
#include "dynamixel/SerialInterface.hpp"

namespace Dynamixel
{

SerialInterface::SerialInterface(SerialDriver *sd)
{
    _sd = sd;
    _state = INTERFACE_STATE_IDLE;
    _input_count = 0;
}

bool SerialInterface::IsBusy()
{
    return (_state == INTERFACE_STATE_IDLE) ? false : true;
}

int SerialInterface::Send(int length, uint8_t* data)
{
    for (int i = 0; i < length; i++) {
        _sd->Put(data[i]);
    }
}

int SerialInterface::Await(uint32_t time_ms, int length, uint32_t timeout_ms)
{
    if(this->IsBusy()) {
        return INTERFACE_ERROR_BUSY;
    }

    _await_start_ms = time_ms;
    _await_timeout_ms = time_ms + timeout_ms;

    _state = INTERFACE_STATE_WAIT;

    return INTERFACE_OK;
}

}

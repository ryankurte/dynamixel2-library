
#pragma once

#include <stdint.h>

#define MAX_INPUT_BUFFER        128

namespace Dynamixel
{

class SerialDriver
{
public:
    virtual int Available() = 0;
    virtual void Put(char c) = 0;
    virtual char Get() = 0;
};

enum InterfaceState {
    INTERFACE_STATE_IDLE,
    INTERFACE_STATE_WAIT,
    INTERFACE_STATE_DONE,
    INTERFACE_STATE_TIMEOUT
};

enum InterfaceError {
    INTERFACE_OK = 0,
    INTERFACE_ERROR_BUSY = -1,
};

class SerialInterface
{
public:
    SerialInterface(SerialDriver *sd);

    int Send(int length, uint8_t* data);

    int Await(uint32_t time_ms, int length, uint32_t timeout_ms);

    bool IsBusy();

private:
    SerialDriver *_sd;
    InterfaceState _state;

    // Expectation timeout
    uint32_t _await_start_ms;
    uint32_t _await_timeout_ms;

    // Input buffering
    uint8_t _input_buf[MAX_INPUT_BUFFER];
    int _input_count;
};

}


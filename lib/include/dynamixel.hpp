
#pragma once

#include <stdint.h>

namespace Dynamixel
{

class SerialInterface
{
    virtual void putc(char* c) = 0;
    virtual char getc() = 0;
};

enum ControlMode {
    ControlModeWheel = 1,   //!< Used for wheel type motors, infinite rotation
    ControlModeJoint = 2    //!< Used for joint type motors, servo angles controlled
};

enum Instruction {
    PING            = 0x01, 
    READ            = 0x02,
    WRITE           = 0x03,
    REG_WRITE       = 0x04,
    ACTION          = 0x05,
    FACTORY_RESET   = 0x06,
    REBOOT          = 0x08,
    STATUS          = 0x55,
    SYNC_READ       = 0x82,
    SYNC_WRITE      = 0x83,
    BULK_READ       = 0x92,
    BULK_WRITE      = 0x93
};

enum Address {
    BROADCAST       = 0xFE
};

enum MemoryAddress {
    DX_MODEL_NO = 0,
    DX_FIRMWARE_VER = 2,
    DX_ID = 3,
    DX_BAUD = 4,
    DX_RETURN_DELAY = 5,
    DX_CW_ANGLE_LIMIT = 6,
    DX_CCW_ANGLE_LIMIT = 8,

};

enum ProtocolError {
    ERRNUM_RESULT_FAIL = 1,       //!< Failed to process the instruction packet.
    ERRNUM_INSTRUCTION = 2,       //!< Instruction error
    ERRNUM_CRC         = 3,       //!< CRC check error
    ERRNUM_DATA_RANGE  = 4,       //!< Data range error
    ERRNUM_DATA_LENGTH = 5,       //!< Data length error
    ERRNUM_DATA_LIMIT  = 6,       //!< Data limit error
    ERRNUM_ACCESS      = 7        //!< Access error
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

private:
    SerialInterface* _si;
    uint32_t _last_update;
    ManagerState _state;

    int BuildPacket(uint8_t id, uint8_t instruction, uint8_t param_count, uint8_t *params,
                    uint8_t max_len, uint8_t* length, uint8_t* packet);
};

}


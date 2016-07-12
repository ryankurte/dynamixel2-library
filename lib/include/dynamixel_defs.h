
#pragma once

namespace Dynamixel
{

enum ControlMode {
    ControlModeWheel = 1,   //!< Used for wheel type motors, infinite rotation
    ControlModeJoint = 2    //!< Used for joint type motors, servo angles controlled
};

enum Instruction {
    DX_INSTR_PING            = 0x01,
    DX_INSTR_READ            = 0x02,
    DX_INSTR_WRITE           = 0x03,
    DX_INSTR_REG_WRITE       = 0x04,
    DX_INSTR_ACTION          = 0x05,
    DX_INSTR_FACTORY_RESET   = 0x06,
    DX_INSTR_REBOOT          = 0x08,
    DX_INSTR_STATUS          = 0x55,
    DX_INSTR_SYNC_READ       = 0x82,
    DX_INSTR_SYNC_WRITE      = 0x83,
    DX_INSTR_BULK_READ       = 0x92,
    DX_INSTR_BULK_WRITE      = 0x93
};

enum Address {
    ADDR_BROADCAST           = 0xFE
};

enum EepromAddress {
    DX_EEP_MODEL_NO         = 0x0,
    DX_EEP_FIRMWARE_VER     = 0x2,
    DX_EEP_ID               = 0x3,
    DX_EEP_BAUD             = 0x4,
    DX_EEP_RETURN_DELAY     = 0x5,
    DX_EEP_CW_ANGLE_LIMIT   = 0x6,
    DX_EEP_CCW_ANGLE_LIMIT  = 0x8,
    DX_EEP_CONTROL_MODE     = 0x11,
    DX_EEP_LIMIT_TEMP       = 0x12,
    DX_EEP_LOWER_LIMIT_V    = 0x13,
    DX_EEP_UPPER_LIMIT_V    = 0x14,
    DX_EEP_MAX_TORQUE       = 0x15,
    DX_EEP_RETURN_LEVEL     = 0x17,
    DX_EEP_ALARM_SHUTDOWN   = 0x18
};

enum RamAddress {
    DX_RAM_TORQUE_ENABLE    = 0x24,
    DX_RAM_LED              = 0x25,
    DX_RAM_D_GAIN           = 0x27,
    DX_RAM_I_GAIN           = 0x28,
    DX_RAM_P_GAIN           = 0x29,
    DX_RAM_GOAL_POS         = 0x30,
    DX_RAM_GOAL_VEL         = 0x32,
    DX_RAM_GOAL_TORQUE      = 0x35,
    DX_RAM_CURR_POS         = 0x37,
    DX_RAM_CURR_VEL         = 0x39,
    DX_RAM_CURR_LOAD        = 0x41,
    DX_RAM_CURR_VOLTAGE     = 0x45,
    DX_RAM_CURR_TEMP        = 0x46,
    DX_RAM_REG_INSTR        = 0x47,
    DX_RAM_MOVING           = 0x49,
    DX_RAM_HW_ERR_STATUS    = 0x50,
    DX_RAM_PUNCH            = 0x51
};

enum ProtocolError {
    ERRNUM_RESULT_FAIL      = 0x1,   //!< Failed to process the instruction packet.
    ERRNUM_INSTRUCTION      = 0x2,   //!< Instruction error
    ERRNUM_CRC              = 0x3,   //!< CRC check error
    ERRNUM_DATA_RANGE       = 0x4,   //!< Data range error
    ERRNUM_DATA_LENGTH      = 0x5,   //!< Data length error
    ERRNUM_DATA_LIMIT       = 0x6,   //!< Data limit error
    ERRNUM_ACCESS           = 0x7    //!< Access error
};

}


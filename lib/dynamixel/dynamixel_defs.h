
#ifndef DYNAMIXEL_DEFS_H
#define DYNAMIXEL_DEFS_H

enum dxl_control_mode_e {
    DX_CTRL_MODE_WHEEL = 1,             //!< Used for wheel type motors, infinite rotation
    DX_CTRL_MODE_JOINT = 2              //!< Used for joint type motors, servo angles controlled
};

enum dxl_factory_rst_mode_e {
    DX_FACTORY_RST_ALL          = 0xff,     //!< Reset all values
    DX_FACTORY_RST_NO_ID        = 0x01,     //!< Reset all values except ID
    DX_FACTORY_RST_NO_ID_BAUD   = 0x02      //!< Reset all values except ID and baud rate
};

enum dxl_instruction_e {
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

enum dxl_id_e {
    DX_ID_BROADCAST        = 0xFE
};

enum dxl_eeprom_address_e {
    DX_EEP_MODEL_NO         = 0,
    DX_EEP_FIRMWARE_VER     = 2,
    DX_EEP_ID               = 3,
    DX_EEP_BAUD             = 4,
    DX_EEP_RETURN_DELAY     = 5,
    DX_EEP_CW_ANGLE_LIMIT   = 6,
    DX_EEP_CCW_ANGLE_LIMIT  = 8,
    DX_EEP_CONTROL_MODE     = 11,
    DX_EEP_LIMIT_TEMP       = 12,
    DX_EEP_LOWER_LIMIT_V    = 13,
    DX_EEP_UPPER_LIMIT_V    = 14,
    DX_EEP_MAX_TORQUE       = 15,
    DX_EEP_RETURN_LEVEL     = 17,
    DX_EEP_ALARM_SHUTDOWN   = 18
};

enum dxl_ram_address_e {
    DX_RAM_TORQUE_ENABLE    = 24,
    DX_RAM_LED              = 25,
    DX_RAM_D_GAIN           = 27,
    DX_RAM_I_GAIN           = 28,
    DX_RAM_P_GAIN           = 29,
    DX_RAM_GOAL_POS         = 30,
    DX_RAM_GOAL_VEL         = 32,
    DX_RAM_GOAL_TORQUE      = 35,
    DX_RAM_CURR_POS         = 37,
    DX_RAM_CURR_VEL         = 39,
    DX_RAM_CURR_LOAD        = 41,
    DX_RAM_CURR_VOLTAGE     = 45,
    DX_RAM_CURR_TEMP        = 46,
    DX_RAM_REG_INSTR        = 47,
    DX_RAM_MOVING           = 49,
    DX_RAM_HW_ERR_STATUS    = 50,
    DX_RAM_PUNCH            = 51
};

enum dxl_protocol_error_e {
    DX_ERRNUM_RESULT_FAIL      = 0x1,   //!< Failed to process the instruction packet.
    DX_ERRNUM_INSTRUCTION      = 0x2,   //!< Instruction error
    DX_ERRNUM_CRC              = 0x3,   //!< CRC check error
    DX_ERRNUM_DATA_RANGE       = 0x4,   //!< Data range error
    DX_ERRNUM_DATA_LENGTH      = 0x5,   //!< Data length error
    DX_ERRNUM_DATA_LIMIT       = 0x6,   //!< Data limit error
    DX_ERRNUM_ACCESS           = 0x7    //!< Access error
};

enum dxl_led_e {
    DX_LED_RED = 0x1,
    DX_LED_GRN = 0x2,
    DX_LED_BLU = 0x4
};

// DXL object for internal use
struct dxl_s {
    int open;                       //!< Indicates whether the device is open
    struct dxl_driver_s* driver;    //!< Driver function object
    void* driver_ctx;               //!< Driver context
};

#endif


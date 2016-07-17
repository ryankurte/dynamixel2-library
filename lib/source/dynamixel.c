/**
 * Dynamixel Support Library
 *
 * Based on http://support.robotis.com/en/product/dynamixel_pro/communication/instruction_status_packet.htm
 * http://support.robotis.com/en/techsupport_eng.htm#product/dynamixel2/communication/xl-320.htm
 * http://www.trossenrobotics.com/dynamixel-xl-320-robot-actuator
 *
 */


#include "dynamixel/dynamixel.h"

#include <stdlib.h>
#include <stdint.h>

#include "dynamixel/dynamixel_proto.h"
#include "dynamixel/dynamixel_defs.h"

// Wrap debug outputs
#ifdef DEBUG_DXL
#define DXL_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DXL_DEBUG_PRINT(...)
#endif


int DXL_init(struct dxl_s *dxl, struct dxl_driver_s *driver, void* driver_ctx)
{
    // Check driver functions exist
    if ((driver->write == NULL) || (driver->read == NULL)){
        return DXL_DRIVER_INVALID;
    }

    // Save driver pointers
    dxl->driver = driver;
    dxl->driver_ctx = driver_ctx;

    return 0;
}


int DXL_ping(struct dxl_s *dxl, uint8_t id, uint16_t *model, uint8_t *firmware)
{

}

int DXL_set_id(struct dxl_s *dxl, uint8_t old_id, uint8_t new_id)
{

}

int DXL_set_baud(struct dxl_s *dxl, uint8_t id, uint32_t baud)
{

}

int DXL_set_led(struct dxl_s *dxl, uint8_t id, uint8_t rgb)
{
    uint8_t data[32];
    uint8_t length;

    DXL_build_write_req(id, DX_RAM_LED, 1, &rgb, sizeof(data), &length, data);

    return dxl->driver->write(dxl->driver_ctx, length, data);
}

int DXL_set_pos(struct dxl_s *dxl, uint8_t id, uint16_t pos)
{

}

int DXL_set_pid(struct dxl_s *dxl, uint8_t id, uint8_t p, uint8_t i, uint8_t d)
{

}

int DXL_get_status(struct dxl_s *dxl, uint8_t id, uint16_t* pos, uint16_t* speed, uint16_t* load)
{

}

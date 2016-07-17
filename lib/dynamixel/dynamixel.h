
#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#include "dynamixel_defs.h"
#include "dynamixel_proto.h"

enum dxl_result_e {
    DXL_RES_OK = 0,
    DXL_DRIVER_INVALID = -1,
    DXL_DRIVER_ERROR = -2,
    DXL_COMMS_ERROR = -3
};

// SPI interaction function for dependency injection
typedef int (*dxl_write_f)(void* context, int len, uint8_t *data_out);
typedef int (*dxl_read_f)(void* context, int max_len, int *len, uint8_t *data_in);

// Driver object for passing in to MPU9250 object
struct dxl_driver_s {
    dxl_write_f write;    //!< Write to UART
    dxl_read_f read;      //!< Read from UART
};

int DXL_init(struct dxl_s *dxl, struct dxl_driver_s *driver, void* driver_ctx);

int DXL_close(struct dxl_s *dxl);

int DXL_ping(struct dxl_s *dxl, uint8_t id, uint16_t *model, uint8_t *firmware);

int DXL_set_id(struct dxl_s *dxl, uint8_t old_id, uint8_t new_id);

int DXL_set_baud(struct dxl_s *dxl, uint8_t id, uint32_t baud);

int DXL_set_led(struct dxl_s *dxl, uint8_t id, uint8_t rgb);

int DXL_set_pos(struct dxl_s *dxl, uint8_t id, uint16_t pos);

int DXL_set_pid(struct dxl_s *dxl, uint8_t id, uint8_t p, uint8_t i, uint8_t d);

int DXL_get_status(struct dxl_s *dxl, uint8_t id, uint16_t* pos, uint16_t* speed, uint16_t* load);

#ifdef __cplusplus
}
#endif

#endif // DYNAMIXEL_H


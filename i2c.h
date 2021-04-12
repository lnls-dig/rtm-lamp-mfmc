#include <stdint.h>
#include "err.h"

//-----------------------------------------------------------------------------
/// Read data through the I2C bus - for devices with one byte address register
/// @param bus_id the I2C bus to use
/// @param chip I2C address of the remote device
/// @param reg selected resister in the addressed device
/// @param buff buffer for received data
/// @param len size of the buffer
/// @return MMC_FAILED in case of error, MMC_OK otherwise
mmc_result_t i2c_read(uint8_t bus_id, uint8_t chip, uint8_t reg, uint8_t* buff, uint8_t len);


//-----------------------------------------------------------------------------
/// Write data through the I2C bus - for devices with one byte address register
/// @param bus_id the I2C bus to use
/// @param chip I2C address of the remote device
/// @param reg selected resister in the addressed device
/// @param buff buffer with data to write
/// @param len amount of data
/// @return MMC_FAILED in case of error, MMC_OK otherwise
mmc_result_t i2c_write(uint8_t bus_id, uint8_t chip, uint8_t reg, uint8_t* buff, uint8_t len);

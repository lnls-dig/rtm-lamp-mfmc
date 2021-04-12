/*
 *   openMMC -- Open Source modular IPM Controller firmware
 *
 *   Copyright (C) 2015  Henrique Silva <henrique.silva@lnls.br>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 */

/**
 * @file   pca9554.c
 * @author Henrique Silva <henrique.silva@lnls.br>
 *
 * @brief  PCA9554 module interface functions implementations
 *
 * @ingroup PCA9554
 */

#include "pca9554_mfmc.h"
#include "i2c.h"

/* Pins Read/Write */
mmc_result_t pca9554_read_port(uint8_t bus_id, uint8_t chip, uint8_t *readout)
{
    return i2c_read(bus_id, chip, PCA9554_INPUT_REG, readout, 1);
}

mmc_result_t pca9554_read_pin(uint8_t bus_id, uint8_t chip, uint8_t pin, uint8_t *status)
{
    uint8_t pin_read = 0;
    mmc_result_t ret;

    ret = pca9554_read_port(bus_id, chip, &pin_read);

    if (status) {
        *status = ((pin_read >> pin) & 0x1);
    }

    return ret;
}

mmc_result_t pca9554_write_port(uint8_t bus_id, uint8_t chip, uint8_t data)
{
    return i2c_write(bus_id, chip, PCA9554_OUTPUT_REG, &data, 1);
}

mmc_result_t pca9554_write_pin(uint8_t bus_id, uint8_t chip, uint8_t pin, uint8_t data)
{
    uint8_t output = 0;
    mmc_result_t ret;

    ret = pca9554_read_port(bus_id, chip, &output);

    if (ret != MMC_OK) {
        return ret;
    }

    output &= ~(1 << pin);
    output |= (data << pin);

    return pca9554_write_port(bus_id, chip, output);
}

/* Polarity Control */
mmc_result_t pca9554_set_port_pol(uint8_t bus_id, uint8_t chip, uint8_t pol)
{
    return i2c_write(bus_id, chip, PCA9554_POLARITY_REG, &pol, 1);
}

mmc_result_t pca9554_set_pin_pol(uint8_t bus_id, uint8_t chip, uint8_t pin, uint8_t pol)
{
    uint8_t pol_reg = 0;
    mmc_result_t ret;

    ret = pca9554_read_port(bus_id, chip, &pol_reg);

    if (ret != MMC_OK) {
        return ret;
    }

    pol_reg &= ~(1 << pin);
    pol_reg |= (pol << pin);

    return pca9554_set_port_pol(bus_id, chip, pol_reg);
}

mmc_result_t pca9554_get_port_pol(uint8_t bus_id, uint8_t chip, uint8_t *pol)
{
    return i2c_read(bus_id, chip, PCA9554_POLARITY_REG, pol, 1);
}

mmc_result_t pca9554_get_pin_pol(uint8_t bus_id, uint8_t chip, uint8_t pin, uint8_t *pol)
{
    uint8_t rx_len;
    mmc_result_t ret;

    ret = pca9554_get_port_pol(bus_id, chip, pol);

    /* Mask all bits, except the one requested */
    *pol = ((*pol >> pin) & 0x1);

    return ret;
}

/* Pins direction (output/input) */
mmc_result_t pca9554_set_port_dir(uint8_t bus_id, uint8_t chip, uint8_t dir)
{
    return i2c_write(bus_id, chip, PCA9554_CFG_REG, &dir, 1);
}

mmc_result_t pca9554_set_pin_dir(uint8_t bus_id, uint8_t chip, uint8_t pin, uint8_t dir)
{
    uint8_t dir_reg = 0;
    mmc_result_t ret;

    ret = pca9554_read_port(bus_id, chip, &dir_reg);

    if (ret != MMC_OK) {
        return ret;
    }

    dir_reg &= ~(1 << pin);
    dir_reg |= (dir << pin);

    return pca9554_set_port_dir(bus_id, chip, dir_reg);
}

mmc_result_t pca9554_get_port_dir(uint8_t bus_id, uint8_t chip, uint8_t *dir)
{
    return i2c_read(bus_id, chip, PCA9554_CFG_REG, dir, 1);
}

mmc_result_t pca9554_get_pin_dir(uint8_t bus_id, uint8_t chip, uint8_t pin, uint8_t *dir)
{
    uint8_t rx_len;
    mmc_result_t ret;

    ret = pca9554_get_port_dir(bus_id, chip, dir);

    /* Mask all bits, except the one requested */
    *dir = ((*dir >> pin) & 0x1);

    return ret;
}

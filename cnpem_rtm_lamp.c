/**
 * @file   cnpem_rtm_lamp.c
 * @author Augusto Fraga Giachero <augusto.fraga@cnpem.br>
 *
 * @brief  RTM-LAMP initialization and power control
 *
 * @ingroup rtm-lamp
 */

#include "cdce906_mfmc.h"
#include "cdce906_mfmc_cfg.h"
#include "pca9554_mfmc.h"
#include "cnpem_rtm_lamp.h"
#include "delay.h"

mmc_result_t cnpem_pll_init(void) {
    uint8_t chip = 0; // Replace with the correct chip id for the CDCE906 (IC12)
    uint8_t bus_id = 0; // Replace with the correct bus id
    mmc_result_t ret;


    /*
     * Set all pins as outputs
     */
    ret = pca9554_set_port_dir(bus_id, chip, 0x00);

    if (ret != MMC_OK) {
        return ret;
    }

    /*
     * Disable all power rails
     */
    ret = pca9554_write_port(bus_id, chip, (0 << RTM_GPIO_NEG_7V_EN) |
                             (1 << RTM_GPIO_7V_EN) | (0 << RTM_GPIO_VS1_EN) |
                             (0 << RTM_GPIO_VS2_EN) | (0 << RTM_GPIO_5V_EN));

    if (ret != MMC_OK) {
        return ret;
    }

    return cdce906_write_cfg(bus_id, chip, &cdce906_rtm_lamp_cfg);
}

mmc_result_t cnpem_rtm_poweron(void) {
    uint8_t chip = 0; // Replace with the correct chip id for the PCA9554 (IC13)
    uint8_t bus_id = 0; // Replace with the correct bus id
    mmc_result_t ret;

    /*
     * RTM-LAMP power up sequence
     */
    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_5V_EN, 1);

    if (ret != MMC_OK) {
        return ret;
    }

    delay_ms(10);

    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_NEG_7V_EN, 1);

    if (ret != MMC_OK) {
        return ret;
    }

    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_7V_EN, 0);

    if (ret != MMC_OK) {
        return ret;
    }

    delay_ms(10);

    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_VS1_EN, 1);

    if (ret != MMC_OK) {
        return ret;
    }

    #ifndef RTM_LAMP_DISABLE_VS2
    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_VS2_EN, 1);
    #endif

    return ret;
}

mmc_result_t cnpem_rtm_poweroff(void) {
    uint8_t chip = 0; // Replace with the correct chip id for the PCA9554 (IC13)
    uint8_t bus_id = 0; // Replace with the correct bus id
    mmc_result_t ret;

    /*
     * RTM-LAMP power down sequence
     */
    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_VS1_EN, 0);

    if (ret != MMC_OK) {
        return ret;
    }

    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_VS2_EN, 0);

    if (ret != MMC_OK) {
        return ret;
    }

    delay_ms(10);

    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_NEG_7V_EN, 0);

    if (ret != MMC_OK) {
        return ret;
    }

    ret = pca9554_write_pin(bus_id, chip, RTM_GPIO_7V_EN, 1);

    if (ret != MMC_OK) {
        return ret;
    }

    delay_ms(10);

    return pca9554_write_pin(bus_id, chip, RTM_GPIO_5V_EN, 0);
}

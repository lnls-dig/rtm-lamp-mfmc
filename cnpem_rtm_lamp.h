/**
 * @file   cnpem_rtm_lamp.h
 * @author Augusto Fraga Giachero <augusto.fraga@cnpem.br>
 *
 * @brief  RTM-LAMP initialization and power control
 *
 * @ingroup rtm-lamp
 */

#ifndef CNPEM_RTM_LAMP_H_
#define CNPEM_RTM_LAMP_H_

#define RTM_GPIO_VS1_EN                 0
#define RTM_GPIO_VS2_EN                 1
#define RTM_GPIO_7V_EN                  2
#define RTM_GPIO_5V_EN                  3
#define RTM_GPIO_NEG_7V_EN              4

#include "err.h"

mmc_result_t cnpem_pll_init(void);
mmc_result_t cnpem_rtm_poweron(void);
mmc_result_t cnpem_rtm_poweroff(void);

#endif

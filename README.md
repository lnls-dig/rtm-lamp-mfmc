# RTM-LAMP support files for MFMC

This repository contains the support files for RTM-LAMP ported from openMMC to MFMC.

## File descriptions

`cnpem_rtm_lamp.c` : Initialization and power up / power down functions;
`cnpem_rtm_lamp.h` : Header definitions for `cnpem_rtm_lamp.c`;
`cdce906_mfmc.c` : Device driver for the CDCE906 clock synthesizer / PLL;
`cdce906_mfmc.h` : Header definitions for `cdce906_mfmc.c:`;
`cdce906_reg.h` : CDCE906 Register definitions for `cdce906_mfmc.c:`;
`cdce906_mfmc_cfg.h` : CDCE906 default configuration definition for RTM-LAMP;
`pca9554_mfmc.c` : Device driver for the PCA9554 I/O expander;
`pca9554_mfmc.h` : Header definitions for `pca9554_mfmc.c:`.

Mock-up headers (substitute with the ones provided by the MFMC mmc):
`i2c.h` : I2C functions definitions;
`delay.h` : Delay definition;
`err.h` : Error codes.

## Usage

After the RTM board is detected, `cnpem_pll_init` should be called to initialize the CDCE906 clock synthesizer / PLL and the PCA9554 I/O directions. When powering up call `cnpem_rtm_poweron`. When powering down call `cnpem_rtm_poweroff`.

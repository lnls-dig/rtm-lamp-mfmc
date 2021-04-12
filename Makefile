cnpem_rtm_lamp.a: cnpem_rtm_lamp.o cdce906_mfmc.o pca9554_mfmc.o
	avr-ar -rcs $@ $?

cnpem_rtm_lamp.o: cnpem_rtm_lamp.c cdce906_mfmc.h cdce906_mfmc_cfg.h pca9554_mfmc.h cnpem_rtm_lamp.h delay.h
	avr-gcc -c $< -o $@

cdce906_mfmc.o: cdce906_mfmc.c cdce906_mfmc.h cdce906_reg.h i2c.h
	avr-gcc -c $< -o $@

pca9554_mfmc.o: pca9554_mfmc.c pca9554_mfmc.h i2c.h
	avr-gcc -c $< -o $@

clean:
	rm -f cnpem_rtm_lamp.o cdce906_mfmc.o pca9554_mfmc.o

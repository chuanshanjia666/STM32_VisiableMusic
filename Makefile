OPENOCD_DIR ?=E:/environment/xpack-openocd-0.12.0-3-win32-x64/xpack-openocd-0.12.0-3/openocd

all:
	$(MAKE) -C main all

clean:
	$(MAKE) -C main clean

upload:
	$(MAKE) -C main upload OPENOCD_DIR=$(OPENOCD_DIR)

debug:
	$(MAKE) -C main debug OPENOCD_DIR=$(OPENOCD_DIR)

.PHONY: all clean upload debug

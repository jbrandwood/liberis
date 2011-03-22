OBJECTS        = src/crt0.o
TARGETS        = liberis.a src/crt0.o
LIBERISOBJS    = src/v810.o src/pad.o src/soundbox.o src/tetsu.o src/7up.o
OBJECTS       += $(LIBERISOBJS)
PREFIX         = v810-
CC             = $(PREFIX)gcc
AS             = $(PREFIX)as
AR             = $(PREFIX)ar
CFLAGS         = -O3 -I include

.PHONY: all clean install

all: $(OBJECTS) $(TARGETS)

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@
liberis.a: $(LIBERISOBJS)
	$(AR) rcs $@ $(LIBERISOBJS) 
clean:
	rm -rf $(OBJECTS) $(TARGETS)
install: $(TARGETS)
	@mkdir -p $(V810DEV)/lib
	@mkdir -p $(V810DEV)/include/eris/
	@echo "    COPY  crt0.o"
	@cp src/crt0.o $(V810DEV)/include/
	@echo "    COPY  liberis.a"
	@cp liberis.a $(V810DEV)/lib/
	@echo "    COPY  include/"
	@cp -R include/* $(V810DEV)/include/


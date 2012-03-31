TARGETS       += $(ELF_TARGET) $(BIN_TARGET)
PREFIX         = v810-
CC             = $(PREFIX)gcc
AS             = $(PREFIX)as
AR             = $(PREFIX)ar
LD             = $(PREFIX)ld
OBJCOPY        = $(PREFIX)objcopy
CFLAGS        += -I$(V810DEV)/include/ -mspace -mv810 -O0 -Wall
LDFLAGS       += -L$(V810DEV)/lib/ $(V810DEV)/lib/crt0.o -leris -lgcc

.PHONY: all cd clean install .FORCE

all: $(OBJECTS) $(TARGETS)

$(CD_OBJECTS): .FORCE lbas.h

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@
%.elf: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@ 
%.bin: %.elf
	$(OBJCOPY) -O binary -R .stack -R .zdata $< $@
cd: $(TARGETS)
	bincat out.bin lbas.h $(BIN_TARGET) $(ADD_FILES)
	make clean -C .
	make -C .
	bincat out.bin lbas.h $(BIN_TARGET) $(ADD_FILES)
	pcfx-cdlink cdlink.txt $(CDOUT)

lbas.h:
	bincat - lbas.h $(BIN_TARGET) $(ADD_FILES)

clean:
	rm -rf $(OBJECTS) $(TARGETS) lbas.h $(CDOUT).cue $(CDOUT).bin

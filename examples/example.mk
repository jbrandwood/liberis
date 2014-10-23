TARGETS       += $(ELF_TARGET) $(BIN_TARGET)
PREFIX         = v810-
CC             = $(PREFIX)gcc
AS             = $(PREFIX)as
AR             = $(PREFIX)ar
LD             = $(PREFIX)ld
OBJCOPY        = $(PREFIX)objcopy
CFLAGS        += -I$(V810DEV)/include/ -nostdlib -mv810 -O0 -Wall
LIBS           = -leris
LDFLAGS       += -L$(V810DEV)/lib/ -T$(V810DEV)/v810/lib/ldscripts/v810.x $(V810DEV)/v810/lib/crt0.o

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
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@ 
%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
cd: $(TARGETS)
	bincat out.bin lbas.h $(BIN_TARGET) $(ADD_FILES)
	make cdclean -C .
	make all -C .
	bincat out.bin lbas.h $(BIN_TARGET) $(ADD_FILES)
	pcfx-cdlink cdlink.txt $(CDOUT)

lbas.h:
	bincat - lbas.h $(BIN_TARGET) $(ADD_FILES)

clean:
	rm -rf $(OBJECTS) $(TARGETS) lbas.h $(CDOUT).cue $(CDOUT).bin

cdclean:
	rm -rf $(OBJECTS) $(TARGETS) $(CDOUT).cue $(CDOUT).bin

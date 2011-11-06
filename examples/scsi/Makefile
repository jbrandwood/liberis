OBJECTS        = scsi.o
TARGETS        = scsi.elf scsi.bin
PREFIX         = v810-
CC             = $(PREFIX)gcc
AS             = $(PREFIX)as
AR             = $(PREFIX)ar
LD             = $(PREFIX)ld
OBJCOPY        = $(PREFIX)objcopy
CFLAGS         = -I$(V810DEV)/include/ -mspace -mv810 -O0 -Wall
LDFLAGS        = -L$(V810DEV)/lib/ $(V810DEV)/lib/crt0.o -leris -lgcc

.PHONY: all clean install

all: $(OBJECTS) $(TARGETS)

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
clean:
	rm -rf $(OBJECTS) $(TARGETS)

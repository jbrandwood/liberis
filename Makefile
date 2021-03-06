OBJECTS        = src/crt0.o
TARGETS        = liberis.a src/crt0.o
LIBERISOBJS    = src/v810.o src/tetsu.o src/king.o src/romfont.o src/bkupmem.o\
                 src/std.o src/timer.o src/cd.o src/pad.o src/7up.o
LIBERISOBJS   += src/low/pad.o src/low/soundbox.o src/low/7up.o src/low/scsi.o
OBJECTS       += $(LIBERISOBJS)
PREFIX         = v810
CC             = $(PREFIX)-gcc
AS             = $(PREFIX)-as
AR             = $(PREFIX)-ar
CFLAGS         = -O3 -I include

.PHONY: all clean install examples example_cds cleanexamples

all: $(OBJECTS) $(TARGETS)

%.o: %.S
	$(AS) $(ASFLAGS) $< -o $@
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@
liberis.a: $(LIBERISOBJS)
	$(AR) rcs $@ $(LIBERISOBJS) 
clean: cleanexamples
	rm -rf $(OBJECTS) $(TARGETS)
install: $(TARGETS)
	@mkdir -p $(V810GCC)/lib
	@mkdir -p $(V810GCC)/include/eris/
	@echo "    COPY  crt0.o"
	@cp src/crt0.o $(V810GCC)/$(PREFIX)/lib/
#	@echo "    COPY  ldscripts"
#	@cp ldscripts/* $(V810GCC)/$(PREFIX)/lib/ldscripts/
	@echo "    COPY  liberis.a"
	@cp liberis.a $(V810GCC)/lib/
	@echo "    COPY  include/"
	@cp -R include/* $(V810GCC)/include/
examples:
	make -C examples
example_cds:
	make -C examples cd
cleanexamples:
	make -C examples clean


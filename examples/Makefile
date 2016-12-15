.PHONY: all hello fxbmp fxpad cellophane psg bg7up spr7up scsi scsi_dma hello_interrupt hello_newlib hello_plusplus cd clean

all: hello fxbmp fxpad cellophane psg bg7up spr7up scsi scsi_dma hello_interrupt hello_newlib hello_plusplus

hello:
	make -C $@
hello_interrupt:
	make -C $@
hello_newlib:
	make -C $@
hello_plusplus:
	make -C $@
fxbmp:
	make -C $@
fxpad:
	make -C $@
cellophane:
	make -C $@
psg:
	make -C $@
bg7up:
	make -C $@
spr7up:
	make -C $@
scsi:
	make -C $@

cd:
	make -C hello cd
	make -C fxbmp cd
	make -C fxpad cd
	make -C cellophane cd
	make -C psg cd
	make -C bg7up cd
	make -C spr7up cd
	make -C scsi cd
	make -C scsi_dma cd
	make -C hello_interrupt cd
	make -C hello_newlib cd
	make -C hello_plusplus cd

clean:
	make -C hello clean
	make -C fxbmp clean
	make -C fxpad clean
	make -C cellophane clean
	make -C psg clean
	make -C bg7up clean
	make -C spr7up clean
	make -C scsi clean
	make -C scsi_dma clean
	make -C hello_interrupt clean
	make -C hello_newlib clean
	make -C hello_plusplus clean

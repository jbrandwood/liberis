.PHONY: all hello fxbmp fxpad cellophane psg bg7up spr7up scsi scsi_dma cd clean

all: hello fxbmp fxpad cellophane psg bg7up spr7up scsi scsi_dma

hello:
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

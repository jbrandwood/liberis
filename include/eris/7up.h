#ifndef _LIBERIS_7UP_H_
#define _LIBERIS_7UP_H_

void eris_7up_set_vram_write_addr(int chip, u16 addr);
void eris_7up_vram_write(int chip, u16 data);
void eris_7up_set_vram_read_addr(int chip, u16 addr);
u16 eris_7up_vram_read(int chip);
void eris_7up_set_control(int chip, int increment, int bg_show, int spr_show);
void eris_7up_set_interrupts(int chip, int irq_on, int raster_irq, int excess_spr, int spr_collision);
u16 eris_7up_get_raster(int chip);
void eris_7up_set_scroll(int chip, u16 x, u16 y);
void eris_7up_do_dma(int chip, u16 src, u16 dst, u16 len);
void eris_7up_setup_dma(int chip, int dsr_dma, int src_dec, int dst_dec, int vram_irq, int satb_irq);
void eris_7up_set_satb_address(int chip, u16 addr);

#endif


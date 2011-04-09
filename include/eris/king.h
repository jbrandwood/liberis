/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _LIBERIS_KING_H_
#define _LIBERIS_KING_H_

#include <eris/types.h>

typedef enum {
	KING_BGMODE_4_PAL = 0x1,
	KING_BGMODE_16_PAL = 0x2,
	KING_BGMODE_256_PAL = 0x3,
	KING_BGMODE_64K = 0x4,
	KING_BGMODE_16M = 0x5,
	KING_BGMODE_BAT = 0x8, /* OR this for BAT mode */
	KING_BGMODE_64K_BAT_EXTDOT = 0xE,
	KING_BGMODE_16M_BAT_EXTDOT = 0xF,
} king_bgmode;

typedef enum {
	KING_BGPRIO_HIDE = 0,
	KING_BGPRIO_0 = 1,
	KING_BGPRIO_1 = 2,
	KING_BGPRIO_2 = 3,
	KING_BGPRIO_3 = 4,
} king_bgprio;

typedef enum {
	KING_BGSIZE_8 = 3,
	KING_BGSIZE_16 = 4,
	KING_BGSIZE_32 = 5,
	KING_BGSIZE_64 = 6,
	KING_BGSIZE_128 = 7,
	KING_BGSIZE_256 = 8,
	KING_BGSIZE_512 = 9,
	KING_BGSIZE_1024 = 10,
} king_bgsize;

typedef enum {
	KING_BG0 = 0,
	KING_BG0SUB = 1,
	KING_BG1 = 2,
	KING_BG2 = 3,
	KING_BG3 = 4,
} king_bg;

void eris_king_init(void);
void eris_king_set_kram_read(u32 addr, int incr);
void eris_king_set_kram_write(u32 addr, int incr);
u16 eris_king_kram_read(void);
void eris_king_kram_write(u16 data);
void eris_king_set_kram_pages(u8 scsi, u8 bg, u8 rainbow, u8 adpcm);
void eris_king_set_bg_mode(king_bgmode bg0, king_bgmode bg1, king_bgmode bg2,
			king_bgmode bg3);
void eris_king_set_bg_prio(king_bgprio bg0, king_bgprio bg1, king_bgprio bg2,
			king_bgprio bg3, king_bgprio bgrot);
void eris_king_set_bg_size(king_bg bg, king_bgsize h, king_bgsize w,
			king_bgsize sub_h, king_bgsize sub_w);
void eris_king_set_bat_cg_addr(king_bg bg, u32 bat, u32 cg);
void eris_king_set_scroll(king_bg bg, s16 x, s16 y);
void eris_king_write_microprogram(u16* data, u8 addr, u8 len);
void eris_king_fill_microprogram(u16 data, u8 addr, u8 len);
void eris_king_enable_microprogram(void);
void eris_king_disable_microprogram(void);

#endif


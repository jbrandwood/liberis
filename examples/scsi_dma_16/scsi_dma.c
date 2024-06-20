/*
	liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011		Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#include <eris/types.h>
#include <eris/std.h>
#include <eris/v810.h>
#include <eris/king.h>
#include <eris/tetsu.h>
#include <eris/romfont.h>
#include <eris/cd.h>
#include <eris/low/pad.h>
#include <eris/low/scsi.h>

#include "lbas.h"

/*
 * Gameblabla :
 * 16bpp example.
 * This color mode is linear and little endian but still expects YUV pixels.
 * Use my tool for converting the images :
 * https://github.com/gameblabla/bmp2huc
 * 
 * You can also refer to it if you want to do software rendering on the hardware itself.
*/

int main(int argc, char *argv[])
{
	int i;
	u16 microprog[16];
	u32 paddata, lastpad;

	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_3, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, 0);
	eris_king_set_bg_mode(KING_BGMODE_64K, 0, 0, 0);
	eris_king_set_kram_pages(0, 0, 0, 0);

	for(i = 0; i < 16; i++) {
		microprog[i] = KING_CODE_NOP;
	}

	microprog[0] = KING_CODE_BG0_CG_0;
	microprog[1] = KING_CODE_BG0_CG_1;
	microprog[2] = KING_CODE_BG0_CG_2;
	microprog[3] = KING_CODE_BG0_CG_3;
	microprog[4] = KING_CODE_BG0_CG_4;
	microprog[5] = KING_CODE_BG0_CG_5;
	microprog[6] = KING_CODE_BG0_CG_6;
	microprog[7] = KING_CODE_BG0_CG_7;
	
	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 16);
	eris_king_enable_microprogram();

	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16,
				TETSU_COLORS_16, 0, 0, 1, 0, 0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0SUB, 0, 0);
	eris_king_set_scroll(KING_BG0, 0, 0);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);

	eris_king_set_kram_read(0, 1);
	eris_king_set_kram_write(0, 1);
	// Clear BG0's RAM
	for(i = 0x0; i < 0x7800 * 2; i++) {
		eris_king_kram_write(0);
	}
	eris_king_set_kram_write(0, 1);
	eris_low_pad_init(0);
	eris_cd_read_kram(BINARY_LBA_PORN_BIN, 0x400, 0x20000 + 0x400);
	
	for(;;) {
	}

	return 0;
}


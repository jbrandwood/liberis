/*
	liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011		Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*
 * Gameblabla :
 * This is similar to the other scsi dma example but
 * this one uses the 32bpp mode instead. (16 millions of colors)
 * The image has been converted with the b2k tool from GMAKER.
 * 
 * The only big difference between the 16 colors example and this one
 * is the microcode. I had to refer to Marshall's documentation to get it working.
 * Otherwise, i would only get parts of it.
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

void printch(u32 sjis, u32 kram, int tall);
void printstr(u32* str, int x, int y, int tall);
void chartou32(char* str, u32* o);
void printhex(void* data, int x, int y, int bytes, int addr, int tall);
char x1toa(int val);

u32 test_data_in(u8 *buf, u32 maxlen);

#define CLEAN_SCSICDB(cmd, len) { \
	scsicdb[0] = cmd; \
	for(i = 1; i < 32; i++) { \
		scsicdb[i] = 0; \
	} \
}

/*
 * Gameblabla :
 * So this is a 32bpp image example test on the PC-FX.
 * This is based upon the 16 colors SCSI DMA example but for the 32bpp mode instead :
 * http://daifukkat.su/pcfx/data/HuC6272.html
 * 
 * The only major difference is the microcode and the image itself being
 * converted with the b2k tool.
 * It seems that 64k color mode require as much space as 32bpp so it does
 * not seem to very useful in most case...
 */

int main(int argc, char *argv[])
{
	int i;
	u32 str[256];
	u16 microprog[16];

	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 3, 0, 0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_0, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, 0);
	eris_king_set_bg_mode(KING_BGMODE_16M, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE);
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

	eris_tetsu_set_palette(0, 0x0088);
	eris_tetsu_set_palette(1, 0xE088);
	eris_tetsu_set_palette(2, 0xE0F0);
	eris_tetsu_set_palette(3, 0x602C);
	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16, TETSU_COLORS_16, 0, 0, 1, 1, 0, 0, 0);

	
	/* BACKGROUND 0 */
	
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
	eris_cd_read_kram(BINARY_LBA_DUMB_BIN, 0x200, (0x20000 + 0x400));

	/* FIN BACKGROUND */
	
	//eris_low_pad_init(0);
	//eris_king_set_scroll(KING_BG0, 30, 0);
	
	for(;;) {

	}

	return 0;
}

void chartou32(char* str, u32* o)
{
	int i;
	int len = strlen8(str);
	for(i = 0; i < len; i++)
		o[i] = str[i];
	o[i] = 0;
}

void printstr(u32* str, int x, int y, int tall)
{
	int i;
	u32 kram = x + (y << 5);
	int len = strlen32(str);
	for(i = 0; i < len; i++) {
		printch(str[i], kram + i, tall);
	}
}

void printch(u32 sjis, u32 kram, int tall)
{
	u16 px;
	int x, y;
	u8* glyph = eris_romfont_get(sjis, tall ? ROMFONT_ANK_8x16 : ROMFONT_ANK_8x8);
	for(y = 0; y < (tall ? 16 : 8); y++) {
		eris_king_set_kram_write(kram + (y << 5), 1);
		px = 0;
		for(x = 0; x < 8; x++) {
			if((glyph[y] >> x) & 1) {
				px |= 1 << (x << 1);
			}
		}
		eris_king_kram_write(px);
	}
}


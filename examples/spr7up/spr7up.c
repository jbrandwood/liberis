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
#include <eris/low/7up.h>
#include <eris/tetsu.h>
#include <eris/romfont.h>

void printch(u32 sjis, u32 kram, int tall);
void printstr(u32* str, int x, int y, int tall);
void chartou32(char* str, u32* o);

int main(int argc, char *argv[])
{
	int i, x, y, xl, yl;
	u32 str[256];
	u16 microprog[16];

	eris_low_7up_init(0);
	eris_low_7up_init(1);
	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
	eris_tetsu_set_7up_palette(0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_3, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE);
	eris_king_set_bg_mode(KING_BGMODE_4_PAL, 0, 0, 0);
	eris_king_set_kram_pages(0, 0, 0, 0);

	for(i = 0; i < 16; i++) {
		microprog[i] = 0x100; /* NOP */
	}

	microprog[0] = 0; /* CG +0 */
	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 16);
	eris_king_enable_microprogram();

	eris_tetsu_set_palette(0, 0x0088);
	eris_tetsu_set_palette(1, 0xE088);
	eris_tetsu_set_palette(2, 0xE0F0);
	eris_tetsu_set_palette(3, 0x602C);
	eris_tetsu_set_palette(4, 0x5080);
	eris_tetsu_set_palette(5, 0xC422);
	eris_tetsu_set_palette(6, 0x9999);
	eris_tetsu_set_palette(7, 0x1234);
	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16,
				TETSU_COLORS_16, 0, 1, 1, 0, 0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0SUB, 0, 0);
	eris_king_set_scroll(KING_BG0, 0, 0);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);
	eris_low_7up_set_control(0, 0, 0, 1);
	eris_low_7up_set_access_width(0, 0, ERIS_LOW_7UP_MAP_32X32, 0, 0);
	eris_low_7up_set_scroll(0, 0, 0);
	eris_low_7up_set_video_mode(0, 2, 2, 4, 0x1F, 0x11, 2, 239, 2);

	eris_king_set_kram_read(0, 1);
	eris_king_set_kram_write(0, 1);
	// Clear BG0's RAM
	for(i = 0; i < 0x1E00; i++) {
		eris_king_kram_write(0);
	}
	eris_low_7up_set_vram_write(0, 0);
	eris_low_7up_vram_write(0, 0x0040);
	eris_low_7up_vram_write(0, 0x0040);
	eris_low_7up_vram_write(0, 0x0008);
	eris_low_7up_vram_write(0, 0x0080);
	for(i = 4; i < 0x100; i += 4) {
		eris_low_7up_vram_write(0, 0x03FF);
		eris_low_7up_vram_write(0, 0x03FF);
		eris_low_7up_vram_write(0, 0x0000);
		eris_low_7up_vram_write(0, 0x0000);
	}
	for(i = 0; i < 8*4; i++) {
		eris_low_7up_vram_write(0, i ^ (i << 3) ^ (i << 6) ^ (i << 9) ^ (i << 12) ^ (i >> 3) ^ 0xAAAA); /* Yay pseudo rando noise */
	}
	eris_low_7up_setup_dma(0, 1, 0, 0, 0, 0);
	eris_low_7up_set_satb_address(0, 0);
	eris_king_set_kram_write(0, 1);
	chartou32("7up sprite example", str);
	printstr(str, 7, 0x10, 1);

	x = y = 0x40;
	xl = yl = 1;
	for(;;) {
		eris_low_7up_set_vram_write(0, 0);
		eris_low_7up_vram_write(0, y);
		eris_low_7up_vram_write(0, x);
		if(yl)
			y++;
		else
			y--;
		if(xl)
			x++;
		else
			x--;
		if(x > 256+32-16)
			xl = 0;
		if(x < 32)
			xl = 1;
		if(y < 64+2)
			yl = 1;
		if(y > 238+64-16)
			yl = 0;
		for(i = 0; i < 0x4000; i++) {
			asm("mov r0, r0");
		}
	}

	return 0;
}

void chartou32(char* str, u32* o)
{
	int i;
	int len = strlen(str);
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


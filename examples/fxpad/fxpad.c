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
#include <eris/low/pad.h>

void printch(u32 sjis, u32 kram, int tall);
void printstr(u32* str, int x, int y, int tall);
void chartou32(char* str, u32* o);

static int padmap[16][2] = {
	{ 7-3, 0x40 },
	{ 7+7-3, 0x40 },
	{ 7+7+7-3, 0x40 },
	{ 7-3, 0x50 },
	{ 7+7-3, 0x50 },
	{ 7+7+7-3, 0x50 },
	{ 7+7-3, 0x60 },
	{ 7-3, 0x60 },
	{ 7-3, 0x30 },
	{ 7+7+7+7-3, 0x30 },
	{ 7+7-3, 0x30 },
	{ 7+7+7-3, 0x30 },
	{ 7+7+7-3, 0x60 },
	{ 0, 0 },
	{ 7+7+7+7-3, 0x60 },
	{ 1, 0 },
};

int main(int argc, char *argv[])
{
	u32 paddata;
	int i;
	u32 str[256];
	u32 pstr[3];
	u32 sstr[3];
	u16 microprog[16];

	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
	eris_tetsu_set_7up_palette(0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_3, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, 0);
	eris_king_set_bg_mode(KING_BGMODE_4_PAL, 0, 0, 0);
	eris_king_set_kram_pages(0, 0, 0, 0);

	for(i = 0; i < 16; i++) {
		microprog[i] = KING_CODE_NOP;
	}

	microprog[0] = KING_CODE_BG0_CG_0;
	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 16);
	eris_king_enable_microprogram();

	eris_tetsu_set_palette(0, 0x0088);
	eris_tetsu_set_palette(1, 0xE088);
	eris_tetsu_set_palette(2, 0xE0F0);
	eris_tetsu_set_palette(3, 0x602C);
	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16,
				TETSU_COLORS_16, 0, 0, 1, 0, 0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0SUB, 0, 0);
	eris_king_set_scroll(KING_BG0, 0, 0);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);
	eris_king_set_kram_read(0, 1);
	eris_king_set_kram_write(0, 1);
	// Clear BG0's RAM
	for(i = 0x0; i < 0x1E00; i++) {
		eris_king_kram_write(0);
	}
	chartou32("FX-PAD Test", str);
	printstr(str, 12, 0x8, 1);

	eris_low_pad_init(0);
	chartou32("+", pstr);
	chartou32(" ", sstr);
	for(;;) {
		if(eris_low_pad_data_ready(0)) {
			chartou32("|  UP  | DOWN | LEFT |RIGHT |", str);
			printstr(str, 0, 0x28, 0);
			chartou32("|   I  |  II  |  III |", str);
			printstr(str, 0, 0x38, 0);
			chartou32("|  IV  |   V  |  VI  |", str);
			printstr(str, 0, 0x48, 0);
			chartou32("|  RUN |SELECT|   A  |   B  |", str);
			printstr(str, 0, 0x58, 0);
			paddata = eris_low_pad_read_data(0);
			for(i = 0; i < 16; i++) {
				if(paddata & (1 << i))
					printstr(pstr, padmap[i][0], padmap[i][1], 0);
				else
					printstr(sstr, padmap[i][0], padmap[i][1], 0);
			}
			for(i = 0; i < 0x8000; i++) {
				asm("mov r0, r0");
			}
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


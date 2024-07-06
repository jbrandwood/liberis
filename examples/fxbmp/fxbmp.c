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
#include <eris/bkupmem.h>

void printch(u32 sjis, u32 kram, int tall);
void printstr(u32* str, int x, int y, int tall);
void chartou32(char* str, u32* o);
void printhex(void* data, int x, int y, int bytes, int addr, int tall);
char x1toa(int data);

int main(int argc, char *argv[])
{
	int i;
	u32 str[256];
	u16 microprog[16];
	u8 tmpbuf[0x80];
	u16 bps[2], sects[2];
	u16 *u16_ptr;

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
	eris_king_set_kram_write(0, 1);
	chartou32("Backup Memory", str);
	printstr(str, 8, 2, 1);

	eris_bkupmem_set_access(1, 1);
	eris_bkupmem_read(0, tmpbuf, 0, 0x40);
	printhex(tmpbuf, 0, 0x60, 0x40, 1, 0);
	eris_bkupmem_read(1, tmpbuf, 0, 0x40);
	printhex(tmpbuf, 0, 0xA0, 0x40, 1, 0);

	chartou32("Checking memory sizes...", str);
	printstr(str, 0, 0x22, 0);

	eris_bkupmem_read(0, tmpbuf, 0x13, 2);
	eris_bkupmem_read(0, tmpbuf + 2, 0xB, 2);

	u16_ptr = (u16*)(tmpbuf + 2);
	bps[0] = *u16_ptr;

	u16_ptr = (u16*)tmpbuf;
	sects[0] = *u16_ptr;

	bps[0] = ((bps[0] & 0x00FF) << 8) | ((bps[0] & 0xFF00) >> 8);
	sects[0] = ((sects[0] & 0x00FF) << 8) | ((sects[0] & 0xFF00) >> 8);

	eris_bkupmem_read(1, tmpbuf, 0x13, 2);
	eris_bkupmem_read(1, tmpbuf + 2, 0xB, 2);

	u16_ptr = (u16*)(tmpbuf + 2);
	bps[1] = *u16_ptr;

	u16_ptr = (u16*)tmpbuf;
	sects[1] = *u16_ptr;

	bps[1] = ((bps[1] & 0x00FF) << 8) | ((bps[1] & 0xFF00) >> 8);
	sects[1] = ((sects[1] & 0x00FF) << 8) | ((sects[1] & 0xFF00) >> 8);

	chartou32("          B/Sectors   Sectors", str);
	printstr(str, 0, 0x2A, 1);
	chartou32("Internal: ", str);
	printstr(str, 0, 0x3A, 1);
	chartou32("External: ", str);
	printstr(str, 0, 0x4A, 1);

	printhex(bps, 0xE, 0x3A, 2, 0, 1);
	printhex(sects, 0x19, 0x3A, 2, 0, 1);
	printhex(bps + 1, 0xE, 0x4A, 2, 0, 1);
	printhex(sects + 1, 0x19, 0x4A, 2, 0, 1);

	return 0;
}

char x1toa(int val)
{
	val &= 0xF;
	if(val >= 0xA)
		return (val - 0xA) + 'A';
	else
		return val + '0';
}


void printhex(void* data, int x, int y, int bytes, int addr, int tall)
{
	u32 ostr[256];
	char tmpstr[256];
	int tmpptr = 0;
	int i, l;
	for(i = 0; i < bytes; i += 8) {
		tmpptr = 0;
		if(addr) {
			tmpstr[tmpptr++] = x1toa(i >> 12);
			tmpstr[tmpptr++] = x1toa(i >> 8);
			tmpstr[tmpptr++] = x1toa(i >> 4);
			tmpstr[tmpptr++] = x1toa(i);
			tmpstr[tmpptr++] = ' ';
			tmpstr[tmpptr++] = ' ';
		}
		for(l = 0; (l < 8) && ((l + i) < bytes); l++) {
			tmpstr[tmpptr++] = x1toa(((char*)data)[i + l] >> 4);
			tmpstr[tmpptr++] = x1toa(((char*)data)[i + l]);
			tmpstr[tmpptr++] = ' ';
		}
		tmpstr[tmpptr] = 0;
		chartou32(tmpstr, ostr);
		printstr(ostr, x, y + i, tall);
	}
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


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

int main(int argc, char *argv[])
{
	int i;
	u32 str[256];
	u16 microprog[16];
	u32 paddata, lastpad;
	u8 scsimem[4096];
	u32 seekaddr = 0;
	u32 bytes = 0;

	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
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
	eris_low_pad_init(0);

	for(i = 0; i < 4096; i++) {
		scsimem[i] = 0;
	}

	chartou32("SCSI Test/Example", str);
	printstr(str, 10, 0, 1);
	for(;;) {
		if(eris_low_pad_data_ready(0)) {
			lastpad = paddata;
			paddata = eris_low_pad_read_data(0);
			if(paddata & (1 << 6) && !(lastpad & (1 << 6))) { // Select
				eris_low_scsi_abort();
			}
			if(paddata & (1 << 7) && !(lastpad & (1 << 7))) { // Run
				eris_low_scsi_reset();
			}
			if(paddata & (1 << 0) && !(lastpad & (1 << 0))) { // (I) Read to Buffer
				bytes = eris_cd_read(seekaddr, scsimem, 2048);
				seekaddr++;
			}
		}
		chartou32("Read bytes:", str);
		printstr(str, 0, 0x18, 0);
		str[0] = x1toa(bytes>>28);
		str[1] = x1toa(bytes>>24);
		str[2] = x1toa(bytes>>16);
		str[3] = x1toa(bytes>>12);
		str[4] = x1toa(bytes>>8);
		str[5] = x1toa(bytes>>4);
		str[6] = x1toa(bytes);
		str[7] = 0;
		printstr(str, 12, 0x18, 0);
		chartou32("Addr:", str);
		printstr(str, 0, 0x20, 0);
		str[0] = x1toa(seekaddr>>28);
		str[1] = x1toa(seekaddr>>24);
		str[2] = x1toa(seekaddr>>16);
		str[3] = x1toa(seekaddr>>12);
		str[4] = x1toa(seekaddr>>8);
		str[5] = x1toa(seekaddr>>4);
		str[6] = x1toa(seekaddr);
		str[7] = 0;
		printstr(str, 12, 0x20, 0);
		chartou32("Transfer buffer:", str);
		printstr(str, 0, 0x30, 0);
		printhex(scsimem, 0, 0x38, 200, 0, 0);
		str[0] = '<';
		str[1] = (i & 7) == 0 ? '*' : '-';
		str[2] = (i & 7) == 1 ? '*' : '-';
		str[3] = (i & 7) == 2 ? '*' : '-';
		str[4] = (i & 7) == 3 ? '*' : '-';
		str[5] = (i & 7) == 4 ? '*' : '-';
		str[6] = (i & 7) == 5 ? '*' : '-';
		str[7] = (i & 7) == 6 ? '*' : '-';
		str[8] = (i & 7) == 7 ? '*' : '-';
		str[9] = '>';
		str[10] = 0;
		i++;
		printstr(str, 10, 0x10, 0);
	}

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

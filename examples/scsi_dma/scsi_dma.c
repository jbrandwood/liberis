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

const u16 pornpal[] = {
0x79A7, 0x57A7, 0x35A7, 0x0088, 0xA687, 0xD987, 0x7387, 0x5187, 0x8C6A, 0xC16A, 0xDB79, 0x4F6B, 0xE779, 0xFF88, 0xA66B, 0x907C, 
};

int main(int argc, char *argv[])
{
	int i, l;
	u32 str[256];
	u16 microprog[16];
	int status;
	u32 paddata, lastpad;
	u8 scsicdb[32];
	u32 seekaddr = BINARY_LBA_PORN_BIN;
	u32 bytes = 0;

	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_3, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, 0);
	eris_king_set_bg_mode(KING_BGMODE_16_PAL, 0, 0, 0);
	eris_king_set_kram_pages(0, 0, 0, 0);

	for(i = 0; i < 16; i++) {
		microprog[i] = KING_CODE_NOP;
	}

	microprog[0] = KING_CODE_BG0_CG_0;
	microprog[1] = KING_CODE_BG0_CG_1;
	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 16);
	eris_king_enable_microprogram();

	for(i = 0; i < 16; i++) {
		eris_tetsu_set_palette(i, pornpal[i]);
	}

	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16,
				TETSU_COLORS_16, 0, 0, 1, 0, 0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0SUB, 0, 0);
	eris_king_set_scroll(KING_BG0, 0, 0);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);

	eris_king_set_kram_read(0, 1);
	eris_king_set_kram_write(0, 1);
	// Clear BG0's RAM
	for(i = 0x0; i < 0x7800; i++) {
		eris_king_kram_write(0);
	}
	eris_king_set_kram_write(0, 1);
	eris_low_pad_init(0);

	chartou32("SCSI Porn", str);
	printstr(str, 10, 0x8, 1);
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
			if(paddata & (1 << 1) && !(lastpad & (1 << 0))) { // (I) DMA to KRAM
				CLEAN_SCSICDB(SCSI_LOW_CMD_READ10, 10)
				scsicdb[2] = (seekaddr >> 24) & 0xFF;
				scsicdb[3] = (seekaddr >> 16) & 0xFF;
				scsicdb[4] = (seekaddr >>  8) & 0xFF;
				scsicdb[5] = (seekaddr >>  0) & 0xFF;
				scsicdb[8] = 0x21;
				eris_low_scsi_command(scsicdb, 10);
				for(l = 0; l < 2048; l++)
					asm volatile("mov r0, r0\n");
				while(!(in16(0x602) & 0x20))
					asm volatile("mov r0, r0\n");
				status = eris_low_scsi_status();
				eris_low_scsi_begin_dma(0x600, 0x6400);
				while(eris_low_scsi_check_dma())
					asm volatile("mov r0, r0\n");

				eris_low_scsi_finish_dma();

				status = eris_low_scsi_status();
				bytes = eris_low_scsi_get_phase();
			}
		}
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
	int len = strlen(str);
	for(i = 0; i < len; i++)
		o[i] = str[i];
	o[i] = 0;
}

void printstr(u32* str, int x, int y, int tall)
{
	int i;
	u32 kram = (x + (y << 5)) << 1;
	int len = strlen32(str);
	for(i = 0; i < len; i++) {
		printch(str[i], kram + (i<<1), tall);
	}
}

void printch(u32 sjis, u32 kram, int tall)
{
	u16 px;
	int x, y, l;
	u8* glyph = eris_romfont_get(sjis, tall ? ROMFONT_ANK_8x16 : ROMFONT_ANK_8x8);
	for(y = 0; y < (tall ? 16 : 8); y++) {
		eris_king_set_kram_write(kram + (y << 6), 1);
		for(l = 8-4; l >= 0; l -= 4) {
			px = 0;
			for(x = 0; x < 4; x++) {
				if((glyph[y] >> (x+l)) & 1) {
					px |= 1 << (x << 3);
				}
			}
			eris_king_kram_write(px);
		}
	}
}

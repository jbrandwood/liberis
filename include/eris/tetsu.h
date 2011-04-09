/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _LIBERIS_TETSU_H_
#define _LIBERIS_TETSU_H_

#include <eris/types.h>

typedef enum {
	TETSU_LINES_263 = 0,
	TETSU_LINES_262 = 1,
	TETSU_LINES_INTERLACED = 2,
	TETSU_LINES_UNKNOWN = 3,
} tetsu_lines;

typedef enum {
	TETSU_DOTCLOCK_5MHz = 0,
	TETUS_DOTCLOCK_7MHz = 1,
} tetsu_dotclock;

typedef enum {
	TETSU_COLORS_16 = 0,
	TETSU_COLORS_256 = 1,
} tetsu_colordepth;

typedef enum {
	TETSU_NO_COEFF = 0,
	TETSU_COEFF_1 = 1,
	TETSU_COEFF_2 = 2,
	TETSU_COEFF_3 = 3,
} tetsu_coeff;

void eris_tetsu_init();
void eris_tetsu_set_video_mode(tetsu_lines lines, int ext_sync,
			tetsu_dotclock dotclock, tetsu_colordepth bg_depth,
			tetsu_colordepth spr_depth, int bg7up_show,
			int spr7up_show, int bg0_disp, int bg1_disp,
			int bg2_disp, int bg3_disp, int rainbow_disp);
void eris_tetsu_set_palette(u16 pal_entry, u16 color);
void eris_tetsu_set_7up_palette(u8 bg7up, u8 spr7up);
void eris_tetsu_set_king_palette(u8 bg0, u8 bg1, u8 bg2, u8 bg3);
void eris_tetsu_set_rainbow_palette(u8 rainbow);
void eris_tetsu_set_priorities(u8 bg7up, u8 spr7up, u8 rainbow, u8 bg0,
				u8 bg1, u8 bg2, u8 bg3);
void eris_tetsu_set_chroma_key(u8 maxy, u8 miny, u8 maxu, u8 minu,
				u8 maxv, u8 minv);
void eris_tetsu_set_cellophane_color(u16 color);
void eris_tetsu_set_cellophane_sprites(int* banks); /* 16 element array */
void eris_tetsu_set_cellophane_control(int enable, int in_front,
				tetsu_coeff bg7up, tetsu_coeff spr7up,
				tetsu_coeff bg0, tetsu_coeff bg1,
				tetsu_coeff bg2, tetsu_coeff bg3,
				tetsu_coeff rainbow);
void eris_tetsu_set_cellophane_coeffs(int coeff, u8 ay, u8 au, u8 av,
				u8 by, u8 bu, u8 bv);

#endif


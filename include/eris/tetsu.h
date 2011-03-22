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

void eris_tetsu_set_video_mode(tetsu_lines lines, int ext_sync, tetsu_dotclock dotclock, tetsu_colordepth bg_depth,
				tetsu_colordepth spr_depth, int bg7up_show, int spr7up_show,
				int bg0_disp, int bg1_disp, int bg2_disp, int bg3_disp, int rainbow_disp);
void eris_tetsu_set_palette(u16 pal_entry, u16 color);
void eris_tetsu_set_palette_offset(u32 off);
void eris_tetsu_set_priorities(u8 bg, u8 spr, u8 rainbow, u8 bg0, u8 bg1, u8 bg2, u8 bg3);

#endif


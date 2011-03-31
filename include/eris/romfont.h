#ifndef _LIBERIS_ROMFONT_H_
#define _LIBERIS_ROMFONT_H_

#include <eris/types.h>

typedef enum {
	ROMFONT_KANJI_16x16 = 0,
	ROMFONT_KANJI_12x12 = 1,
	ROMFONT_ANK_8x16 = 2,
	ROMFONT_ANK_6x12 = 3,
	ROMFONT_ANK_8x8 = 4,
	ROMFONT_ANK_8x12 = 5,
} romfont_type;

void* eris_romfont_get(u32 sjis, romfont_type type);

#endif


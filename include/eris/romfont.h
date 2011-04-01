/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

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

u8* eris_romfont_get(u32 sjis, romfont_type type);

#endif


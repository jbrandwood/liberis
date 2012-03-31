/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>
Copyright (C) 2011                           Nodtveidt <david@eponasoft.com>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief High-level access to the 7up video chips.
 */

#ifndef _LIBERIS_7UP_H_
#define _LIBERIS_7UP_H_

typedef enum { 
	SUP_MAP_32X32 = 0,
	SUP_MAP_64X32 = 1,
	SUP_MAP_128X32 = 2,
	SUP_MAP_32X64 = 4, 
	SUP_MAP_64X64 = 5,
	SUP_MAP_128X64 = 7 
} sup_mapsize;

// General
void eris_sup_init(int chip, int auto_update);
void eris_sup_set(int chip);
void eris_sup_show(int spr, int bg);

// Sprites
void eris_sup_spr_set(int spr);
void eris_sup_spr_x(s16 x);
void eris_sup_spr_y(s16 y);
void eris_sup_spr_xy(s16 x, s16 y);
void eris_sup_spr_pattern(u16 pat);
void eris_sup_spr_pri(int pri);
void eris_sup_spr_pal(int pal);
void eris_sup_spr_ctrl(u16 mask, u16 val);
void eris_sup_spr_create(s16 x, s16 y, u16 pat, u16 ctrl);
s16 eris_sup_spr_get_x(void);
s16 eris_sup_spr_get_y(void);
u16 eris_sup_spr_get_pattern(void);
u16 eris_sup_spr_get_ctrl(void);
int eris_sup_spr_get_pal(void);

// BG
void eris_sup_bg_set_size(sup_mapsize size);
void eris_sup_bg_set_tile(int x, int y, u16 tile);
void eris_sup_bg_load_tiles(int w, int h, u16 *tiles);
void eris_sup_bg_scroll_x(s16 x);
void eris_sup_bg_scroll_y(s16 y);
void eris_sup_bg_scroll_xy(s16 x, s16 y);
u16 eris_sup_bg_get_tile(int x, int y);
s16 eris_sup_bg_get_scroll_x(void);
s16 eris_sup_bg_get_scroll_y(void);

#endif

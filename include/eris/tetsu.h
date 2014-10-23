/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Controls the NEW Iron Guanyin (Tetsu kannon) chip (Video Controller)
 */

#ifndef _LIBERIS_TETSU_H_
#define _LIBERIS_TETSU_H_

#include <eris/types.h>

/*! \brief Number of vertical lines to display.
 */
typedef enum {
	TETSU_LINES_263        = 0, /*!< 263 lines. A little flickery, but less cross-talk. */
	TETSU_LINES_262        = 1, /*!< 262 lines. No flicker, but lots of cross-talk. */
	TETSU_LINES_INTERLACED = 2, /*!< Interlaced. Very flickery. */
	TETSU_LINES_UNKNOWN    = 3, /*!< Interlaced + 1/2dot shift?. Flickery^2 */
} tetsu_lines;

/*! \brief Dot clock. Determines screen width.
 */
typedef enum {
	TETSU_DOTCLOCK_5MHz = 0, /*!< ~5MHz dot clock. 256px wide. */
	TETUS_DOTCLOCK_7MHz = 1, /*!< ~7MHz dot clock. 320px wide. */
} tetsu_dotclock;

/*! \brief Amount of colors (to display?).
 */
typedef enum {
	TETSU_COLORS_16  = 0, /*!< 16 colors */
	TETSU_COLORS_256 = 1, /*!< 256 colors */
} tetsu_colordepth;

/*! \brief Which coefficient to use for cellophane.
 */
typedef enum {
	TETSU_NO_COEFF = 0, /*!< No coefficient (no cellophane). */
	TETSU_COEFF_1  = 1, /*!< Coefficient 1 */
	TETSU_COEFF_2  = 2, /*!< Coefficient 2 */
	TETSU_COEFF_3  = 3, /*!< Coefficient 3 */
} tetsu_coeff;

/*! \brief Initialize the NEW Iron Guanyin.
 */
void eris_tetsu_init();
/*! \brief Setup the video mode.
 *
 * \param lines Vertical line mode.
 * \param ext_sync Whether to use external sync.
 * \param dotclock The dotclock to run at.
 * \param bg_depth Color depth of 7up backgrounds.
 * \param spr_depth Color depth of 7up sprites.
 * \param bg7up_show Whether 7up backgrounds are displayed.
 * \param spr7up_show Whether 7up sprites are displayed.
 * \param bg0_disp Whether KING BG0 is displayed.
 * \param bg1_disp Whether KING BG1 is displayed.
 * \param bg2_disp Whether KING BG2 is displayed.
 * \param bg3_disp Whether KING BG3 is displayed.
 * \param rainbow_disp Whether the RAINBOW output is displayed.
 */
void eris_tetsu_set_video_mode(tetsu_lines lines, int ext_sync,
			tetsu_dotclock dotclock, tetsu_colordepth bg_depth,
			tetsu_colordepth spr_depth, int bg7up_show,
			int spr7up_show, int bg0_disp, int bg1_disp,
			int bg2_disp, int bg3_disp, int rainbow_disp);
/*! \brief Set a palette entry.
 *
 * \param pal_entry Which palette entry to set the color of.
 * \param color The color to set. In Y8U4V4 format.
 */
void eris_tetsu_set_palette(u16 pal_entry, u16 color);
/*! \brief Which palette to use for the 7up chips.
 *
 * Palettes are actually indexes into the palette which is the first color
 * to the chip. For example, if bg7up was 4, then the 4th palette entry would
 * be color 0, 5th would be 1, etc.
 * \param bg7up Which palette to use for 7up backgrounds.
 * \param spr7up Which palette to use for 7up sprites.
 */
void eris_tetsu_set_7up_palette(u16 bg7up, u16 spr7up);
/*! \brief Which palette to use for the KING backgrounds.
 *
 * Palettes are actually indexes into the palette which is the first color
 * to the chip. For example, if bg0 was 4, then the 4th palette entry would
 * be color 0, 5th would be 1, etc.
 * \param bg0 Which palette to use for KING background 0.
 * \param bg1 Which palette to use for KING background 1.
 * \param bg2 Which palette to use for KING background 2.
 * \param bg3 Which palette to use for KING background 3.
 */
void eris_tetsu_set_king_palette(u16 bg0, u16 bg1, u16 bg2, u16 bg3);
/*! \brief Which palette to use for RAIBOW.
 *
 * Palettes are actually indexes into the palette which is the first color
 * to the chip. For example, if raibow was 4, then the 4th palette entry would
 * be color 0, 5th would be 1, etc.
 * \param rainbow Which palette to use for RAIBOW.
 */
void eris_tetsu_set_rainbow_palette(u16 rainbow);
/*! \brief Set layer priorities.
 *
 * \param bg7up Priority for the 7up backgrounds. (0 ~ 7)
 * \param spr7up Priority for the 7up sprites. (0 ~ 7)
 * \param bg0 Priority for KING BG0. (0 ~ 7)
 * \param bg1 Priority for KING BG1. (0 ~ 7)
 * \param bg2 Priority for KING BG2. (0 ~ 7)
 * \param bg3 Priority for KING BG3. (0 ~ 7)
 * \param rainbow Priority for RAINBOW. (0 ~ 7)
 */
void eris_tetsu_set_priorities(u8 bg7up, u8 spr7up, u8 bg0, u8 bg1, u8 bg2,
				u8 bg3, u8 rainbow);
/*! \brief Set chroma color key values.
 *
 * Disable each colorkey by setting the minimum higher than the maximum.
 * \param maxy Maximum Y.
 * \param miny Minimum Y.
 * \param maxu Maximum U.
 * \param minu Minimum U.
 * \param maxv Maximum V.
 * \param minv Minimum V.
 */
void eris_tetsu_set_chroma_key(u8 maxy, u8 miny, u8 maxu, u8 minu,
				u8 maxv, u8 minv);
/*! \brief Get the current raster.
 *
 * \return Current raster.
 */
int eris_tetsu_get_raster(void);
/*! \brief Check which field is being displayed for interlaced mode.
 *
 * \return 1 if displaying odd field, 0 for even field.
 */
int eris_tetsu_get_field(void);
/*! \brief Checks if we are currently displaying (not in H or V blank)
 *
 * \return 1 if we are displaying, 0 for in blank.
 */
int eris_tetsu_is_displaying(void);
/*! \brief Sets the constant color for the cellophane.
 *
 * This color is either the color of the cellophane (in the case of it being
 * in front) or the color of the background (in the case of it being in back).
 * \param color Color in Y8U4V4 format.
 */
void eris_tetsu_set_cellophane_color(u16 color);
/*! \brief Sets cellophane activity on sprites.
 *
 * \param banks A 16-element array of 1s or 0s that contains whether that color
 *              palette bank receives cellophane treatment.
 */
void eris_tetsu_set_cellophane_sprites(int* banks); /* 16 element array */
/*! \brief Set cellophane control.
 *
 * \param enable Whether the cellophane is being used or not.
 * \param in_front Whether the cellophane is the constant color, or the active
 *                 surfaces. If 1, it is the constant color.
 * \param bg7up Which coefficient to use for 7up backgrounds.
 * \param spr7up Which coefficient to use for 7up sprites.
 * \param bg0 Which coefficient to use for KING BG0.
 * \param bg1 Which coefficient to use for KING BG1.
 * \param bg2 Which coefficient to use for KING BG2.
 * \param bg3 Which coefficient to use for KING BG3.
 * \param rainbow Which coefficient to use for RAINBOW output.
 */
void eris_tetsu_set_cellophane_control(int enable, int in_front,
				tetsu_coeff bg7up, tetsu_coeff spr7up,
				tetsu_coeff bg0, tetsu_coeff bg1,
				tetsu_coeff bg2, tetsu_coeff bg3,
				tetsu_coeff rainbow);
/*! \brief Set a cellophane coefficient.
 *
 * For coefficient information, see hardware documentation.
 * \param coeff Which coefficient to set the information for. (1 ~ 3)
 * \param ay Y component of the A coefficient.
 * \param au U component of the A coefficient.
 * \param av V component of the A coefficient.
 * \param by Y component of the B coefficient.
 * \param bu U component of the B coefficient.
 * \param bv V component of the B coefficient.
 */
void eris_tetsu_set_cellophane_coeffs(int coeff, u8 ay, u8 au, u8 av,
				u8 by, u8 bu, u8 bv);

#endif


/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Low-level access to the 7up video chips.
 */

#ifndef _LIBERIS_LOW_7UP_H_
#define _LIBERIS_LOW_7UP_H_

/*! \brief Map sizes for the backgrounds.
 */
typedef enum {
	ERIS_LOW_7UP_MAP_32X32 = 0, /*!< 32x32 tile map. (256x256 pixel) */
	ERIS_LOW_7UP_MAP_64X32 = 1, /*!< 64x32 tile map. (512x256 pixel) */
	ERIS_LOW_7UP_MAP_128X32 = 2, /*!< 128x32 tile map. (1024x256 pixel) */
	ERIS_LOW_7UP_MAP_32X64 = 4, /*!< 32x64 tile map. (256x512 pixel) */
	ERIS_LOW_7UP_MAP_64X64 = 5, /*!< 64x64 tile map. (512x512 pixel) */
	ERIS_LOW_7UP_MAP_128X64 = 7 /*!< 128x64 tile map. (1024x512 pixel) */
} eris_low_7up_mapsize;

/*! \brief Initialize a 7up.
 *
 * \param chip Which 7up to initialize. (0 ~ 1)
 */
void eris_low_7up_init(int chip);
/*! \brief Setup a 7up's video mode.
 *
 * \param chip Which 7up to configure. (0 ~ 1)
 * \param hdispstrt The start of horizontal display, -1. (0 ~ 127)
 * \param hsyncwid The length of hsync. (0 ~ 31)
 * \param hdispend The end of horizontal display, -1. (0 ~ 127)
 * \param hdispwid The length of horizontal display, -1. (0 ~ 127)
 * \param vdispstrt The start of vertical display, -2. (0 ~ 255)
 * \param vsyncwid The length of vsync. (0 ~ 31)
 * \param vdispwid The length of vertical display, -1. (0 ~ 512)
 * \param vdispend The end of vertical display. (0 ~ 255)
 */
void eris_low_7up_set_video_mode(int chip, int hdispstrt, int hsyncwid,
				int hdispend, int hdispwid, int vdispstrt,
				int vsyncwid, int vdispwid, int vdispend);
/*! \brief Set the VRAM write address for a 7up chip.
 *
 * \param chip Which 7up to set the write address for. (0 ~ 1)
 * \param addr New VRAM address for write pointer.
 */
void eris_low_7up_set_vram_write(int chip, u16 addr);
/*! \brief Write to VRAM on a 7up chip.
 *
 * \param chip Which 7up to write data to. (0 ~ 1)
 * \param data Data to write.
 */
void eris_low_7up_vram_write(int chip, u16 data);
/*! \brief Set the VRAM read address for a 7up chip.
 *
 * \param chip Which 7up to set the read address for. (0 ~ 1)
 * \param addr New VRAM address for read pointer.
 */
void eris_low_7up_set_vram_read(int chip, u16 addr);
/*! \brief Read from VRAM from a 7up chip.
 *
 * \param chip Which 7up to read data from. (0 ~ 1)
 * \return The daata located at the read pointer address.
 */
u16 eris_low_7up_vram_read(int chip);
/*! \brief Set controls for a 7up chip.
 *
 * \param chip Which 7up to set controls for. (0 ~ 1)
 * \param increment How much to increment on every VRAM read/write. See
 *                  hardwre documentation for which values.
 * \param bg_show Whether the BG should show or not.
 * \param spr_show Whether sprites should show or not.
 */
void eris_low_7up_set_control(int chip, int increment, int bg_show,
				int spr_show);
/*! \brief Set interrupt information for a 7up chip.
 *
 * \param chip Which 7up to set interrupts for. (0 ~ 1)
 * \param vblank_irq Whether an IRQ should fire on VBlank.
 * \param raster_irq Whether an IRQ should fire on raster match.
 * \param excess_spr Whether an IRQ should fire on too many sprites per line.
 * \param spr_collision Whether an IRQ should fire on a sprite overlapping
 *                      sprite 0.
 */
void eris_low_7up_set_interrupts(int chip, int vblank_irq, int raster_irq,
				int excess_spr, int spr_collision);
/*! \brief Get the current raster being displayed by a 7up.
 *
 * \param chip Which 7up to get the raster from. (0 ~ 1)
 * \return The currently displaying raster.
 */
u16 eris_low_7up_get_raster(int chip);
/*! \brief Scroll a 7up background.
 *
 * \param chip Which 7up to scroll. (0 ~ 1)
 * \param x Top-left X coordinate of the background.
 * \param y Top-left Y coordinate of the background.
 */
void eris_low_7up_set_scroll(int chip, u16 x, u16 y);
/*! \brief Perform a 7up DMA.
 *
 * \param chip Which 7up to DMA on. (0 ~ 1)
 * \param src The source address of the DMA.
 * \param dst The destination of the DMA.
 * \param len How many 16bit words to transfer.
 */
void eris_low_7up_do_dma(int chip, u16 src, u16 dst, u16 len);
/*! \brief Setup the DMA on a 7up.
 *
 * \param chip Which 7up to setup the DMA on. (0 ~ 1)
 * \param satb_repeat Whether to continually DMA the SATB after a transfer.
 * \param src_dec If 1, decrement the source address for each transfer.
 *                Otherwise, increment it.
 * \param dst_dec If 1, decrement the destination address for each transfer.
 *                Otherwise, increment it.
 * \param vram_irq Fire an IRQ at the end of a VRAM->VRAM transfer.
 * \param satb_irq Fire an IRq at the end of a VRAM->SATB transfer.
 */
void eris_low_7up_setup_dma(int chip, int satb_repeat, int src_dec,
				int dst_dec, int vram_irq, int satb_irq);
/*! \brief Sets the Sprite Attribute Table Block address.
 *
 * Setting the address starts a VRAM->SATB DMA.
 * \param chip Which 7up to set the SATB for. (0 ~ 1)
 * \param addr VRAM address for the start of the SATB.
 */
void eris_low_7up_set_satb_address(int chip, u16 addr);
/*! \brief Set access width information.
 *
 * See the hardware documentation for more information.
 * \param chip Which 7up to set access width information for. (0 ~ 1)
 * \param cg_mode Which character generation is used on vram_px_w = 3.
 * \param mapsize Size of the background map.
 * \param spr_px_w Sprite pixel width. See hardware documentation. (0 ~ 3)
 * \param vram_px_w VRAM pixel width. See hardware documentation. (0 ~ 3)
 */
void eris_low_7up_set_access_width(int chip, int cg_mode,
				eris_low_7up_mapsize mapsize, int spr_px_w,
				int vram_px_w);

#endif


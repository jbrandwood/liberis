/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Controls the KING processor.
 */

#ifndef _LIBERIS_KING_H_
#define _LIBERIS_KING_H_

#include <eris/types.h>

/*! \brief KING microprogram opcode generator.
 *
 * \brief off Offset.
 * \brief type Type of access.
 * \brief rot Rotate processing.
 * \brief bg Which background to operate on.
 * \brief nop Whether this is a NOP opcode or not.
 */
#define KING_CODE(off, type, rot, bg, nop) \
		(((off & 7) << 0) | ((type & 3) << 3) | ((rot & 1) << 5) | \
		((bg & 3) << 6) | ((nop & 1) << 8))

/*! \brief KING microprogram opcodes.
 */
typedef enum {
	KING_CODE_BG0_CG_0 = KING_CODE(0, 0, 0, 0, 0), /*!< Background 0, CG, +0 */
	KING_CODE_BG0_CG_1 = KING_CODE(1, 0, 0, 0, 0), /*!< Background 0, CG, +1 */
	KING_CODE_BG0_CG_2 = KING_CODE(2, 0, 0, 0, 0), /*!< Background 0, CG, +2 */
	KING_CODE_BG0_CG_3 = KING_CODE(3, 0, 0, 0, 0), /*!< Background 0, CG, +3 */
	KING_CODE_BG0_CG_4 = KING_CODE(4, 0, 0, 0, 0), /*!< Background 0, CG, +4 */
	KING_CODE_BG0_CG_5 = KING_CODE(5, 0, 0, 0, 0), /*!< Background 0, CG, +5 */
	KING_CODE_BG0_CG_6 = KING_CODE(6, 0, 0, 0, 0), /*!< Background 0, CG, +6 */
	KING_CODE_BG0_CG_7 = KING_CODE(7, 0, 0, 0, 0), /*!< Background 0, CG, +7 */
	KING_CODE_BG0_BATCG_0 = KING_CODE(0, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +0 */
	KING_CODE_BG0_BATCG_1 = KING_CODE(1, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +1 */
	KING_CODE_BG0_BATCG_2 = KING_CODE(2, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +2 */
	KING_CODE_BG0_BATCG_3 = KING_CODE(3, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +3 */
	KING_CODE_BG0_BATCG_4 = KING_CODE(4, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +4 */
	KING_CODE_BG0_BATCG_5 = KING_CODE(5, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +5 */
	KING_CODE_BG0_BATCG_6 = KING_CODE(6, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +6 */
	KING_CODE_BG0_BATCG_7 = KING_CODE(7, 1, 0, 0, 0), /*!< Background 0, BAT->CG, +7 */
	KING_CODE_BG0_BAT_0 = KING_CODE(0, 2, 0, 0, 0), /*!< Background 0, BAT, +0 */
	KING_CODE_BG0_BAT_1 = KING_CODE(1, 2, 0, 0, 0), /*!< Background 0, BAT, +1 */
	KING_CODE_BG0_BAT_2 = KING_CODE(2, 2, 0, 0, 0), /*!< Background 0, BAT, +2 */
	KING_CODE_BG0_BAT_3 = KING_CODE(3, 2, 0, 0, 0), /*!< Background 0, BAT, +3 */
	KING_CODE_BG0_BAT_4 = KING_CODE(4, 2, 0, 0, 0), /*!< Background 0, BAT, +4 */
	KING_CODE_BG0_BAT_5 = KING_CODE(5, 2, 0, 0, 0), /*!< Background 0, BAT, +5 */
	KING_CODE_BG0_BAT_6 = KING_CODE(6, 2, 0, 0, 0), /*!< Background 0, BAT, +6 */
	KING_CODE_BG0_BAT_7 = KING_CODE(7, 2, 0, 0, 0), /*!< Background 0, BAT, +7 */
	KING_CODE_BG1_CG_0 = KING_CODE(0, 0, 0, 1, 0), /*!< Background 1, CG, +0 */
	KING_CODE_BG1_CG_1 = KING_CODE(1, 0, 0, 1, 0), /*!< Background 1, CG, +1 */
	KING_CODE_BG1_CG_2 = KING_CODE(2, 0, 0, 1, 0), /*!< Background 1, CG, +2 */
	KING_CODE_BG1_CG_3 = KING_CODE(3, 0, 0, 1, 0), /*!< Background 1, CG, +3 */
	KING_CODE_BG1_CG_4 = KING_CODE(4, 0, 0, 1, 0), /*!< Background 1, CG, +4 */
	KING_CODE_BG1_CG_5 = KING_CODE(5, 0, 0, 1, 0), /*!< Background 1, CG, +5 */
	KING_CODE_BG1_CG_6 = KING_CODE(6, 0, 0, 1, 0), /*!< Background 1, CG, +6 */
	KING_CODE_BG1_CG_7 = KING_CODE(7, 0, 0, 1, 0), /*!< Background 1, CG, +7 */
	KING_CODE_BG1_BATCG_0 = KING_CODE(0, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +0 */
	KING_CODE_BG1_BATCG_1 = KING_CODE(1, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +1 */
	KING_CODE_BG1_BATCG_2 = KING_CODE(2, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +2 */
	KING_CODE_BG1_BATCG_3 = KING_CODE(3, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +3 */
	KING_CODE_BG1_BATCG_4 = KING_CODE(4, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +4 */
	KING_CODE_BG1_BATCG_5 = KING_CODE(5, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +5 */
	KING_CODE_BG1_BATCG_6 = KING_CODE(6, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +6 */
	KING_CODE_BG1_BATCG_7 = KING_CODE(7, 1, 0, 1, 0), /*!< Background 1, BAT->CG, +7 */
	KING_CODE_BG1_BAT_0 = KING_CODE(0, 2, 0, 1, 0), /*!< Background 1, BAT, +0 */
	KING_CODE_BG1_BAT_1 = KING_CODE(1, 2, 0, 1, 0), /*!< Background 1, BAT, +1 */
	KING_CODE_BG1_BAT_2 = KING_CODE(2, 2, 0, 1, 0), /*!< Background 1, BAT, +2 */
	KING_CODE_BG1_BAT_3 = KING_CODE(3, 2, 0, 1, 0), /*!< Background 1, BAT, +3 */
	KING_CODE_BG1_BAT_4 = KING_CODE(4, 2, 0, 1, 0), /*!< Background 1, BAT, +4 */
	KING_CODE_BG1_BAT_5 = KING_CODE(5, 2, 0, 1, 0), /*!< Background 1, BAT, +5 */
	KING_CODE_BG1_BAT_6 = KING_CODE(6, 2, 0, 1, 0), /*!< Background 1, BAT, +6 */
	KING_CODE_BG1_BAT_7 = KING_CODE(7, 2, 0, 1, 0), /*!< Background 1, BAT, +7 */
	KING_CODE_BG2_CG_0 = KING_CODE(0, 0, 0, 2, 0), /*!< Background 2, CG, +0 */
	KING_CODE_BG2_CG_1 = KING_CODE(1, 0, 0, 2, 0), /*!< Background 2, CG, +1 */
	KING_CODE_BG2_CG_2 = KING_CODE(2, 0, 0, 2, 0), /*!< Background 2, CG, +2 */
	KING_CODE_BG2_CG_3 = KING_CODE(3, 0, 0, 2, 0), /*!< Background 2, CG, +3 */
	KING_CODE_BG2_CG_4 = KING_CODE(4, 0, 0, 2, 0), /*!< Background 2, CG, +4 */
	KING_CODE_BG2_CG_5 = KING_CODE(5, 0, 0, 2, 0), /*!< Background 2, CG, +5 */
	KING_CODE_BG2_CG_6 = KING_CODE(6, 0, 0, 2, 0), /*!< Background 2, CG, +6 */
	KING_CODE_BG2_CG_7 = KING_CODE(7, 0, 0, 2, 0), /*!< Background 2, CG, +7 */
	KING_CODE_BG2_BATCG_0 = KING_CODE(0, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +0 */
	KING_CODE_BG2_BATCG_1 = KING_CODE(1, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +1 */
	KING_CODE_BG2_BATCG_2 = KING_CODE(2, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +2 */
	KING_CODE_BG2_BATCG_3 = KING_CODE(3, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +3 */
	KING_CODE_BG2_BATCG_4 = KING_CODE(4, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +4 */
	KING_CODE_BG2_BATCG_5 = KING_CODE(5, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +5 */
	KING_CODE_BG2_BATCG_6 = KING_CODE(6, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +6 */
	KING_CODE_BG2_BATCG_7 = KING_CODE(7, 1, 0, 2, 0), /*!< Background 2, BAT->CG, +7 */
	KING_CODE_BG2_BAT_0 = KING_CODE(0, 2, 0, 2, 0), /*!< Background 2, BAT, +0 */
	KING_CODE_BG2_BAT_1 = KING_CODE(1, 2, 0, 2, 0), /*!< Background 2, BAT, +1 */
	KING_CODE_BG2_BAT_2 = KING_CODE(2, 2, 0, 2, 0), /*!< Background 2, BAT, +2 */
	KING_CODE_BG2_BAT_3 = KING_CODE(3, 2, 0, 2, 0), /*!< Background 2, BAT, +3 */
	KING_CODE_BG2_BAT_4 = KING_CODE(4, 2, 0, 2, 0), /*!< Background 2, BAT, +4 */
	KING_CODE_BG2_BAT_5 = KING_CODE(5, 2, 0, 2, 0), /*!< Background 2, BAT, +5 */
	KING_CODE_BG2_BAT_6 = KING_CODE(6, 2, 0, 2, 0), /*!< Background 2, BAT, +6 */
	KING_CODE_BG2_BAT_7 = KING_CODE(7, 2, 0, 2, 0), /*!< Background 2, BAT, +7 */
	KING_CODE_BG3_CG_0 = KING_CODE(0, 0, 0, 3, 0), /*!< Background 3, CG, +0 */
	KING_CODE_BG3_CG_1 = KING_CODE(1, 0, 0, 3, 0), /*!< Background 3, CG, +1 */
	KING_CODE_BG3_CG_2 = KING_CODE(2, 0, 0, 3, 0), /*!< Background 3, CG, +2 */
	KING_CODE_BG3_CG_3 = KING_CODE(3, 0, 0, 3, 0), /*!< Background 3, CG, +3 */
	KING_CODE_BG3_CG_4 = KING_CODE(4, 0, 0, 3, 0), /*!< Background 3, CG, +4 */
	KING_CODE_BG3_CG_5 = KING_CODE(5, 0, 0, 3, 0), /*!< Background 3, CG, +5 */
	KING_CODE_BG3_CG_6 = KING_CODE(6, 0, 0, 3, 0), /*!< Background 3, CG, +6 */
	KING_CODE_BG3_CG_7 = KING_CODE(7, 0, 0, 3, 0), /*!< Background 3, CG, +7 */
	KING_CODE_BG3_BATCG_0 = KING_CODE(0, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +0 */
	KING_CODE_BG3_BATCG_1 = KING_CODE(1, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +1 */
	KING_CODE_BG3_BATCG_2 = KING_CODE(2, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +2 */
	KING_CODE_BG3_BATCG_3 = KING_CODE(3, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +3 */
	KING_CODE_BG3_BATCG_4 = KING_CODE(4, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +4 */
	KING_CODE_BG3_BATCG_5 = KING_CODE(5, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +5 */
	KING_CODE_BG3_BATCG_6 = KING_CODE(6, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +6 */
	KING_CODE_BG3_BATCG_7 = KING_CODE(7, 1, 0, 3, 0), /*!< Background 3, BAT->CG, +7 */
	KING_CODE_BG3_BAT_0 = KING_CODE(0, 2, 0, 3, 0), /*!< Background 3, BAT, +0 */
	KING_CODE_BG3_BAT_1 = KING_CODE(1, 2, 0, 3, 0), /*!< Background 3, BAT, +1 */
	KING_CODE_BG3_BAT_2 = KING_CODE(2, 2, 0, 3, 0), /*!< Background 3, BAT, +2 */
	KING_CODE_BG3_BAT_3 = KING_CODE(3, 2, 0, 3, 0), /*!< Background 3, BAT, +3 */
	KING_CODE_BG3_BAT_4 = KING_CODE(4, 2, 0, 3, 0), /*!< Background 3, BAT, +4 */
	KING_CODE_BG3_BAT_5 = KING_CODE(5, 2, 0, 3, 0), /*!< Background 3, BAT, +5 */
	KING_CODE_BG3_BAT_6 = KING_CODE(6, 2, 0, 3, 0), /*!< Background 3, BAT, +6 */
	KING_CODE_BG3_BAT_7 = KING_CODE(7, 2, 0, 3, 0), /*!< Background 3, BAT, +7 */
	KING_CODE_ROTATE = KING_CODE(0, 0, 1, 0, 0), /*!< Rotate background */
	KING_CODE_NOP = KING_CODE(0, 0, 0, 0, 1), /*!< No Operation */
} king_opcode;

/*! \brief Color mode for a KING background.
 */
typedef enum {
	KING_BGMODE_4_PAL = 0x1, /*!< Paletted 4 color mode */
	KING_BGMODE_16_PAL = 0x2, /*!< Paletted 16 color mode */
	KING_BGMODE_256_PAL = 0x3, /*!< Paletted 256 color mode */
	KING_BGMODE_64K = 0x4, /*!< Non-paletted 65536 color mode */
	KING_BGMODE_16M = 0x5, /*!< Non-paletted 16777216 color mode */
	KING_BGMODE_BAT = 0x8, /*!< OR this for a Block Attribute Table mode */
	KING_BGMODE_64K_BAT_EXTDOT = 0xE, /*!< Block Attribute Tabled 65536
						color mode. EXTDOT? */
	KING_BGMODE_16M_BAT_EXTDOT = 0xF, /*!< Block Attribute Tabled 16777216
						color mode. EXTDOT? */
} king_bgmode;

/*! \brief Background priority.
 */
typedef enum {
	KING_BGPRIO_HIDE = 0, /*!< The background is hidden. */
	KING_BGPRIO_0 = 1, /*!< Farthest back background. */
	KING_BGPRIO_1 = 2, /*!< 2nd to back background. */
	KING_BGPRIO_2 = 3, /*!< 2nd to front background. */
	KING_BGPRIO_3 = 4, /*!< Farthest forward background. */
} king_bgprio;

/*! \brief Background axis size.
 */
typedef enum {
	KING_BGSIZE_8 = 3, /*!< 8px axis. */
	KING_BGSIZE_16 = 4, /*!< 16px axis. */
	KING_BGSIZE_32 = 5, /*!< 32px axis. */
	KING_BGSIZE_64 = 6, /*!< 64px axis. */
	KING_BGSIZE_128 = 7, /*!< 128px axis. */
	KING_BGSIZE_256 = 8, /*!< 256px axis. */
	KING_BGSIZE_512 = 9, /*!< 512px axis. */
	KING_BGSIZE_1024 = 10, /*!< 1024px axis. Only available on BG0. */
} king_bgsize;

/*! \brief KING background.
 */
typedef enum {
	KING_BG0 = 0, /*!< Background 0 */
	KING_BG0SUB = 1, /*!< Background 0 (sub) */
	KING_BG1 = 2, /*!< Background 1 */
	KING_BG2 = 3, /*!< Background 2 */
	KING_BG3 = 4, /*!< Background 3 */
} king_bg;

/*! \brief Initialize KING.
 */
void eris_king_init(void);
/*! \brief Set KRAM read address.
 *
 * \param addr New read address.
 * \param incr How many 16bit words to increase on every read.
 */
void eris_king_set_kram_read(u32 addr, int incr);
/*! \brief Set KRAM write address.
 *
 * \param addr New write address.
 * \param incr How many 16bit words to increase on every write.
 */
void eris_king_set_kram_write(u32 addr, int incr);
/*! \brief Read from KRAM.
 *
 * \return Value read from KRAM.
 */
u16 eris_king_kram_read(void);
/*! \brief Write to KRAM.
 *
 * \param data Value to write to KRAM.
 */
void eris_king_kram_write(u16 data);
/*! \brief Set the KRAM page for various peripherals.
 *
 * \param scsi The KRAM page used for SCSI. (0 ~ 1)
 * \param bg The KRAM page used for backgrounds. (0 ~ 1)
 * \param rainbow The KRAM page used for RAINBOW. (0 ~ 1)
 * \param adpcm The KRAM page used for the ADPCM. (0 ~ 1)
 */
void eris_king_set_kram_pages(u8 scsi, u8 bg, u8 rainbow, u8 adpcm);
/*! \brief Set color modes for the backgrounds.
 *
 * \param bg0 Color mode for background 0.
 * \param bg1 Color mode for background 1.
 * \param bg2 Color mode for background 2.
 * \param bg3 Color mode for background 3.
 */
void eris_king_set_bg_mode(king_bgmode bg0, king_bgmode bg1, king_bgmode bg2,
			king_bgmode bg3);
/*! \brief Set priorities for the backgrounds.
 *
 * \param bg0 Priority for background 0.
 * \param bg1 Priority for background 1.
 * \param bg2 Priority for background 2.
 * \param bg3 Priority for background 3.
 * \param bgrot Background 0 rotation enable.
 */
void eris_king_set_bg_prio(king_bgprio bg0, king_bgprio bg1, king_bgprio bg2,
			king_bgprio bg3, int bgrot);
/*! \brief Set background sizes.
 *
 * \param bg Which background to set the size of (BG0SUB is not allowed).
 * \param h Height of the background.
 * \param w Width of the background.
 * \param sub_h Height of the sub background (BG0 only).
 * \param sub_w Width of the sub background (BG0 only).
 */
void eris_king_set_bg_size(king_bg bg, king_bgsize h, king_bgsize w,
			king_bgsize sub_h, king_bgsize sub_w);
/*! \brief Set background BAT and CG addresses.
 *
 * \param bg Which background to set the size of.
 * \param bat The KRAM address for the BAT.
 * \param cg The KRAM address of the CG.
 */
void eris_king_set_bat_cg_addr(king_bg bg, u32 bat, u32 cg);
/*! \brief Set background scrolling.
 *
 * \param bg Which background to scroll (BG0SUB is not allowed).
 * \param x Signed X value correlating to the upper-left corner of the BG.
 * \param y Signed Y value correlating to the upper-left corner of the BG.
 */
void eris_king_set_scroll(king_bg bg, s16 x, s16 y);
/*! \brief Write the KING microprogram.
 *
 * \param data Array containing microprogram.
 * \param addr Address to start writing the microprogram.
 * \param len How many opcodes to write.
 */
void eris_king_write_microprogram(u16* data, u8 addr, u8 len);
/*! \brief Write the KING microprogram.
 *
 * \param data Opcode to fill microprogram with.
 * \param addr Address to start writing the microprogram.
 * \param len How many opcodes to write.
 */
void eris_king_fill_microprogram(u16 data, u8 addr, u8 len);
/*! \brief Enable the KING microprogram.
 */
void eris_king_enable_microprogram(void);
/*! \brief Disable the KING microprogram.
 */
void eris_king_disable_microprogram(void);

/* SCSI */
typedef enum {
	KING_SCSI_SEL = 0x02,
	KING_SCSI_IO = 0x04,
	KING_SCSI_CD = 0x08,
	KING_SCSI_MSG = 0x10,
	KING_SCSI_REQ = 0x20,
	KING_SCSI_BUSY = 0x40,
	KING_SCSI_RESET = 0x80
} king_scsi_status;
/*! \brief Get SCSI status.
 *
 * \return Returns the current state of the SCSI drive.
 */
int eris_king_scsi_status(void);
/*! \brief Reset the SCSI drive.
 */
void eris_king_scsi_reset(void);
/*! \brief Read data from the SCSI drive.
 *
 * \param buf Buffer to read into.
 * \param maxlen Maximum length to read from.
 * \return Bytes read.
 */
u32 eris_king_scsi_data_in(u8 *buf, u32 maxlen);
/*! \brief Write data to the SCSI drive.
 *
 * \param buf Buffer to write from.
 * \param len Length of the buffer.
 */
u32 eris_king_scsi_data_out(u8 *buf, u32 len);
/*! \brief Abort the current SCSI operation.
 */
void eris_king_scsi_abort(void);
/*! \brief Send a command to the SCSI drive.
 *
 * \param cdb Command bytes.
 * \param len Length of the command data.
 */
int eris_king_scsi_command(u8 *cdb, u32 len);
// Get Error?

#endif


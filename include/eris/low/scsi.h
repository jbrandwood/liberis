/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Low-level control of the KING processor's SCSI controller.
 */

#ifndef _LIBERIS_LOW_SCSI_H_
#define _LIBERIS_LOW_SCSI_H_

#include <eris/types.h>

typedef enum
{
	SCSI_LOW_PHASE_BUS_FREE    = 0,
	SCSI_LOW_PHASE_SELECT      = 1,
	SCSI_LOW_PHASE_DATA_OUT    = 2,
	SCSI_LOW_PHASE_DATA_IN     = 3,
	SCSI_LOW_PHASE_COMMAND     = 4,
	SCSI_LOW_PHASE_STATUS      = 5,
	SCSI_LOW_PHASE_MESSAGE_OUT = 6,
	SCSI_LOW_PHASE_MESSAGE_IN  = 7,
	SCSI_LOW_PHASE_ILLEGAL     = 8
} scsi_low_phase;
typedef enum
{
	// Our special statuses, indicating that the command is still in-progress.
	SCSI_LOW_STATUS_MISC            = -5,
	SCSI_LOW_STATUS_NEED_MESSAGE    = -4,
	SCSI_LOW_STATUS_NEED_DATA       = -3,
	SCSI_LOW_STATUS_HAVE_DATA       = -2,
	SCSI_LOW_STATUS_IN_PROGRESS     = -1,

	SCSI_LOW_STATUS_GOOD            = 0x0,
	SCSI_LOW_STATUS_CHECK_CONDITION = 0x2,
	SCSI_LOW_STATUS_CONDITION_MET   = 0x4,
	SCSI_LOW_STATUS_BUSY            = 0x6,
	SCSI_LOW_STATUS_INTERMEDIATE    = 0x10
} scsi_low_status;
typedef enum {
	SCSI_LOW_CMD_TEST_UNIT_READY  = 0x00,
	SCSI_LOW_CMD_REQ_SENSE        = 0x03,
	SCSI_LOW_CMD_READ10           = 0x28,
	SCSI_LOW_CMD_SEEK10           = 0x2B,
	SCSI_LOW_CMD_PREFETCH10       = 0x34,
	SCSI_LOW_CMD_READ_SUBQ        = 0x42,
	SCSI_LOW_CMD_READ_TOC         = 0x43,
	SCSI_LOW_CMD_READ_HEADER      = 0x44,
	SCSI_LOW_CMD_PLAY_AUDIO_INDEX = 0x48,
	SCSI_LOW_CMD_PAUSE            = 0x4B,
} scsi_low_cmd;
/*! \brief Get SCSI phase.
 * \return Returns the current phase of the SCSI drive.
 */
scsi_low_phase eris_low_scsi_get_phase(void);
/*! \brief Get SCSI status.
 *
 * \return Returns the current state of the SCSI drive.
 */
scsi_low_status eris_low_scsi_status(void);
/*! \brief Reset the SCSI drive.
 */
void eris_low_scsi_reset(void);
/*! \brief Read data from the SCSI drive.
 *
 * \param buf Buffer to read into.
 * \param maxlen Maximum length to read from.
 * \return Bytes read.
 */
u32 eris_low_scsi_data_in(u8 *buf, u32 maxlen);
/*! \brief Write data to the SCSI drive.
 *
 * \param buf Buffer to write from.
 * \param len Length of the buffer.
 */
u32 eris_low_scsi_data_out(u8 *buf, u32 len);
/*! \brief Begin a DMA from the SCSI drive.
 *
 * \param kram_addr Address in KRAM to DMA to.
 * \param size How many bytes to transfer (must be a multiple of 2).
 */
void eris_low_scsi_begin_dma(u32 kram_addr, u32 size);
/*! \brief Check if a DMA is in progress.
 *
 * \return 1 if a DMA is in progress, 0 if not.
 */
int eris_low_scsi_check_dma(void);
/*! \brief Finish a DMA from the SCSI drive.
 */
void eris_low_scsi_finish_dma(void);
/*! \brief Abort the current SCSI operation.
 */
void eris_low_scsi_abort(void);
/*! \brief Send a command to the SCSI drive.
 *
 * \param cdb Command bytes.
 * \param len Length of the command data.
 */
int eris_low_scsi_command(u8 *cdb, u32 len);
// Get Error?

#endif


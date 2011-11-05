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

typedef enum {
	SCSI_LOW_SEL   = 0x02,
	SCSI_LOW_IO    = 0x04,
	SCSI_LOW_CD    = 0x08,
	SCSI_LOW_MSG   = 0x10,
	SCSI_LOW_REQ   = 0x20,
	SCSI_LOW_BUSY  = 0x40,
	SCSI_LOW_RESET = 0x80
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
	SCSI_LOW_CMD_READ12           = 0xA8,
} scsi_low_cmd;
/*! \brief Get SCSI phase.
 * \return Returns the current phase of the SCSI drive.
 */
int eris_low_scsi_get_phase(void);
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


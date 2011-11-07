/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief High-level control of the CD drive.
 */

#ifndef _LIBERIS_CD_H_
#define _LIBERIS_CD_H_

#include <eris/types.h>

/*! \brief Reset the CD drive.
 */
void eris_cd_reset(void);
/*! \brief Read data from the CD drive.
 *
 * \param lba LBA of the sector to start reading from.
 * \param buf Buffer to store the data into. Must have ((size+2047) & ~0x2047) bytes
 *            available!
 * \param size How many bytes to read.
 */
u32 eris_cd_read(u32 lba, u8 *buf, u32 size);
/*! \brief Read data from the CD drive into KRAM.
 *
 * \param lba LBA of the sector to start reading from.
 * \param kram_addr Address in KRAM to start writing into.
 * \param size How many bytes to read.
 */
void eris_cd_read_kram(u32 lba, u32 kram_addr, u32 size);

#endif

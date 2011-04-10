/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Backup memory control.
 */

#ifndef _LIBERIS_BKUPMEM_H_
#define _LIBERIS_BKUPMEM_H_

#include <eris/types.h>

/*! \brief Set access bits.
 *
 * These bits control access to external and internal backup memory.
 * \param b0 Bit0 of the access bits. (External or Internal?)
 * \param b1 Bit1 of the access bits. (External or Internal?)
 */
void eris_bkupmem_set_access(int b0, int b1);
/*! \brief Read backup memory.
 *
 * \param ext If 1, read from external memory. 0 is internal memory.
 * \param buf Buffer to store the data.
 * \param addr Address to start reading from.
 * \param len Bytes to read.
 * \sa eris_bkupmem_write()
 */
void eris_bkupmem_read(int ext, u8* buf, u32 addr, u32 len);
/*! \brief Write backup memory.
 *
 * \param ext If 1, write to external memory. 0 is internal memory.
 * \param buf Buffer holding the data to write.
 * \param addr Address to start writing to.
 * \param len Bytes to write.
 * \sa eris_bkupmem_read()
 */
void eris_bkupmem_write(int ext, u8* buf, u32 addr, u32 len);

#endif


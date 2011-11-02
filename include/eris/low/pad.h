/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief Low-level access to FX-PADs.
 */

#ifndef _LIBERIS_LOW_PAD_H_
#define _LIBERIS_LOW_PAD_H_

#include <eris/types.h>

/*! \brief Initialize a pad.
 *
 * \param pad The pad to initialize. (0 ~ 1)
 */
void eris_low_pad_init(int pad);

/*! \brief Read pad status.
 *
 * \param pad The pad to read the status of. (0 ~ 1)
 * \return The pad's status.
 */
u16 eris_low_pad_read_status(int pad);
/*! \brief Read pad data.
 *
 * \param pad The pad to read data from. (0 ~ 1)
 * \return The pad's data.
 */
u32 eris_low_pad_read_data(int pad);
/*! \brief Check if pad has data ready.
 *
 * \param pad The pad to check. (0 ~ 1)
 * \return If there is data ready, returns 1. Otherwise, it returns 0.
 */
int eris_low_pad_data_ready(int pad);
/*! \brief Write pad control.
 *
 * \param pad The pad to write the control of. (0 ~ 1)
 * \param ctl The control data to be written.
 */
void eris_low_pad_write_control(int pad, u16 ctl);
/*! \brief Write pad data.
 *
 * \param pad The pad to write data to. (0 ~ 1)
 * \param data The data to be written.
 */
void eris_low_pad_write_data(int pad, u32 data);

#endif


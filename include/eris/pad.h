/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file
 * \brief High-level access to pads.
 */

#ifndef _LIBERIS_PAD_H_
#define _LIBERIS_PAD_H_

#include <eris/types.h>

typedef enum {
	PAD_TYPE_NONE = 0,
	PAD_TYPE_MOUSE = 13,
	PAD_TYPE_MULTITAP = 14,
	PAD_TYPE_FXPAD = 15
} pad_type;
/*! \brief Initialize a pad.
 *
 * \param pad The pad to initialize. (0 ~ 1)
 */
void eris_pad_init(int pad);
/*! \brief Read the pad data.
 *
 * \param pad The pad to read. (0 ~ 1)
 * \return The current state of the pad.
 */
u32 eris_pad_read(int pad);
/*! \brief Get the pad type.
 *
 * \param pad The pad to read. (0 ~ 1)
 * \return The pad's type.
 */
pad_type eris_pad_type(int pad);
/*! \brief Check if a pad is connected.
 *
 * \param pad The pad to check. (0 ~ 1)
 * \return 1 if there is a pad, 0 if not.
 */
int eris_pad_connected(int pad);

#endif


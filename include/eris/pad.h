/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _LIBERIS_PAD_H_
#define _LIBERIS_PAD_H_

#include <eris/types.h>

void eris_pad_init(int pad);

u16 eris_pad_read_status(int pad);
u32 eris_pad_read_data(int pad);
int eris_pad_data_ready(int pad);
void eris_pad_write_control(int pad, u16 ctl);
void eris_pad_write_data(int pad, u32 data);

#endif


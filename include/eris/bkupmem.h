/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _LIBERIS_BKUPMEM_H_
#define _LIBERIS_BKUPMEM_H_

#include <eris/types.h>

void eris_bkupmem_set_access(int b0, int b1);
void eris_bkupmem_read(int ext, u8* buf, u32 addr, u32 len);
void eris_bkupmem_write(int ext, u8* buf, u32 addr, u32 len);

#endif


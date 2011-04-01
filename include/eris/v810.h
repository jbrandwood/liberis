/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _LIBERIS_V810_H_
#define _LIBERIS_V810_H_

#include <eris/types.h>

/* Cache functions */

void cache_enable(void);
void cache_disable(void);
void cache_clear(int entry, int count);
/* Must be aligned to 256 byte boundary */
void cache_dump(void* dumpaddr);
void cache_restore(void* restaddr);


/* IRQ functions */

int irq_enable(void);
int irq_disable(void);
void irq_set_level(int lv);
void irq_set_mask(int mask);
void irq_set_priority(u32 prio);
int irq_get_level(void);
u16 irq_get_mask(void);
u32 irq_get_priority(void);


/* string.h functions */

void memset32(void* addr, u32 val, int size);
void memset16(void* addr, u16 val, int size);
void memset(void* addr, u8 val, int size);
void memcpy32(void* dst, void* src, int size);
void memcpy16(void* dst, void* src, int size);
void memcpy(void* dst, void* src, int size);
int memcmp32(void* mem1, void* mem2, int size);
int memcmp16(void* mem1, void* mem2, int size);
int memcmp(void* mem1, void* mem2, int size);
int strlen32(u32* str);
int strlen16(u16* str);
int strlen(char* str);

/* Port functions */
void out32(u32 port, u32 data);
void out16(u32 port, u16 data);
void out8(u32 port, u8 data);
u32 in32(u32 port);
u16 in16(u32 port);
u8 in8(u32 port);

#endif


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


/* Memory functions */

void memset32(void* addr, u32 val, int size);
void memset16(void* addr, u16 val, int size);
void memset(void* addr, u8 val, int size);
void memcpy32(void* dst, void* src, int size);
void memcpy16(void* dst, void* src, int size);
void memcpy(void* dst, void* src, int size);
int memcmp32(void* mem1, void* mem2, int size);
int memcmp16(void* mem1, void* mem2, int size);
int memcmp(void* mem1, void* mem2, int size);


/* Port functions */
void out32(u32 port, u32 data);
void out16(u32 port, u16 data);
void out8(u32 port, u8 data);

#endif


#ifndef _LIBERIS_PAD_H_
#define _LIBERIS_PAD_H_

#include <eris/types.h>

u16 eris_pad_read_status(int pad);
u32 eris_pad_read_data(int pad);
void eris_pad_write_control(int pad, u16 ctl);

#endif


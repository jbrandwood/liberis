/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _LIBERIS_STD_H_
#define _LIBERIS_STD_H_

#include <eris/types.h>

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
void strcpy32(u32* dst, u32* src);
void strcpy16(u16* dst, u16* src);
void strcpy(char* dst, char* src);
int strcmp32(u32* str1, u32* str2);
int strcmp16(u16* str1, u16* str2);
int strcmp(char* str1, char* str2);
int strnlen32(u32* str, int len);
int strnlen16(u16* str, int len);
int strnlen(char* str, int len);
void strncpy32(u32* dst, u32* src, int len);
void strncpy16(u16* dst, u16* src, int len);
void strncpy(char* dst, char* src, int len);
int strncmp32(u32* str1, u32* str2, int len);
int strncmp16(u16* str1, u16* str2, int len);
int strncmp(char* str1, char* str2, int len);


#endif


/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*! \file stdarg.h
 *  \brief V810 stdarg implementation.
 */

#ifndef	_STDARG_H_
#define	_STDARG_H_

#ifndef _VA_LIST
#define _VA_LIST
typedef char *va_list;
#endif

#define va_start(list, start) ((void)((list) = (sizeof(start)<4 ? \
				(char *)((int *)&(start)+1) : (char *)(&(start)+1))))
#define va_end(list) ((void)0)
#define va_arg(list, mode) *(mode *)(&(list = (char*)(((int)list + 7)&~3U))[-4])

#endif


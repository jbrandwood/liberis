/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  Pad control                                                          []  *
 *****************************************************************************/
	.global	_eris_pad_read_status
	.global	_eris_pad_read_data
	.global	_eris_pad_write_control

_eris_pad_read_status:
	shl	7, r6
	in.h	0[r6], r10
	jmp	[lp]

_eris_pad_read_data:
	shl	7, r6
	ori	0x40, r6, r6
	in.w	0[r6], r10
	jmp	[lp]

_eris_pad_write_control:
	shl	7, r6
	out.h	r7, 0[r6]
	jmp	[lp]


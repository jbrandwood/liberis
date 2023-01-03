/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  Low-level pad control                                                []  *
 *****************************************************************************/
	.global	_eris_low_pad_init
	.global	_eris_low_pad_read_status
	.global	_eris_low_pad_read_data
	.global	_eris_low_pad_data_ready
	.global	_eris_low_pad_write_control
	.global	_eris_low_pad_write_data

_eris_low_pad_init:
	shl	7, r6
	out.h	r0, 0[r6]
	out.w	r0, 0x40[r6]
	in.h	0[r6], r10
	jmp	[lp]

_eris_low_pad_read_status:
	shl	7, r6
	in.h	0[r6], r10
	jmp	[lp]

_eris_low_pad_read_data:
	shl	7, r6
	mov	7, r10		/* reset multitap and request data from pad */
	out.h	r10, 0[r6]

wait_for_input_ready:
        in.h	0[r6], r10	/* r10 is now the status register value */
        andi	9, r10, r10
        cmp	1, r10
        bz	wait_for_input_ready

	in.w	0x40[r6], r10	/* and now r10 is the pad data value */
	jmp	[lp]

/* This function seems to be of no use */
_eris_low_pad_data_ready:
	shl	7, r6
	in.h	0[r6], r10
	andi	0x9, r10, r10
	cmp	1, r10
	be	1f
	mov	1, r10
	jmp	[lp]
1:	mov	0, r10
	jmp	[lp]

_eris_low_pad_write_control:
	shl	7, r6
	out.h	r7, 0[r6]
	jmp	[lp]

_eris_low_pad_write_data:
	shl	7, r6
	out.w	r7, 0x40[r6]
	jmp	[lp]


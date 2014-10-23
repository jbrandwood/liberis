/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  Timer handling                                                       []  *
 *****************************************************************************/
	.global	_eris_timer_init
	.global	_eris_timer_set_period
	.global	_eris_timer_read_counter
	.global	_eris_timer_ack_irq
	.global	_eris_timer_read_control
	.global	_eris_timer_write_control
	.global	_eris_timer_start
	.global	_eris_timer_stop

_eris_timer_init:
	out.h	r0, 0xF00[r0]
	out.h	r0, 0xF80[r0]
	jmp	[lp]

_eris_timer_set_period:
	out.h	r6, 0xF80[r0]
	jmp	[lp]

_eris_timer_read_counter:
	in.h	0xFC0[r0], r10
	jmp	[lp]

_eris_timer_ack_irq:
	in.h	0xF00[r0], r10
	andi	~4, r10, r10
	out.h	r10, 0xF00[r0]
	jmp	[lp]

_eris_timer_read_control:
	in.h	0xF00[r0], r10
	jmp	[lp]

_eris_timer_write_control:
	out.h	r6, 0xF00[r0]
	jmp	[lp]

_eris_timer_start:
	in.h	0xF00[r0], r10
	andi	~3, r10, r10
	ori	2, r6, r6
	or	r6, r10
	out.h	r10, 0xF00[r0]
	jmp	[lp]

_eris_timer_stop:
	in.h	0xF00[r0], r10
	andi	~1, r10, r10
	out.h	r10, 0xF00[r0]
	jmp	[lp]

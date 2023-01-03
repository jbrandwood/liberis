/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  High-level pad control                                               []  *
 *****************************************************************************/
	.global	_eris_pad_init
	.global	_eris_pad_read
	.global _eris_pad_type
	.global	_eris_pad_connected

eris_pad_states:
	.word	0
	.word	0

_eris_pad_init:
	andi	1, r6, r6
	mov	r6, r10
	shl	2, r10
	movhi	hi(eris_pad_states), r0, r11
	movea	lo(eris_pad_states), r11, r11
	add	r10, r11
	st.w	r0, 0[r11]
	jr	_eris_low_pad_init

_eris_pad_read:
	mov	lp, r18
	andi	1, r6, r6
	mov	r6, r17
	mov	r6, r16
	shl	2, r16
	movhi	hi(eris_pad_states), r0, r15
	movea	lo(eris_pad_states), r15, r15
	add	r16, r15

	mov	r17, r6
	jal	_eris_low_pad_read_data
	st.w	r10, 0[r15]

	mov	r18, lp
	jmp	[lp]

_eris_pad_type:
	mov	lp, r18
	andi	1, r6, r6
	mov	r6, r17
	mov	r6, r16
	shl	2, r16
	movhi	hi(eris_pad_states), r0, r15
	movea	lo(eris_pad_states), r15, r15
	add	r16, r15

	mov	r17, r6
	jal	_eris_low_pad_read_data
	st.w	r10, 0[r15]
	br	2f

2:	shr	28, r10
	mov	r18, lp
	jmp	[lp]

_eris_pad_connected:
	mov	lp, r14
	jal	_eris_pad_type
	cmp	0, r10
	setf	nz, r10
	mov	r14, lp
	jmp	[lp]

/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  Cache functions                                                     []   *
 *****************************************************************************/
	.global _cache_enable
	.global	_cache_disable
	.global _cache_clear
	.global _cache_dump
	.global _cache_restore

_cache_enable:
	stsr	CHCW, r10
	ori	2, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_disable:
	mov	-3, r11
	stsr	CHCW, r10
	and	r11, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_clear:
	stsr	CHCW, r10
	shl	8, r7
	shl	20, r6
	or	r7, r10
	or	r6, r10
	ori	1, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_dump:
	stsr	CHCW, r10
	shl	8, r6
	or	r6, r10
	ori	16, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_restore:
	stsr	CHCW, r10
	shl	8, r6
	or	r6, r10
	ori	32, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

/*****************************************************************************
 *  IRQ functions                                                        []  *
 *****************************************************************************/
	.global _irq_enable
	.global	_irq_disable
	.global	_irq_restore
	.global _irq_set_level
	.global	_irq_set_mask
	.global	_irq_set_priority
	.global	_irq_set_handler
	.global	_irq_get_level
	.global	_irq_get_mask
	.global	_irq_get_priority

_irq_enable:
	stsr	PSW, r10
	movea	0x1000, r0, r12
	not	r12, r11
	and	r10, r11
	and	r12, r10
	shr	12, r10
	ldsr	r11, PSW
	jmp	[lp]

_irq_disable:
	stsr	PSW, r10
	movea	0x1000, r0, r11
	and	r11, r10
	or	r10, r11
	ldsr	r11, PSW
	jmp	[lp]

_irq_restore:
	andi	1, r6, r6
	movea	0x1000, r0, r11
	not	r11, r11
	stsr	PSW, r10
	and	r10, r11
	shl	12, r6
	or	r6, r11
	ldsr	r11, PSW
	jmp	[lp]

_irq_set_level:
	stsr	PSW, r10
	andi	0xF, r6, r6
	shl	16, r6
	movhi	0xF, r0, r11
	not	r11, r12
	and	r10, r12
	or	r6, r12
	ldsr	r12, PSW
	jmp	[lp]

_irq_set_mask:
	out.h	r6, 0xE40[r0]
	jmp	[lp]

_irq_set_priority:
	mov	r6, r11
	shr	16, r11
	out.h	r11, 0xEC0[r0]
	out.h	r6, 0xE80[r0]
	jmp	[lp]

_irq_set_handler:
	add	-7, r6
	shl	2, r6
	movea	0x7FE0, r0, r10
	sub	r6, r10
	st.w	r7, 0[r10]
	jmp	[lp]

_irq_get_level:
	stsr	PSW, r10
	movhi	0xF, r0, r11
	and	r11, r10
	jmp	[lp]

_irq_get_mask:
	in.h	0xE40[r0], r10
	jmp	[lp]

_irq_get_priority:
	in.h	0xEC0[r0], r11
	shl	16, r11
	in.h	0xE80[r0], r10
	or	r11, r10
	jmp	[lp]

/*****************************************************************************
 *  Port functions                                                       []  *
 *****************************************************************************/
	.global	_out32
	.global	_out16
	.global _out8
	.global _in32
	.global _in16
	.global _in8

_out32:
	out.w	r7, 0[r6]
	jmp	[lp]

_out16:
	out.h	r7, 0[r6]
	jmp	[lp]

_out8:
	out.b	r7, 0[r6]
	jmp	[lp]

_in32:
	in.w	0[r6], r10
	jmp	[lp]

_in16:
	in.h	0[r6], r10
	jmp	[lp]

_in8:
	in.b	0[r6], r10
	jmp	[lp]



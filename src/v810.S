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
	mov	~2, r11
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
	.global	_irq_level_enable
	.global	_irq_level_disable
	.global	_irq_set_raw_handler

.irp param, 0,1,2,3,4,5,6,7
_irq_shim\param:
	add	-0x10, sp
	st.w	lp, 0x00[sp]
	stsr	sr0, lp
	st.w	lp, 0x04[sp]
	stsr	sr1, lp
	st.w	lp, 0x08[sp]
	st.w	r1, 0x0C[sp]
	addi	-0x3C, sp, sp
	st.w	r6, 0x00[sp]
	st.w	r7, 0x04[sp]
	st.w	r8, 0x08[sp]
	st.w	r9, 0x0C[sp]
	st.w	r10, 0x10[sp]
	st.w	r11, 0x14[sp]
	st.w	r12, 0x18[sp]
	st.w	r13, 0x1C[sp]
	st.w	r14, 0x20[sp]
	st.w	r15, 0x24[sp]
	st.w	r16, 0x28[sp]
	st.w	r17, 0x2C[sp]
	st.w	r18, 0x30[sp]
	st.w	r19, 0x34[sp]
	st.w	r30, 0x38[sp]
	movhi	hi(_irq_handlers+(\param *4)), r0, r10
	ld.w	lo(_irq_handlers+(\param *4))[r10], r10
	jal	.+4
	add	4, lp
	jmp	[r10]
	ld.w	0x38[sp], r30
	ld.w	0x34[sp], r19
	ld.w	0x30[sp], r18
	ld.w	0x2C[sp], r17
	ld.w	0x28[sp], r16
	ld.w	0x24[sp], r15
	ld.w	0x20[sp], r14
	ld.w	0x1C[sp], r13
	ld.w	0x18[sp], r12
	ld.w	0x14[sp], r11
	ld.w	0x10[sp], r10
	ld.w	0x0C[sp], r9
	ld.w	0x08[sp], r8
	ld.w	0x04[sp], r7
	ld.w	0x00[sp], r6
	addi	0x3C, sp, sp
	ld.w	0x0C[sp], r1
	ld.w	0x08[sp], lp
	ldsr	lp, sr1
	ld.w	0x04[sp], lp
	ldsr	lp, sr0
	ld.w	0x00[sp], lp
	addi	0x10, sp, sp
	reti
.endr

	.align	4
_irq_shim_addr:
	.long	_irq_shim0
	.long	_irq_shim1
	.long	_irq_shim2
	.long	_irq_shim3
	.long	_irq_shim4
	.long	_irq_shim5
	.long	_irq_shim6
	.long	_irq_shim7

_irq_handlers:
	.long	0,0,0,0, 0,0,0,0

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
	addi	-7, r6, r6
	shl	2, r6
	movea	0x7FE0, r0, r10
	sub	r6, r10

	addi	-4, r6, r6
	movhi	hi(_irq_handlers), r6, r11
	st.w	r7, lo(_irq_handlers)[r11]

	movhi	hi(_irq_shim_addr), r6, r11
	ld.w	lo(_irq_shim_addr)[r11], r11

	sub	r10, r11
	st.h	r11, 2[r10]
	shr	16, r11
	andi	0x03FF, r11, r11
	ori	0xA800, r11, r11
	st.h	r11, 0[r10]

	mov	0, r6
	movea	128, r0, r7
	jr	_cache_clear

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

_irq_level_enable:
	in.h	0xE40[r0], r10
	add	-8, r6
	movea	~0x80, r0, r11
	shr	r6, r11
	and	r11, r10
	out.h	r10, 0xE40[r0]
	jmp	[lp]

_irq_level_disable:
	in.h	0xE40[r0], r10
	add	-8, r6
	movea	0x80, r0, r11
	shr	r6, r11
	or	r11, r10
	out.h	r10, 0xE40[r0]
	jmp	[lp]

_irq_set_raw_handler:
	addi	-7, r6, r6
	shl	2, r6
	movea	0x7FE0, r0, r10
	sub	r6, r10

	sub	r10, r7
	st.h	r7, 2[r10]
	shr	16, r7
	andi	0x03FF, r7, r7
	ori	0xA800, r7, r7
	st.h	r7, 0[r10]

	mov	0, r6
	movea	128, r0, r7
	jr	_cache_clear

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



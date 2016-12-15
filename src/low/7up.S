/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  Low-level 7up functions                                              []  *
 *****************************************************************************/
	.global	_eris_low_sup_init
	.global	_eris_low_sup_set_video_mode
	.global	_eris_low_sup_get_video_mode
	.global	_eris_low_sup_set_vram_write
	.global	_eris_low_sup_vram_write
	.global	_eris_low_sup_set_vram_read
	.global	_eris_low_sup_vram_read
	.global	_eris_low_sup_set_control
	.global	_eris_low_sup_get_control
	.global	_eris_low_sup_set_interrupts
	.global _eris_low_sup_set_interrupt_raster
	.global _eris_low_sup_set_scroll
	.global _eris_low_sup_get_scroll
	.global	_eris_low_sup_do_dma
	.global	_eris_low_sup_setup_dma
	.global	_eris_low_sup_set_satb_address
	.global	_eris_low_sup_set_access_width
	.global	_eris_low_sup_get_access_width

.macro	set_rrg	reg, ch, tmp
	movea	0x400, \ch, \tmp
	out.h	\reg, 0[\tmp]
.endm

.macro	set_reg	reg, ch, tmp1, tmp2
	movea	\reg, r0, \tmp2
	set_rrg	\tmp2, \ch, \tmp1
.endm

_eris_low_sup_init:
	shl	8, r6
	set_reg	0, r6, r10, r11
	out.h	r0, 4[r10]
	set_reg	1, r6, r10, r11
	out.h	r0, 4[r10]
	set_reg	2, r6, r10, r11
	movhi	1, r0, r8
1:
	out.h	r0, 4[r10]
	out.h	r0, 4[r10]
	out.h	r0, 4[r10]
	out.h	r0, 4[r10]
	add	-4, r8
	bne	1b
	set_reg	0, r6, r10, r11
	out.h	r0, 4[r10]
	movea	0x14, r0, r8
2:
	add	-1, r8
	set_rrg	r8, r6, r10
	out.h	r0, 4[r10]
	cmp	5, r8
	bne	2b
	jmp	[lp]

_eris_low_sup_set_video_mode:
	shl	8, r6
	ld.w	0[sp], r10
	ld.w	4[sp], r11
	ld.w	8[sp], r12
	ld.w	12[sp], r13
	ld.w	16[sp], r14
	set_reg	0xA, r6, r15, r16
	shl	8, r7
	or	r7, r8
	out.h	r8, 4[r15]
	set_reg	0xB, r6, r15, r16
	shl	8, r9
	or	r9, r10
	out.h	r10, 4[r15]
	set_reg	0xC, r6, r15, r16
	shl	8, r11
	or	r11, r12
	out.h	r12, 4[r15]
	set_reg	0xD, r6, r15, r16
	out.h	r13, 4[r15]
	set_reg	0xE, r6, r15, r16
	out.h	r14, 4[r15]
	jmp	[lp]

_eris_low_sup_get_video_mode:
	shl	8, r6
	ld.w	0[sp], r10
	ld.w	4[sp], r11
	ld.w	8[sp], r12
	ld.w	12[sp], r13
	ld.w	16[sp], r14

	set_reg	0xA, r6, r15, r16
	in.h	4[r15], r16
	andi	0xFF, r16, r17
	st.w	r17, 0[r8]
	shr	8, r16
	st.w	r16, 0[r7]

	set_reg	0xB, r6, r15, r16
	in.h	4[r15], r16
	andi	0xFF, r16, r17
	st.w	r17, 0[r10]
	shr	8, r16
	st.w	r16, 0[r9]

	set_reg	0xC, r6, r15, r16
	in.h	4[r15], r16
	andi	0xFF, r16, r17
	st.w	r17, 0[r12]
	shr	8, r16
	st.w	r16, 0[r11]

	set_reg	0xD, r6, r15, r16
	in.h	4[r15], r16
	st.w	r16, 0[r13]

	set_reg	0xD, r6, r15, r16
	in.h	4[r15], r16
	st.w	r16, 0[r14]

	jmp	[lp]

/* This will eventually be the set video mode in the high level */
_eris_7up_set_video_mode:
	shl	8, r6
	set_reg	0xA, r6, r10, r11
	movea	0x202, r0, r12
	movea	0x41F, r0, r13
	cmp	r0, r7
	be	1f
	addi	0x101, r12, r12
	addi	0xC, r13, r13
1:
	out.h	r12, 4[r10]
	set_reg	0xB, r6, r10, r11
	out.h	r13, 4[r10]
	movea	240, r0, r12
	sub	r8, r12
	mov	r12, r13
	shr	1, r12
	addi	0x11, r12, r12
	shl	8, r12
	add	2, r12
	set_reg	0xC, r6, r10, r11
	out.h	r12, 4[r10]
	mov	r8, r12
	add	-1, r12
	set_reg	0xD, r6, r10, r11
	out.h	r12, 4[r10]
	add	1, r13
	shr	1, r13
	add	2, r13
	set_reg	0xE, r6, r10, r11
	out.h	r13, 4[r10]
	jmp	[lp]

_eris_low_sup_set_vram_write:
	shl	8, r6
	set_rrg	r0, r6, r10
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_vram_write:
	shl	8, r6
	set_reg	2, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_set_vram_read:
	shl	8, r6
	set_reg	1, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_vram_read:
	shl	8, r6
	set_reg	2, r6, r10, r11
	in.h	4[r10], r10
	jmp	[lp]

_eris_low_sup_set_control:
	shl	8, r6
	set_reg	5, r6, r10, r11
	in.h	4[r10], r12
	andi	0xE73F, r12, r12
	shl	11, r7
	shl	7, r8
	shl	6, r9
	or	r9, r7
	or	r8, r7
	or	r12, r7
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_get_control:
	shl	8, r6
	set_reg	5, r6, r10, r11
	in.h	4[r10], r12
	mov	r12, r13
	shr	11, r13
	andi	3, r13, r13
	st.w	r13, 0[r7]
	mov	r12, r13
	shr	7, r13
	andi	1, r13, r13
	st.w	r13, 0[r8]
	shr	6, r12
	andi	1, r12, r12
	st.w	r12, 0[r9]
	jmp	[lp]

_eris_low_sup_set_interrupts:
	ld.w	0[sp], r13
	shl	8, r6
	set_reg	5, r6, r10, r11
	in.h	4[r10], r12
	andi	0xFFF0, r12, r12
	shl	3, r7
	shl	2, r8
	shl	1, r9
	or	r7, r13
	or	r8, r13
	or	r9, r13
	or	r12, r13
	out.h	r13, 4[r10]
	jmp	[lp]

_eris_low_sup_set_interrupt_raster:
	shl	8, r6
	set_reg	6, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_set_scroll:
	shl	8, r6
	set_reg	7, r6, r10, r11
	out.h	r7, 4[r10]
	set_reg	8, r6, r10, r11
	out.h	r8, 4[r10]
	jmp	[lp]

_eris_low_sup_get_scroll:
	shl	8, r6
	set_reg	7, r6, r10, r11
	in.h	4[r10], r11
	st.h	r11, 0[r7]
	set_reg	8, r6, r10, r11
	in.h	4[r10], r11
	st.h	r11, 0[r8]
	jmp	[lp]

_eris_low_sup_do_dma:
	shl	8, r6
	set_reg	16, r6, r10, r11
	out.h	r7, 4[r10]
	set_reg	17, r6, r10, r11
	out.h	r8, 4[r10]
	set_reg	18, r6, r10, r11
	out.h	r9, 4[r10]
	jmp	[lp]

_eris_low_sup_setup_dma:
	ld.w	0[sp], r10
	ld.w	4[sp], r11
	shl	8, r6
	shl	4, r7
	shl	3, r8
	shl	2, r9
	shl	1, r10
	or	r8, r7
	or	r9, r7
	or	r10, r7
	or	r11, r7
	set_reg	15, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_set_satb_address:
	shl	8, r6
	set_reg	19, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_set_access_width:
	shl	8, r6
	set_reg	9, r6, r10, r11
	ld.w	0[sp], r12
	shl	7, r7
	shl	4, r8
	shl	2, r9
	or	r12, r7
	or	r8, r7
	or	r9, r7
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_low_sup_get_access_width:
	shl	8, r6
	ld.w	0[sp], r10
	set_reg	9, r6, r11, r12
	in.h	4[r11], r12
	mov	r12, r13
	shr	7, r13
	addi	1, r13, r13
	st.w	r13, 0[r7]
	mov	r12, r13
	shr	4, r13
	addi	7, r13, r13
	st.w	r13, 0[r8]
	mov	r12, r13
	shr	2, r13
	addi	3, r13, r13
	st.w	r13, 0[r9]
	addi	3, r12, r12
	st.w	r12, 0[r10]
	jmp	[lp]


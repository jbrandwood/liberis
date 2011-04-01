/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  7up functions                                                        []  *
 *****************************************************************************/
	.global	_eris_7up_init
	.global	_eris_7up_set_vram_write_addr
	.global	_eris_7up_vram_write
	.global	_eris_7up_set_vram_read_addr
	.global	_eris_7up_vram_read
	.global	_eris_7up_set_control
	.global	_eris_7up_set_interrupts
	.global	_eris_7up_get_raster
	.global _eris_7up_set_scroll
	.global	_eris_7up_do_dma
	.global	_eris_7up_setup_dma
	.global	_eris_7up_set_satb_address
	.global	_eris_7up_set_access_width

.macro	set_rrg	reg, ch, tmp
	movea	0x400, \ch, \tmp
	out.h	\reg, 0[\tmp]
.endm

.macro	set_reg	reg, ch, tmp1, tmp2
	movea	\reg, r0, \tmp2
	set_rrg	\tmp2, \ch, \tmp1
.endm

_eris_7up_init:
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
2:	add	-1, r8
	set_rrg	r8, r6, r10
	out.h	r0, 4[r10]
	cmp	5, r8
	bne	2b
	jmp	[lp]

_eris_7up_set_vram_write_addr:
	shl	8, r6
	set_reg	0, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_7up_vram_write:
	shl	8, r6
	set_reg	2, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_7up_set_vram_read_addr:
	shl	8, r6
	set_reg	1, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_7up_vram_read:
	shl	8, r6
	set_reg	2, r6, r10, r11
	in.h	4[r10], r10
	jmp	[lp]

_eris_7up_set_control:
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

_eris_7up_set_interrupts:
	ld.w	16[sp], r13
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

_eris_7up_get_raster:
	shl	8, r6
	set_reg	6, r6, r10, r11
	in.h	4[r10], r10
	jmp	[lp]

_eris_7up_set_scroll:
	shl	8, r6
	set_reg	7, r6, r10, r11
	out.h	r7, 4[r10]
	set_reg	8, r6, r10, r11
	out.h	r8, 4[r10]
	jmp	[lp]

_eris_7up_do_dma:
	shl	8, r6
	set_reg	16, r6, r10, r11
	out.h	r7, 4[r10]
	set_reg	17, r6, r10, r11
	out.h	r8, 4[r10]
	set_reg	18, r6, r10, r11
	out.h	r9, 4[r10]
	jmp	[lp]

_eris_7up_setup_dma:
	ld.w	16[sp], r10
	ld.w	20[sp], r11
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

_eris_7up_set_satb_address:
	shl	8, r6
	set_reg	19, r6, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_7up_set_access_width:
	shl	8, r6
	set_reg	9, r6, r10, r11
	ld.w	16[sp], r12
	shl	7, r7
	shl	4, r8
	shl	2, r9
	or	r12, r7
	or	r8, r7
	or	r9, r7
	out.h	r7, 4[r10]
	jmp	[lp]


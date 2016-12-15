/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  High-level 7up control                                               []  *
 *****************************************************************************/
	.global	_eris_sup_init
	.global	_eris_sup_set
	.global _eris_sup_show

	.global	_eris_sup_spr_set
	.global	_eris_sup_spr_x
	.global	_eris_sup_spr_y
	.global	_eris_sup_spr_xy
	.global	_eris_sup_spr_pattern
	.global	_eris_sup_spr_pri
	.global	_eris_sup_spr_pal
	.global	_eris_sup_spr_ctrl
	.global	_eris_sup_spr_create
	.global	_eris_sup_spr_get_x
	.global	_eris_sup_spr_get_y
	.global	_eris_sup_spr_get_pattern

	.global _eris_sup_bg_set_size
	.global _eris_sup_bg_set_tile
	.global _eris_sup_bg_load_tiles
	.global _eris_sup_bg_scroll_x
	.global _eris_sup_bg_scroll_y
	.global _eris_sup_bg_scroll_xy
	.global _eris_sup_bg_get_tile
	.global _eris_sup_bg_get_scroll_x
	.global _eris_sup_bg_get_scroll_y

eris_sup_last_sup:
	.word	0
eris_sup_last_spr:
	.word	0, 0

_eris_sup_init:
	addi	-20, sp, sp
	mov	lp, r20
	andi	1, r6, r19
	andi	1, r7, r18
	mov	r19, r6
	mov	r18, r7

	# core init
	mov	r19, r6
	jal	_eris_low_sup_init

	mov	r19, r6
	mov	r0, r7
	mov	r0, r8
	mov	r0, r9
	jal	_eris_low_sup_set_control

	mov	r19, r6
	mov	r0, r7
	mov	r0, r8
	mov	r0, r9
	st.w	r0, 0[sp]
	jal	_eris_low_sup_set_access_width

	cmp	1, r19 # Never setup the timing on 7up-B
	be	1f
	mov	r0, r6
	mov	2, r7
	mov	2, r8
	mov	4, r9
	movea	0x1F, r0, r10
	st.w	r10, 0[sp]
	movea	0x11, r0, r10
	st.w	r10, 4[sp]
	st.w	r7, 8[sp]
	movea	239, r0, r10
	st.w	r10, 12[sp]
	st.w	r7, 16[sp]
	jal	_eris_low_sup_set_video_mode
1:
	# bg stuff
	mov	r19, r6
	mov	r0, r7
	mov	r0, r8
	jal	_eris_low_sup_set_scroll

	# sprite stuff
	movhi	hi(eris_sup_last_sup), r0, r10
	movea	lo(eris_sup_last_spr), r0, r11
	movhi	hi(eris_sup_last_spr), r11, r11

	st.w	r19, lo(eris_sup_last_sup)[r10]
	shl	2, r6
	add	r6, r11
	st.w	r0, 0[r11]

	mov	r19, r6
	mov	r18, r7
	mov	0, r8
	mov	0, r9
	st.w	r0, 0[sp]
	st.w	r0, 4[sp]
	jal	_eris_low_sup_setup_dma

	mov	r19, r6
	ori	0xFF00, r0, r7
	jal	_eris_low_sup_set_satb_address

	addi	20, sp, sp
	mov	r20, lp
	jmp	[lp]

_eris_sup_set:
	andi	1, r6, r6
	movhi	hi(eris_sup_last_sup), r0, r10
	st.w	r6, lo(eris_sup_last_sup)[r10]
	jmp	[lp]

_eris_sup_show:
	addi	-12, sp, sp
	mov	r6, r15
	mov	r7, r16
	movhi	hi(eris_sup_last_sup), r0, r10
	ld.w	lo(eris_sup_last_sup)[r10], r6
	mov	r6, r14
	addi	0, sp, r7
	addi	4, sp, r8
	addi	8, sp, r9
	jal	_eris_low_sup_get_control
	mov	r14, r6
	ld.w	0[sp], r7
	mov	r15, r8
	mov	r16, r9
	jal	_eris_low_sup_set_control
	addi	12, sp, sp
	jmp	[lp]

_eris_sup_spr_set:
	andi	63, r6, r6
	movhi	hi(eris_sup_last_sup), r0, r10
	movea	lo(eris_sup_last_spr), r0, r11
	ld.w	lo(eris_sup_last_sup)[r10], r10
	movhi	hi(eris_sup_last_spr), r11, r11
	add	r10, r11
	st.w	r6, 0[r11]
	jmp	[lp]

.macro get_sup supreg
	movhi	hi(eris_sup_last_sup), r0, \supreg
	ld.w	lo(eris_sup_last_sup)[\supreg], \supreg
.endm

.macro setup_addr sprreg, supreg, calcreg, off
	movhi	hi(eris_sup_last_sup), r0, \supreg
	movea	lo(eris_sup_last_spr), r0, \sprreg
	ld.w	lo(eris_sup_last_sup)[\supreg], \supreg
	movhi	hi(eris_sup_last_spr), \sprreg, \sprreg
	add	\supreg, \sprreg
	ld.w	0[\sprreg], \sprreg

	shl	2, \sprreg
	ori	0xFF00|\off, \sprreg, \calcreg
.endm

_eris_sup_spr_x:
	mov	lp, r17
	setup_addr	r20, r19, r18, 1
	mov	r6, r16

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	mov	r19, r6
	mov	r16, r7
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_y:
	mov	lp, r17
	setup_addr	r20, r19, r18, 0
	mov	r6, r16

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	mov	r19, r6
	mov	r16, r7
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_xy:
	mov	lp, r17
	setup_addr	r20, r19, r18, 0
	mov	r6, r16
	mov	r7, r15

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	mov	r19, r6
	mov	r15, r7
	jal	_eris_low_sup_vram_write

	mov	r19, r6
	mov	r16, r7
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_pattern:
	mov	lp, r17
	setup_addr	r20, r19, r18, 2
	mov	r6, r16

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	mov	r19, r6
	mov	r16, r7
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_pri:
	mov	lp, r17
	setup_addr	r20, r19, r18, 3
	mov	r6, r16

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	shl	7, r16

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read

	andi	0x80, r10, r7
	or	r16, r7
	mov	r19, r6
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_pal:
	mov	lp, r17
	setup_addr	r20, r19, r18, 3
	andi	0xF, r6, r16

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read

	andi	0xFFF0, r10, r7
	or	r16, r7
	mov	r19, r6
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_ctrl:
	mov	lp, r17
	setup_addr	r20, r19, r18, 3
	mov	r6, r16
	mov	r7, r15

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read
	mov	r10, r7

	and	r16, r7
	or	r15, r7
	mov	r19, r6
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_create:
	mov	lp, r17
	setup_addr	r20, r19, r18, 0
	mov	r6, r16
	mov	r7, r15

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_write

	mov	r19, r6
	mov	r15, r7
	jal	_eris_low_sup_vram_write

	mov	r19, r6
	mov	r16, r7
	jal	_eris_low_sup_vram_write

	mov	r19, r6
	mov	r8, r7
	jal	_eris_low_sup_vram_write

	mov	r19, r6
	mov	r9, r7
	jal	_eris_low_sup_vram_write

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_get_x:
	mov	lp, r17
	setup_addr	r20, r19, r18, 1

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_get_y:
	mov	lp, r17
	setup_addr	r20, r19, r18, 0

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_get_pattern:
	mov	lp, r17
	setup_addr	r20, r19, r18, 2

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_get_ctrl:
	mov	lp, r17
	setup_addr	r20, r19, r18, 3

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read

	mov	r17, lp
	jmp	[lp]

_eris_sup_spr_get_pal:
	mov	lp, r17
	setup_addr	r20, r19, r18, 1

	mov	r19, r6
	mov	r18, r7
	jal	_eris_low_sup_set_vram_read

	mov	r19, r6
	jal	_eris_low_sup_vram_read

	andi	0xF, r10, r10

	mov	r17, lp
	jmp	[lp]

_eris_sup_bg_set_size:
	addi	-20, sp, sp
	mov	lp, r14
	mov	r6, r16

	get_sup	r6
	mov	r6, r15
	addi	4, sp, r7
	addi	8, sp, r8
	addi	12, sp, r9
	addi	16, sp, r10
	st.w	r10, 0[sp]
	jal	_eris_low_sup_get_access_width

	mov	r15, r6
	ld.w	4[sp], r7
	mov	r16, r8
	ld.w	12[sp], r9
	ld.w	16[sp], r10
	st.w	r10, 0[sp]
	jal	_eris_low_sup_set_access_width

	mov	r14, lp
	addi	20, sp, sp
	jmp	[lp]

_eris_sup_bg_set_tile:
	addi	-20, sp, sp
	mov	lp, r14
	mov	r6, r16
	mov	r7, r17
	mov	r8, r18

	get_sup	r6
	mov	r6, r15
	addi	4, sp, r7
	addi	8, sp, r8
	addi	12, sp, r9
	addi	16, sp, r10
	st.w	r10, 0[sp]
	jal	_eris_low_sup_get_access_width

	ld.w	8[sp], r10
	andi	3, r10, r10
	add	5, r10

	shl	r10, r17
	add	r16, r17
	mov	r15, r6
	mov	r17, r7
	jal	_eris_low_sup_set_vram_write

	mov	r15, r6
	mov	r18, r7
	jal	_eris_low_sup_vram_write

	mov	r14, lp
	addi	20, sp, sp
	jmp	[lp]

_eris_sup_bg_load_tiles:
	addi	-20, sp, sp
	mov	lp, r14
	mov	r6, r16
	mov	r7, r17
	mov	r8, r18

	get_sup	r6
	mov	r6, r15
	addi	4, sp, r7
	addi	8, sp, r8
	addi	12, sp, r9
	addi	16, sp, r10
	st.w	r10, 0[sp]
	jal	_eris_low_sup_get_access_width

	ld.w	8[sp], r10
	andi	3, r10, r10
	add	5, r10

	shl	r10, r17
	add	r16, r17
	mov	r15, r6
	mov	r17, r7
	jal	_eris_low_sup_set_vram_write

	mov	r15, r6
	mov	r18, r7
	jal	_eris_low_sup_vram_write

	mov	r14, lp
	addi	20, sp, sp
	jmp	[lp]

_eris_sup_bg_scroll_x:
	jmp	[lp]

_eris_sup_bg_scroll_y:
	jmp	[lp]

_eris_sup_bg_scroll_xy:
	jmp	[lp]

_eris_sup_bg_get_tile:
	addi	-20, sp, sp
	mov	lp, r14
	mov	r6, r16
	mov	r7, r17

	get_sup	r6
	mov	r6, r15
	addi	4, sp, r7
	addi	8, sp, r8
	addi	12, sp, r9
	addi	16, sp, r10
	st.w	r10, 0[sp]
	jal	_eris_low_sup_get_access_width

	ld.w	8[sp], r10
	andi	3, r10, r10
	add	5, r10

	shl	r10, r17
	add	r16, r17
	mov	r15, r6
	mov	r17, r7
	jal	_eris_low_sup_set_vram_read

	mov	r15, r6
	jal	_eris_low_sup_vram_read

	mov	r14, lp
	addi	20, sp, sp
	jmp	[lp]

_eris_sup_bg_get_scroll_x:
	jmp	[lp]

_eris_sup_bg_get_scroll_xy:
	jmp	[lp]


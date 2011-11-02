/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 * HuC6272 (KING) functions                                              []  *
 *****************************************************************************/
	.global	_eris_king_init
	.global	_eris_king_set_kram_read
	.global	_eris_king_set_kram_write
	.global	_eris_king_kram_read
	.global	_eris_king_kram_write
	.global	_eris_king_set_kram_pages
	.global	_eris_king_set_bg_mode
	.global	_eris_king_set_bg_prio
	.global	_eris_king_set_bg_size
	.global	_eris_king_set_bat_cg_addr
	.global	_eris_king_set_scroll
	.global _eris_king_write_microprogram
	.global _eris_king_fill_microprogram
	.global	_eris_king_enable_microprogram
	.global _eris_king_disable_microprogram
	.global _eris_king_scsi_status
	.global _eris_king_scsi_reset
	.global _eris_king_scsi_data_in
	.global _eris_king_scsi_data_out
	.global _eris_king_scsi_abort
	.global _eris_king_scsi_command
	.global _eris_king_scsi_test_unit_ready

.macro	set_rrg	reg
	out.h	\reg, 0x600[r0]
.endm

.macro	set_reg reg, tmp
	movea	\reg, r0, \tmp
	set_rrg	\tmp
.endm

_eris_king_init:
	mov	1, r10
1:	mov	r10, r11
	shl	31, r11
	mov	1, r12
2:	mov	r12, r13
	shl	17, r13
	set_reg	0xD, r15
	or	r13, r11
	movhi	4, r0, r13
	or	r13, r11
	out.w	r11, 0x604[r0]
	set_reg	0xE, r15
	movhi	2, r0, r13
3:	out.h	r0, 0x604[r0]
	add	-1, r13
	bne	3b
	add	-1, r12
	bge	2b
	add	-1, r10
	bge	1b
	movea	0x80, r0, r10
	set_reg	1, r15
	out.h	r10, 0x604[r0]
	out.h	r0, 0x604[r0]
	jmp	[lp]

_eris_king_set_kram_read:
	shl	18, r7
	set_reg	0xC, r10
	or	r7, r6
	out.w	r6, 0x604[r0]
	jmp	[lp]

_eris_king_set_kram_write:
	shl	18, r7
	set_reg	0xD, r10
	or	r7, r6
	out.w	r6, 0x604[r0]
	jmp	[lp]

_eris_king_kram_read:
	set_reg	0xE, r10
	in.h	0x604[r0], r10
	jmp	[lp]

_eris_king_kram_write:
	set_reg	0xE, r10
	out.h	r6, 0x604[r0]
	jmp	[lp]

_eris_king_set_kram_pages:
	set_reg	0xF, r10
	shl	8, r7
	shl	16, r8
	shl	24, r9
	or	r7, r6
	or	r8, r6
	or	r9, r6
	out.w	r6, 0x604[r0]
	jmp	[lp]

_eris_king_set_bg_mode:
	set_reg	0x10, r10
	shl	4, r7
	shl	8, r8
	shl	12, r9
	or	r7, r6
	or	r8, r6
	or	r9, r6
	out.h	r6, 0x604[r0]
	jmp	[lp]

_eris_king_set_bg_prio:
	set_reg	0x12, r10
	ld.w	16[sp], r11
	shl	3, r7
	shl	6, r8
	shl	9, r9
	shl	12, r11
	or	r7, r6
	or	r8, r6
	or	r9, r6
	or	r11, r6
	out.h	r6, 0x604[r0]
	jmp	[lp]

_eris_king_set_bg_size:
	ld.w	16[sp], r10
	shl	4, r8
	shl	8, r9
	shl	12, r10
	or	r8, r7
	or	r9, r7
	or	r10, r7
	movea	0x2C, r0, r10
	cmp	0, r6
	be	1f
	add	-1, r6
1:	add	r10, r6
	set_rrg	r6
	out.h	r7, 0x604[r0]
	jmp	[lp]

_eris_king_set_bat_cg_addr:
	movea	0x20, r0, r10
	shl	1, r6
	add	r10, r6
	set_rrg	r6
	out.h	r7, 0x604[r0]
	add	1, r6
	set_rrg	r6
	out.h	r8, 0x604[r0]
	jmp	[lp]

_eris_king_set_scroll:
	movea	0x2C, r0, r10
	cmp	0, r6
	be	1f
	add	-1, r6
1:	shl	1, r6
	add	r10, r6
	set_rrg	r6
	out.h	r7, 0x604[r0]
	add	1, r6
	set_rrg	r6
	out.h	r8, 0x604[r0]
	jmp	[lp]

_eris_king_write_microprogram:
	set_reg	0x13, r10
	out.h	r7, 0x604[r0]
	set_reg	0x14, r10
1:
	ld.h	0[r6], r10
	out.h	r10, 0x604[r0]
	add	2, r6
	add	-1, r8
	bne	1b
	jmp	[lp]

_eris_king_fill_microprogram:
	set_reg	0x13, r10
	out.h	r7, 0x604[r0]
	set_reg	0x14, r10
1:
	out.h	r6, 0x604[r0]
	add	-1, r8
	bne	1b
	jmp	[lp]

_eris_king_enable_microprogram:
	mov	1, r11
	set_reg	0x15, r10
	out.h	r11, 0x604[r0]
	jmp	[lp]

_eris_king_disable_microprogram:
	set_reg	0x15, r10
	out.h	r0, 0x604[r0]
	jmp	[lp]

eris_king_scsi_get_phase:
	in.h	0x602[r0], r11
	mov	0, r10         # Bus Free
	andi	0x40, r11, r12
	be	1f
	mov	1, r10         # Select
	andi	0x2, r11, r12
	bne	1f
	mov	0, r10         # Bus Free
	andi	0x1C, r11, r12
	mov	2, r10         # Data Out
	cmp	0, r12
	be	1f
	mov	3, r10         # Data In
	cmp	4, r12
	be	1f
	mov	4, r10         # Command
	cmp	8, r12
	be	1f
	mov	5, r10         # Status
	cmp	0xC, r12
	be	1f
	mov	6, r10         # Message Out
	cmp	0x18, r12
	be	1f
	mov	7, r10         # Message In
	cmp	0x1C, r12
	be	1f
	mov	8, r10         # Illegal
1:
	jmp	[lp]

_eris_king_scsi_status:
	in.h	0x602[r0], r10
	jmp	[lp]

_eris_king_scsi_reset:
	movea	0x1000, r0, r10
	mov	1, r11
	movea	0x80, r0, r12
1:
	out.h	r11, 0x600[r0]
	out.h	r12, 0x604[r0]
	add	-1, r10
	bne	1b

	out.h	r11, 0x600[r0]
	out.h	r0, 0x604[r0]
	jmp	[lp]

_eris_king_scsi_data_in:
	mov	0, r14
	mov	lp, r15
1:	in.h	0x602[r0], r10
	andi	0x20, r10, r10
	be	1b

	br	2f
1:
	mov	1, r10
	mov	0x10, r12
	out.h	r0, 0x600[r0]
	in.h	0x604[r0], r11
	st.b	r11, 0[r6]
	add	1, r14

	out.h	r10, 0x600[r0]
	out.h	r12, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	bne	3b

	out.h	r10, 0x600[r0]
	out.h	r0, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	3b

2:	jal	eris_king_scsi_get_phase
	cmp	3, r10 # data in
	bne	1f
	add	1, r6
	add	-1, r7
	bne	1b

1:
	mov	r14, r10
	mov	r15, lp
	jmp	[lp]

_eris_king_scsi_data_out:
	mov	0, r14
	mov	lp, r15
	mov	3, r11
1:	in.h	0x602[r0], r10
	andi	0x20, r10, r10
	be	1b

	out.h	r11, 0x600[r0]
	out.h	r0, 0x604[r0]
	br	2f
1:
	ld.b	0[r6], r11
	mov	1, r10
	mov	0x11, r12
	out.h	r0, 0x600[r0]
	out.h	r11, 0x604[r0]
	add	1, r14

	out.h	r10, 0x600[r0]
	out.h	r12, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	bne	3b

	out.h	r10, 0x600[r0]
	out.h	r0, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	3b

2:	jal	eris_king_scsi_get_phase
	cmp	2, r10 # data in
	bne	1f
	add	1, r6
	add	-1, r7
	bne	1b

1:
	mov	r14, r10
	mov	r15, lp
	jmp	[lp]

_eris_king_scsi_abort:
	mov	1, r10
	out.h	r0, 0x600[r0]
	out.h	r0, 0x604[r0]

	out.h	r0, 0x600[r0]
	out.h	r10, 0x604[r0]
	add	1, r10

	out.h	r0, 0x600[r0]
	out.h	r10, 0x604[r0]
	add	1, r10

	out.h	r0, 0x600[r0]
	out.h	r10, 0x604[r0]
	add	3, r10

	out.h	r0, 0x600[r0]
	out.h	r10, 0x604[r0]
	add	-5, r10

	out.h	r10, 0x600[r0]
	out.h	r10, 0x604[r0]

	out.h	r10, 0x600[r0]
	add	2, r10
	out.h	r10, 0x604[r0]
	jmp	[lp]

.macro scsi_delay
	movea	(262144/8), r0, r10
9:
.rept 8
	mov	r0, r0
.endr
	add	-1, r10
	bne	9b
.endm

_eris_king_scsi_command:
	mov	lp, r15
	mov	0, r14
	mov	1, r13
	movea	0x84, r0, r12
	mov	3, r11
	mov	r0, r10
	out.h	r11, 0x600[r0]
	out.h	r0, 0x604[r0]
	out.h	r0, 0x600[r0]
	add	2, r11
	out.h	r12, 0x604[r0]

	scsi_delay

	out.h	r13, 0x600[r0]
	out.h	r13, 0x604[r0]

	scsi_delay

	out.h	r13, 0x600[r0]
	out.h	r11, 0x604[r0]

	scsi_delay

1:	jal	eris_king_scsi_get_phase
	be	1b

	scsi_delay

	out.h	r13, 0x600[r0]
	out.h	r0, 0x604[r0]

	scsi_delay

1:	jal	eris_king_scsi_get_phase
	cmp	4, r10 # command
	bne	1b
	mov	3, r11
	mov	2, r10
	out.h	r11, 0x600[r0]
	out.h	r10, 0x604[r0]
1:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	1b

	br	2f
1:
	mov	1, r10
	mov	0, r11
	cmp	r14, r7
	bnh	3f
	ld.b	0[r6], r11
3:
	add	1, r14
	mov	0x11, r12
	out.h	r10, 0x600[r0]
	out.h	r11, 0x604[r0]

	out.h	r10, 0x600[r0]
	out.h	r10, 0x604[r0]

	out.h	r10, 0x600[r0]
	out.h	r12, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	bne	3b

	out.h	r10, 0x600[r0]
	out.h	r10, 0x600[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	3b

2:	jal	eris_king_scsi_get_phase
	cmp	4, r10 # command
	be	1b

	mov	r15, lp
	jmp	[lp]

/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 * HuC6272 (KING) SCSI functions                                         []  *
 *****************************************************************************/
	.global _eris_low_scsi_get_phase
	.global _eris_low_scsi_status
	.global _eris_low_scsi_reset
	.global _eris_low_scsi_data_in
	.global _eris_low_scsi_data_out
	.global _eris_low_scsi_begin_dma
	.global _eris_low_scsi_check_dma
	.global _eris_low_scsi_finish_dma
	.global _eris_low_scsi_abort
	.global _eris_low_scsi_command
	.global _eris_low_scsi_test_unit_ready

	.global	eris_low_scsi_eat_data_in

_eris_low_scsi_get_phase:
	in.h	0x602[r0], r11
	mov	0, r10         # Bus Free
	andi	0x40, r11, r12
	be	1f
	mov	1, r10         # Select
	andi	0x2, r11, r12
	bne	1f
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
	movea	0x18, r0, r11
	mov	6, r10         # Message Out
	cmp	r11, r12
	be	1f
	add	4, r11
	mov	7, r10         # Message In
	cmp	r11, r12
	be	1f
	mov	8, r10         # Illegal
1:
	jmp	[lp]

scsi_phase_status_tbl:
	.word	0 # Bus free
	.word	-1 # Select
	.word	-3 # Data Out
	.word	-2 # Data In
	.word	-1 # Command
	.word	1 # Status
	.word	-4 # Message Out
	.word	0 # Message In
	.word	0 # Illegal

_eris_low_scsi_status:
	mov	lp, r15
	jal	_eris_low_scsi_get_phase
	shl	2, r10
	movea	lo(scsi_phase_status_tbl), r0, r12
	movhi	hi(scsi_phase_status_tbl), r12, r12
	add	r10, r12
	ld.w	0[r12], r10
	cmp	0, r10
	be	1f
	blt	2f

	mov	1, r13
	out.h	r13, 0x600[r0]
	out.h	r0, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	3b

	out.h	r0, 0x600[r0]
	in.h	0x604[r0], r10
	andi	0xFFFE, r10, r10
	movea	0x10, r0, r14
	out.h	r13, 0x600[r0]
	out.h	r14, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	bne	3b

	out.h	r13, 0x600[r0]
	out.h	r0, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	3b

	out.h	r13, 0x600[r0]
	out.h	r14, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	bne	3b

	out.h	r13, 0x600[r0]
	out.h	r0, 0x604[r0]
2:
	mov	r15, lp
	jmp	[lp]

1:
	mov	-5, r10
	mov	r15, lp
	jmp	[lp]

_eris_low_scsi_reset:
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

_eris_low_scsi_data_in:
	mov	0, r14
	mov	lp, r15
1:	in.h	0x602[r0], r10
	andi	0x20, r10, r10
	be	1b

	br	2f
1:
	mov	1, r10
	movea	0x10, r0, r12
	out.h	r0, 0x600[r0]
	in.h	0x604[r0], r11
	st.b	r11, 0[r6]
	add	1, r14
	add	1, r6
	add	-1, r7

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

2:	jal	_eris_low_scsi_get_phase
	cmp	3, r10 # data in
	bne	1f
	cmp	0, r7
	bne	1b

1:
	mov	r14, r10
	mov	r15, lp
	jmp	[lp]

_eris_low_scsi_data_out:
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
	movea	0x11, r0, r12
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

2:	jal	_eris_low_scsi_get_phase
	cmp	2, r10 # data out
	bne	1f
	add	1, r6
	add	-1, r7
	bne	1b

1:
	mov	r14, r10
	mov	r15, lp
	jmp	[lp]

_eris_low_scsi_begin_dma:
	mov	3, r10
	mov	2, r12
	mov	1, r11
	out.h	r10, 0x600[r0]
	add	6, r10
	out.h	r11, 0x604[r0]

	out.h	r10, 0x600[r0]
	add	1, r10
	out.w	r6, 0x604[r0]

	out.h	r10, 0x600[r0]
	add	-8, r10
	out.w	r7, 0x604[r0]

	out.h	r10, 0x600[r0]
	add	9, r10
	out.h	r12, 0x604[r0]

	out.h	r10, 0x600[r0]
	add	-4, r10
	out.h	r11, 0x604[r0]

	out.h	r10, 0x600[r0]
	out.h	r11, 0x604[r0]

	jmp	[lp]

_eris_low_scsi_check_dma:
	mov	11, r11
	out.h	r11, 0x600[r0]
	add	-1, r11
	in.h	0x604[r0], r10
	andi	1, r10, r10
	bne	1f

	out.h	r11, 0x600[r0]
	in.w	0x604[r0], r10
	cmp	0, r10
	setf	nz, r10
1:
	jmp	[lp]

_eris_low_scsi_finish_dma:
	mov	2, r13
	out.h	r13, 0x600[r0]
	add	1, r13
	out.h	r0, 0x604[r0]
	out.h	r13, 0x600[r0]
	add	-2, r13
	out.h	r0, 0x604[r0]

	jr	eris_low_scsi_eat_data_in

_eris_low_scsi_abort:
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
	movhi	4, r0, r10
9:
.rept 8
	mov	r0, r0
.endr
	add	-1, r10
	bne	9b
.endm

_eris_low_scsi_command:
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

1:	jal	_eris_low_scsi_get_phase
	be	1b

	scsi_delay

	out.h	r13, 0x600[r0]
	out.h	r0, 0x604[r0]

	scsi_delay

1:	jal	_eris_low_scsi_get_phase
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
	mov	r0, r11
	cmp	r14, r7
	bnh	3f
	ld.b	0[r6], r11
	add	1, r6
3:
	add	1, r14
	movea	0x11, r0, r12
	out.h	r0, 0x600[r0]
	out.h	r11, 0x604[r0]

	out.h	r10, 0x600[r0]
	out.h	r10, 0x604[r0]

	out.h	r10, 0x600[r0]
	out.h	r12, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	bne	3b

	out.h	r10, 0x600[r0]
	out.h	r10, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	3b

2:	jal	_eris_low_scsi_get_phase
	cmp	4, r10 # command
	be	1b

	mov	1, r11
	mov	3, r10
	out.h	r11, 0x600[r0]
	out.h	r0, 0x604[r0]
	out.h	r10, 0x600[r0]
	out.h	r0, 0x604[r0]

	mov	r14, r10
	mov	r15, lp
	jmp	[lp]

eris_low_scsi_eat_data_in:
	mov	lp, r20
	mov	1, r13
	movea	0x10, r0, r14
	br	2f
1:
	out.h	r13, 0x600[r0]
	out.h	r14, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	bne	3b

	out.h	r13, 0x600[r0]
	out.h	r0, 0x604[r0]

3:	in.h	0x602[r0], r11
	andi	0x20, r11, r11
	be	3b

2:	jal	_eris_low_scsi_get_phase
	cmp	3, r10 # data in
	be	1b

	mov	r20, lp
	jmp	[lp]

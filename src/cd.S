/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  High-level CD handling                                               []  *
 *****************************************************************************/
	.global	_eris_cd_reset
	.global _eris_cd_read
	.global _eris_cd_read_kram

_eris_cd_reset:
	jr	_eris_low_scsi_reset

_eris_cd_read:
	mov	lp, r19
	movea	0x7FF, r0, r10
	not	r10, r13
	mov	r6, r11
	mov	r7, r18
	mov	r8, r16
	add	r10, r16 # for rounding up
	and	r13, r16
	mov	r16, r17

	addi	-32, sp, sp
	movea	0x28, r0, r10 # SCSI_LOW_CMD_READ10
	st.b	r10, 0[sp]
	st.b	r0, 1[sp]
	st.b	r11, 5[sp]
	shr	11, r16 # bytes to blocks
	shr	8, r11
	st.b	r11, 4[sp]
	shr	8, r11
	st.b	r11, 3[sp]
	shr	8, r11
	st.b	r11, 2[sp]
	st.b	r16, 8[sp]
	shr	8, r16
	st.b	r16, 7[sp]
	st.b	r0, 6[sp]
	st.b	r0, 9[sp]
	st.h	r0, 10[sp]
	st.w	r0, 12[sp]
	st.w	r0, 16[sp]
	st.w	r0, 20[sp]
	st.w	r0, 24[sp]
	st.w	r0, 28[sp]

	mov	sp, r6
	mov	10, r7
	jal	_eris_low_scsi_command
	addi	32, sp, sp

	movea	0x800, r0, r10
1:	nop
	nop
	nop
	nop
	add	-1, r10
	bne	1b

	mov	r18, r6
	mov	r17, r7
	jal	_eris_low_scsi_data_in
	mov	r10, r18

	jal	eris_low_scsi_eat_data_in

	movea	0x800, r0, r10
1:	nop
	nop
	nop
	nop
	add	-1, r10
	bne	1b

	jal	_eris_low_scsi_status

	mov	r18, r10
	mov	r19, lp
	jmp	[lp]

_eris_cd_read_kram:
	mov	lp, r19
	movea	0x7FF, r0, r10
	not	r10, r13
	mov	r6, r11
	mov	r7, r18
	mov	r8, r16
	mov	r16, r17
	add	r10, r16 # for rounding up
	and	r13, r16

	addi	-32, sp, sp
	movea	0x28, r0, r10 # SCSI_LOW_CMD_READ10
	st.b	r10, 0[sp]
	st.b	r0, 1[sp]
	st.b	r11, 5[sp]
	shr	11, r16 # bytes to blocks
	shr	8, r11
	st.b	r11, 4[sp]
	shr	8, r11
	st.b	r11, 3[sp]
	shr	8, r11
	st.b	r11, 2[sp]
	st.b	r16, 8[sp]
	shr	8, r16
	st.b	r16, 7[sp]
	st.b	r0, 6[sp]
	st.b	r0, 9[sp]
	st.h	r0, 10[sp]
	st.w	r0, 12[sp]
	st.w	r0, 16[sp]
	st.w	r0, 20[sp]
	st.w	r0, 24[sp]
	st.w	r0, 28[sp]

	mov	sp, r6
	mov	10, r7
	jal	_eris_low_scsi_command
	addi	32, sp, sp

	movea	0x800, r0, r10
1:	add	-1, r10
	nop
	bne	1b

1:	in.h	0x602[r0], r10
	andi	0x20, r10, r10
	be	1b

	jal	_eris_low_scsi_status

	mov	r18, r6
	mov	r17, r7
	jal	_eris_low_scsi_begin_dma

1:	jal	_eris_low_scsi_check_dma
	cmp	0, r10
	bne	1b

	jal	_eris_low_scsi_finish_dma

	jal	_eris_low_scsi_status

	mov	r19, lp
	jmp	[lp]


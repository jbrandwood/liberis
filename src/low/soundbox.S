/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  Low-level PSG functions                                              []  *
 *****************************************************************************/
	.global	_eris_low_psg_set_main_volume
	.global	_eris_low_psg_set_freq
	.global	_eris_low_psg_set_volume
	.global	_eris_low_psg_set_balance
	.global	_eris_low_psg_set_channel
	.global	_eris_low_psg_waveform_data
	.global	_eris_low_psg_set_noise
	.global _eris_low_psg_set_lfo_freq
	.global _eris_low_psg_set_lfo_control

.macro set_ch ch
	out.b	\ch, 0x100[r0]
.endm

_eris_low_psg_set_main_volume:
	shl	4, r6
	or	r6, r7
	out.b	r7, 0x102[r0]
	jmp	[lp]

_eris_low_psg_set_freq:
	mov	r6, r11
	shr	8, r11
	out.b	r6, 0x104[r0]
	out.b	r11, 0x106[r0]
	jmp	[lp]

_eris_low_psg_set_volume:
	shl	7, r7
	shl	6, r8
	or	r7, r6
	or	r8, r6
	out.b	r6, 0x108[r0]
	jmp	[lp]

_eris_low_psg_set_balance:
	shl	4, r6
	or	r6, r7
	out.b	r7, 0x10A[r0]
	jmp	[lp]

_eris_low_psg_set_channel:
	set_ch	r6
	jmp	[lp]

_eris_low_psg_waveform_data:
	out.b	r6, 0x10C[r0]
	jmp	[lp]

_eris_low_psg_set_noise:
	shl	7, r7
	or	r7, r6
	out.b	r6, 0x10E[r0]
	jmp	[lp]

_eris_low_psg_set_lfo_freq:
	out.b	r6, 0x110[r0]
	jmp	[lp]

_eris_low_psg_set_lfo_control:
	out.b	r6, 0x114[r0]
	jmp	[lp]

/*****************************************************************************
 *  Low-level ADPCM functions                                            []  *
 *****************************************************************************/
	.global _eris_low_adpcm_set_control
	.global	_eris_low_adpcm_set_volume

_eris_low_adpcm_set_control:
	ld.w	16[sp], r10
	shl	2, r7
	shl	3, r8
	shl	4, r9
	shl	5, r10
	or	r7, r6
	or	r8, r6
	or	r9, r6
	or	r10, r6
	out.b	r6, 0x120[r0]
	jmp	[lp]

_eris_low_adpcm_set_volume:
	shl	2, r6
	out.b	r7, 0x122[r6]
	out.b	r8, 0x124[r6]
	jmp	[lp]


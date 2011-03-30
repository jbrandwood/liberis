/*****************************************************************************
 *  NEW Tetsukannon (HuC6261) functions                                  []  *
 *****************************************************************************/
	.global _eris_tetsu_init
	.global	_eris_tetsu_set_video_mode
	.global _eris_tetsu_set_palette
	.global _eris_tetsu_set_7up_palette
	.global _eris_tetsu_set_king_palette
	.global	_eris_tetsu_set_rainbow_palette
	.global _eris_tetsu_set_priorities

.macro	set_rrg	reg
	out.h	\reg, 0x300[r0]
.endm

.macro	set_reg reg, tmp
	movea	\reg, r0, \tmp
	set_rrg	\tmp
.endm

_eris_tetsu_init:
	set_reg	0, r10
	out.h	r0, 0x304[r0]

	movea	0x200, r0, r6
	movea	0x88, r0, r7
	set_reg	1, r10
	out.h	r0, 0x304[r0]
	set_reg	2, r10
1:
	out.h	r7, 0x304[r0]
	add	-1, r6
	bne	1b

	movea	0x15, r0, r6
2:
	set_rrg	r6
	out.h	r0, 0x304[r0]
	add	-1, r6
	cmp	4, r6
	bne	2b

	movea	0xFF, r0, r6
	set_reg	0xA, r10
	out.h	r6, 0x304[r0]
	set_reg	0xB, r10
	out.h	r6, 0x304[r0]
	set_reg	0xC, r10
	out.h	r6, 0x304[r0]
	jmp	[lp]

_eris_tetsu_set_video_mode:
	ld.w	16[sp], r10
	ld.w	20[sp], r11
	ld.w	24[sp], r12
	ld.w	28[sp], r13
	ld.w	32[sp], r14
	ld.w	36[sp], r15
	ld.w	40[sp], r16
	ld.w	44[sp], r17
	shl	2, r7
	shl	3, r8
	shl	6, r9
	shl	7, r10
	shl	8, r11
	shl	9, r12
	shl	10, r13
	shl	11, r14
	shl	12, r15
	shl	13, r16
	shl	14, r17
	or	r7, r6
	or	r8, r6
	or	r9, r6
	or	r10, r6
	or	r11, r6
	or	r12, r6
	or	r13, r6
	or	r14, r6
	or	r15, r6
	or	r16, r6
	or	r17, r6
	set_reg	0, r10
	out.h	r6, 0x304[r0]
	jmp	[lp]

_eris_tetsu_set_palette:
	set_reg	1, r10
	out.h	r6, 0x304[r0]
	set_reg	2, r10
	out.h	r7, 0x304[r0]
	jmp	[lp]

_eris_tetsu_set_7up_palette:
	set_reg 4, r10
	shr	1, r6
	shr	1, r7
	shl	8, r7
	or	r7, r6
	out.b	r6, 0x304[r0]
	jmp	[lp]

_eris_tetsu_set_king_palette:
	set_reg 5, r10
	shr	1, r6
	shr	1, r7
	shl	8, r7
	or	r7, r6
	out.b	r6, 0x304[r0]
	set_reg 6, r10
	shr	1, r8
	shr	1, r9
	shl	8, r9
	or	r9, r8
	out.b	r8, 0x304[r0]
	jmp	[lp]

_eris_tetsu_set_rainbow_palette:
	set_reg 7, r10
	shr	1, r6
	out.b	r6, 0x304[r0]
	jmp	[lp]

_eris_tetsu_set_priorities:
	ld.w	16[sp], r10
	ld.w	20[sp], r11
	ld.w	24[sp], r12
	set_reg	8, r13
	shl	4, r7
	shl	8, r8
	or	r7, r6
	or	r8, r6
	out.h	r6, 0x304[r0]
	set_reg	9, r13
	shl	4, r10
	shl	8, r11
	shl	12, r12
	or	r10, r9
	or	r11, r9
	or	r12, r9
	out.h	r9, 0x304[r0]
	jmp	[lp]


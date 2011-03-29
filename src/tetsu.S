/*****************************************************************************
 *  NEW Tetsukannon (HuC6261) functions                                  []  *
 *****************************************************************************/
	.global _eris_tetsu_init
	.global	_eris_tetsu_set_video_mode
	.global _eris_tetsu_set_palette
	.global _eris_tetsu_set_7up_palette_offset
	.global _eris_tetsu_set_priorities

.macro	set_rrg	reg, tmp
	movea	0x300, r0, \tmp
	out.h	\reg, 0[\tmp]
.endm

.macro	set_reg reg, tmp1, tmp2
	movea	\reg, r0, \tmp2
	set_rrg	\tmp2, \tmp1
.endm

_eris_tetsu_init:
	set_reg	0, r10, r11
	out.h	r0, 4[r10]

	movea	0x1FF, r0, r6
	movea	0x88, r0, r7
	set_reg	1, r10, r11
	out.h	r0, 4[r10]
	set_reg	2, r10, r11
1:
	out.h	r7, 4[r10]
	add	-1, r6
	bne	1b

	mov	0x15, r6
2:
	set_rrg	r6, r10
	out.h	r0, 4[r10]
	add	-1, r6
	cmp	4, r6
	bne	2b

	movea	0xFF, r0, r6
	set_reg	0xA, r10, r11
	out.h	r6, 4[r10]
	set_reg	0xB, r10, r11
	out.h	r6, 4[r10]
	set_reg	0xC, r10, r11
	out.h	r6, 4[r10]
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
	set_reg	0, r10, r11
	out.h	r6, 4[r10]
	jmp	[lp]

_eris_tetsu_set_palette:
	set_reg	1, r10, r11
	out.h	r6, 4[r10]
	set_reg	2, r10, r11
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_tetsu_set_7up_palette_offset:
	set_reg 4, r10, r11
	mov	r6, r11
	mov	r6, r12
	mov	r6, r13
	mov	r6, r14
	shr	24, r11
	shr	16, r12
	shr	8, r13
	out.b	r11, 4[r10]
	set_reg	5, r10, r15
	out.b	r12, 4[r10]
	set_reg	6, r10, r15
	out.b	r13, 4[r10]
	set_reg 7, r10, r15
	out.b	r14, 4[r10]
	jmp	[lp]

_eris_tetsu_set_priorities:
	ld.w	16[sp], r10
	ld.w	20[sp], r11
	ld.w	24[sp], r12
	set_reg	8, r13, r14
	shl	4, r7
	shl	8, r8
	or	r7, r6
	or	r8, r6
	out.h	r6, 4[r13]
	set_reg	9, r13, r14
	shl	4, r10
	shl	8, r11
	shl	12, r12
	or	r10, r9
	or	r11, r9
	or	r12, r9
	out.h	r9, 4[r13]
	jmp	[lp]



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

.macro	set_rrg	reg, tmp
	movea	0x600, r0, \tmp
	out.h	\reg, 0[\tmp]
.endm

.macro	set_reg reg, tmp1, tmp2
	movea	\reg, r0, \tmp2
	set_rrg	\tmp2, \tmp1
.endm

_eris_king_init:
	
	jmp	[lp]

_eris_king_set_kram_read:
	set_reg	0xC, r10, r11
	out.w	r6, 4[r10]
	jmp	[lp]

_eris_king_set_kram_write:
	set_reg	0xD, r10, r11
	out.w	r6, 4[r10]
	jmp	[lp]

_eris_king_kram_read:
	set_reg	0xE, r10, r11
	in.h	4[r10], r10
	jmp	[lp]

_eris_king_kram_write:
	set_reg	0xE, r10, r11
	out.h	r6, 4[r10]
	jmp	[lp]

_eris_king_set_kram_pages:
	set_reg	0xF, r10, r11
	shl	8, r7
	shl	16, r8
	shl	24, r9
	or	r7, r6
	or	r8, r6
	or	r9, r6
	out.w	r6, 4[r10]
	jmp	[lp]

_eris_king_set_bg_mode:
	set_reg	0x10, r10, r11
	shl	4, r7
	shl	8, r8
	shl	12, r9
	or	r7, r6
	or	r8, r6
	or	r9, r6
	out.h	r6, 4[r10]
	jmp	[lp]

_eris_king_set_bg_prio:
	set_reg	0x12, r10, r11
	ld.w	16[sp], r11
	shl	3, r7
	shl	6, r8
	shl	9, r9
	shl	12, r11
	or	r7, r6
	or	r8, r6
	or	r9, r6
	or	r11, r6
	out.h	r6, 4[r10]
	jmp	[lp]

_eris_king_set_bg_size:
	movea	0x2C, r0, r10
	cmp	0, r6
	be	1f
	add	-1, r6
1:	add	r10, r6
	set_rrg	r6, r10
	out.h	r7, 4[r10]
	jmp	[lp]

_eris_king_set_bat_cg_addr:
	movea	0x20, r0, r10
	shl	1, r6
	add	r10, r6
	set_rrg	r6, r10
	out.h	r7, 4[r10]
	add	1, r6
	set_rrg	r6, r10
	out.h	r8, 4[r10]
	jmp	[lp]

_eris_king_set_scroll:
	movea	0x2C, r0, r10
	cmp	0, r6
	be	1f
	add	-1, r6
1:	shl	1, r6
	add	r10, r6
	set_rrg	r6, r10
	out.h	r7, 4[r10]
	add	1, r6
	set_rrg	r6, r10
	out.h	r8, 4[r10]
	jmp	[lp]


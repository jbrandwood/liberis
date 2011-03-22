/*****************************************************************************
 *  Cache functions                                                     []   *
 *****************************************************************************/
	.global _cache_enable
	.global _cache_clear
	.global _cache_dump
	.global _cache_restore

_cache_enable:
	stsr	CHCW, r10
	ori	2, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_disable:
	mov	-3, r11
	stsr	CHCW, r10
	and	r11, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_clear:
	stsr	CHCW, r10
	shl	8, r7
	shl	20, r6
	or	r7, r10
	or	r6, r10
	ori	1, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_dump:
	stsr	CHCW, r10
	shl	8, r6
	or	r6, r10
	ori	16, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

_cache_restore:
	stsr	CHCW, r10
	shl	8, r6
	or	r6, r10
	ori	32, r10, r10
	ldsr	r10, CHCW
	jmp	[lp]

/*****************************************************************************
 *  IRQ functions                                                        []  *
 *****************************************************************************/
	.global _irq_enable
	.global	_irq_disable
	.global _irq_set_level
	.global	_irq_set_mask
	.global	_irq_get_level
	.global	_irq_get_mask
_irq_enable:
	stsr	PSW, r10
	movea	0x1000, r0, r12
	not	r12, r11
	and	r10, r11
	and	r12, r10
	shr	12, r10
	ldsr	r11, PSW
	jmp	[lp]

_irq_disable:
	stsr	PSW, r10
	movea	0x1000, r0, r11
	and	r11, r10
	or	r10, r11
	ldsr	r11, PSW
	jmp	[lp]

_irq_set_level:
	stsr	PSW, r10
	andi	0xF, r6, r6
	shl	16, r6
	movhi	0xF, r0, r11
	not	r11, r12
	and	r10, r12
	or	r6, r12
	ldsr	r12, PSW
	jmp	[lp]

_irq_set_mask:
	movea	0xE40, r0, r10
	out.h	r6, 0[r10]
	jmp	[lp]

_irq_set_priority:
	movea	0xE80, r0, r10
	mov	r6, r11
	shr	16, r11
	out.h	r11, 0x40[r10]
	out.h	r6, 0[r10]
	jmp	[lp]

_irq_get_level:
	stsr	PSW, r10
	movhi	0xF, r0, r11
	and	r11, r10
	jmp	[lp]

_irq_get_mask:
	movea	0xE40, r0, r10
	in.h	0[r10], r10
	jmp	[lp]

_irq_get_priority:
	movea	0xE80, r0, r10
	in.h	0x40[r10], r11
	shl	16, r11
	in.h	0[r10], r10
	or	r11, r10
	jmp	[lp]

/*****************************************************************************
 *  Memory functions                                                     []  *
 *****************************************************************************/
	.global	_memset32
	.global	_memset16
	.global	_memset
	.global _memcpy32
	.global	_memcpy16
	.global _memcpy
	.global	_memcmp32
	.global _memcmp16
	.global _memcmp

_memset32:
	add	r6, r8
1:
	st.w	r7, 0[r6]
	add	4, r6
	cmp	r8, r6
	bl	1b
	jmp	[lp]

_memset16:
	add	r6, r8
1:
	st.h	r7, 0[r6]
	add	2, r6
	cmp	r8, r6
	bl	1b
	jmp	[lp]

_memset:
	add	r6, r8
1:
	st.b	r7, 0[r6]
	add	1, r6
	cmp	r8, r6
	bl	1b
	jmp	[lp]

_memcpy32:
	shr	2, r8
1:
	ld.w	0[r6], r10
	st.w	r10, 0[r7]
	add	4, r6
	add	4, r7
	add	-1, r8
	bne	1b
	jmp	[lp]

_memcpy16:
	shr	1, r8
1:
	ld.h	0[r6], r10
	st.h	r10, 0[r7]
	add	2, r6
	add	2, r7
	add	-1, r8
	bne	1b
	jmp	[lp]

_memcpy:
1:
	ld.b	0[r6], r10
	st.b	r10, 0[r7]
	add	1, r6
	add	1, r7
	add	-1, r8
	bne	1b
	jmp	[lp]

_memcmp32:
	shr	2, r8
1:
	ld.w	0[r6], r10
	ld.w	0[r7], r11
	cmp	r10, r11
	bne	2f
	add	4, r6
	add	4, r7
	add	-1, r8
	bne	1b
2:	sub	r11, r10
	jmp	[lp]

_memcmp16:
	shr	1, r8
1:
	ld.h	0[r6], r10
	ld.h	0[r7], r11
	cmp	r10, r11
	bne	2f
	add	2, r6
	add	2, r7
	add	-1, r8
	bne	1b
2:	sub	r11, r10
	jmp	[lp]

_memcmp:
1:
	ld.b	0[r6], r10
	ld.b	0[r7], r11
	cmp	r10, r11
	bne	2f
	add	1, r6
	add	1, r7
	add	-1, r8
	bne	1b
2:	sub	r11, r10
	jmp	[lp]

/*****************************************************************************
 *  Port functions                                                       []  *
 *****************************************************************************/
	.global	_out32
	.global	_out16
	.global _out8
	.global _in32
	.global _in16
	.global _in8

_out32:
	out.w	r7, 0[r6]
	jmp	[lp]

_out16:
	out.h	r7, 0[r6]
	jmp	[lp]

_out8:
	out.b	r7, 0[r6]
	jmp	[lp]

_in32:
	in.w	0[r6], r10
	jmp	[lp]

_in16:
	in.h	0[r6], r10
	jmp	[lp]

_in8:
	in.b	0[r6], r10
	jmp	[lp]



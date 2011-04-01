/*****************************************************************************
 *  Backup memory (internal and external) support                        []  *
 *****************************************************************************/
	.global	_eris_bkupmem_set_access
	.global	_eris_bkupmem_read
	.global	_eris_bkupmem_write
_eris_bkupmem_set_access:
	shl	1, r7
	or	r7, r6
	out.h	r6, 0xC80[r0]
	jmp	[lp]

_eris_bkupmem_read:
	shl	27, r6
	movhi	0xE000, r6, r6
	shl	1, r8
	shl	1, r9
	add	r6, r8
	add	r8, r9
	mov	-2, r10
	and	r10, r9
	and	r10, r8
1:	ld.h	0[r8], r10
	st.b	r10, 0[r7]
	add	2, r8
	add	1, r7
	cmp	r8, r9
	bne	1b
	jmp	[lp]

_eris_bkupmem_write:
	shl	27, r6
	movea	0xFF, r0, r11
	movhi	0xE000, r6, r6
	shl	1, r8
	shl	1, r9
	add	r6, r8
	add	r8, r9
	mov	-2, r10
	and	r10, r9
	and	r10, r8
1:	ld.b	0[r7], r10
	and	r11, r10
	st.h	r10, 0[r8]
	add	2, r8
	add	1, r7
	cmp	r8, r9
	bne	1b
	jmp	[lp]



/*****************************************************************************
 *  ROM Font handling                                                    []  *
 *****************************************************************************/
	.global	_eris_romfont_get

/* TODO: Maybe ABI needs conversion? */
_eris_romfont_get:
	mov	0xC, r10
	movhi	0xFFF0, r10, r10
	jmp	[r10]

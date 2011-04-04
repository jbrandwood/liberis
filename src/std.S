/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  Memory functions                                                   []  *
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
 *  String functions                                                     []  *
 *****************************************************************************/
	.global	_strlen32
	.global	_strlen16
	.global	_strlen
	.global	_strcpy32
	.global	_strcpy16
	.global	_strcpy
	.global	_strcmp32
	.global	_strcmp16
	.global	_strcmp
	.global	_strnlen32
	.global	_strnlen16
	.global	_strnlen
	.global	_strncpy32
	.global	_strncpy16
	.global	_strncpy
	.global	_strncmp32
	.global	_strncmp16
	.global	_strncmp

_strlen32:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.w	0[r6], r11
	add	4, r6
	cmp	r0, r11
	bne	1b
	jmp	[lp]

_strlen16:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.h	0[r6], r11
	add	2, r6
	cmp	r0, r11
	bne	1b
	jmp	[lp]

_strlen:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.b	0[r6], r11
	add	1, r6
	cmp	r0, r11
	bne	1b
	jmp	[lp]

_strcpy32:
1:	ld.w	0[r7], r10
	st.w	r10, 0[r6]
	add	4, r7
	add	4, r6
	cmp	r10, r0
	bne	1b
	jmp	[lp]

_strcpy16:
1:	ld.h	0[r7], r10
	st.h	r10, 0[r6]
	add	2, r7
	add	2, r6
	cmp	r10, r0
	bne	1b
	jmp	[lp]

_strcpy:
1:	ld.b	0[r7], r10
	st.b	r10, 0[r6]
	add	1, r7
	add	1, r6
	cmp	r10, r0
	bne	1b
	jmp	[lp]

_strcmp32:
1:	ld.w	0[r6], r10
	ld.w	0[r7], r11
	add	4, r6
	add	4, r7
	cmp	r10, r0
	be	2f
	cmp	r11, r10
	be	1b
	sub	r11, r10
2:
	jmp	[lp]

_strcmp16:
1:	ld.h	0[r6], r10
	ld.h	0[r7], r11
	add	2, r6
	add	2, r7
	cmp	r10, r0
	be	2f
	cmp	r11, r10
	be	1b
	sub	r11, r10
2:
	jmp	[lp]

_strcmp:
1:	ld.b	0[r6], r10
	ld.b	0[r7], r11
	add	1, r6
	add	1, r7
	cmp	r10, r0
	be	2f
	cmp	r11, r10
	be	1b
	sub	r11, r10
2:
	jmp	[lp]

_strnlen32:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.w	0[r6], r11
	add	4, r6
	cmp	r10, r7
	be	3f
	cmp	r0, r11
	bne	1b
3:
	jmp	[lp]

_strnlen16:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.h	0[r6], r11
	add	2, r6
	cmp	r10, r7
	be	3f
	cmp	r0, r11
	bne	1b
3:
	jmp	[lp]

_strnlen:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.b	0[r6], r11
	add	1, r6
	cmp	r10, r7
	be	3f
	cmp	r0, r11
	bne	1b
3:
	jmp	[lp]

_strncpy32:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.w	0[r7], r11
	st.w	r11, 0[r6]
	cmp	r10, r8
	be	3f
	add	4, r7
	add	4, r6
	cmp	r11, r0
	bne	1b
3:
	jmp	[lp]

_strncpy16:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.h	0[r7], r11
	st.h	r11, 0[r6]
	cmp	r10, r8
	be	3f
	add	2, r7
	add	2, r6
	cmp	r11, r0
	bne	1b
3:
	jmp	[lp]

_strncpy:
	mov	r0, r10
	br	2f
1:	add	1, r10
2:	ld.b	0[r7], r11
	st.b	r11, 0[r6]
	cmp	r10, r8
	be	3f
	add	1, r7
	add	1, r6
	cmp	r11, r0
	bne	1b
3:
	jmp	[lp]

_strncmp32:
	mov	r0, r10
	br	1f
4:	add	1, r10
1:	ld.w	0[r6], r12
	ld.w	0[r7], r11
	cmp	r10, r8
	be	3f
	add	4, r6
	add	4, r7
	cmp	r12, r0
	be	2f
	cmp	r11, r12
	be	4b
3:	sub	r11, r12
2:
	jmp	[lp]

_strncmp16:
	mov	r0, r10
	br	1f
4:	add	1, r10
1:	ld.h	0[r6], r12
	ld.h	0[r7], r11
	cmp	r10, r8
	be	3f
	add	2, r6
	add	2, r7
	cmp	r12, r0
	be	2f
	cmp	r11, r12
	be	4b
3:	sub	r11, r12
2:
	jmp	[lp]

_strncmp:
	mov	r0, r10
	br	1f
4:	add	1, r10
1:	ld.b	0[r6], r12
	ld.b	0[r7], r11
	cmp	r10, r8
	be	3f
	add	1, r6
	add	1, r7
	cmp	r10, r0
	be	2f
	cmp	r11, r10
	be	4b
3:	sub	r11, r10
2:
	jmp	[lp]


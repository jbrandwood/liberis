/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

	.section .text
	.align	2

/*************************************************
  startup code
 *************************************************/
	.global	_start
	.global	_dbgbreak

_start:
	jr	_realstart

_dbgbreak:
	jmp	[lp]

_realstart:
	/* Initialize registers */
	movhi	hi(__stack), r0, sp
	movea	lo(__stack), sp, sp
	movhi	hi(__gp), r0, gp
	movea	lo(__gp), gp, gp

	/* Cache control */
	ldsr	r0, chcw
	movhi	1, r0, r10
	movea	1, r10, r10
	ldsr	r10, chcw
	mov	1, r10
	ldsr	r10, chcw

	/* Clear BSS */
	movhi	hi(__bss_start), r0, r6
	movea	lo(__bss_start), r6, r6
	movhi	hi(__bss_end), r0, r7
	movea	lo(__bss_end), r7, r7
1:	st.b	r0, 0[r6]
	addi	1, r6, r6
	cmp	r7, r6
	bl	1b

	/* call main function */
	addi	-12, sp, sp
	mov	r0, r6
	mov	r0, r7
	mov	r0, r8
	jal	_main

	/* jump to exit */
	mov	r10, r6
	jr	_exit

/*************************************************
  void exit(int code)
 *************************************************/
	.global	_exit
	.type	_exit,@function

_exit:
	/* jump to _exit */
	jr	__exit

	.size	_exit, .-_exit


/*************************************************
  void _exit()
 *************************************************/
	.global	__exit
	.type	__exit,@function

__exit:	trap	30
	halt

	.size	__exit, .-__exit

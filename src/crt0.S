	.section .text
	.align	1

/*************************************************
  startup code
 *************************************************/
	.global	_start

_start:
	/* Initialize registers */
	movhi	hi(_stack), r0, sp
	movea	lo(_stack), sp, sp
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
	movhi	hi(_edata), r0, r6
	movea	lo(_edata), r6, r6
	movhi	hi(_end), r0, r7
	movea	lo(_end), r7, r7
1:	st.b	r0, 0[r6]
	addi	1, r6, r6
	cmp	r7, r6
	bl	1b

	/* Call ctors */
	movhi	hi(___ctors_end), r0, r10
	movea	lo(___ctors_end), r10, r29
	movhi	hi(___ctors), r0, r10
	movea	lo(___ctors), r10, r28
	cmp	r28, r29
	bnh	3f
2:	add	-4, r29
	ld.w	0[r29], r10
	jal	.+4
	add	4, r31
	jmp	r10
	cmp	r28, r29
	bh	2b
3:
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

_exit:	/* call dtors */
	movhi	hi(___dtors), r0, r10
	movea	lo(___dtors), r10, r29
	movhi	hi(___dtors_end), r0, r10
	movea	lo(___dtors_end), r10, r28
	cmp	r28, r29
	bnl	2f
1:	ld.w	0[r29], r10
	add	4, r29
	jal	.+4
	add	4, r31
	jmp	r10
	cmp	r28, r29
	bl	1b
2:
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


/*************************************************
  stack area
 *************************************************/
	.section .stack
_stack:	.long 	1


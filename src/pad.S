/*****************************************************************************
 *  Pad control                                                          []  *
 *****************************************************************************/
	.global	_eris_pad_read_status
	.global	_eris_pad_read_data
	.global	_eris_pad_write_control

_eris_pad_read_status:
	shl	7, r6
	in.h	0[r6], r10
	jmp	[lp]

_eris_pad_read_data:
	shl	7, r6
	ori	0x40, r6, r6
	in.w	0[r6], r10
	jmp	[lp]

_eris_pad_write_control:
	shl	7, r6
	out.h	r7, 0[r6]
	jmp	[lp]


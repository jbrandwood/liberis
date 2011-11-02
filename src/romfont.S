/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*****************************************************************************
 *  ROM Font handling                                                    []  *
 *****************************************************************************/
	.global	_eris_romfont_get

/* TODO: Maybe ABI needs conversion? */
_eris_romfont_get:
	mov	0xC, r10
	movhi	0xFFF0, r10, r10
	jmp	[r10]

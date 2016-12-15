/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>
Copyright (C) 2016              John Brandwood <john@telzey.com>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*************************************************
  PC-FX Memory Layout ...

  2MB RAM is located from $00000000-$001FFFFF.

  BIOS loads code from CD using parameters in the
  boot sector.

  By default, we're loading and running at $8000.

  BIOS uses RAM $7E00-$7FFF for itself.

  BIOS "fsys" functions use the lowest 88 bytes
  of memory addressed by the gp register (r4).

  That's -32768[gp] to -32681[gp].

  The PC-FX linker script reserves this space so
  that the fsys functions can be used.
 *************************************************/


/*************************************************
  start of reserved memory for bios usage
 *************************************************/

                .global __zplim
__zplim         =       0x7e00


/*************************************************
  startup code               pc-fx location $8000
 *************************************************/

                .section .text
                .align          2

                .global _start
                .global _jmp_r1
                .global _dbgbreak
                .global _dbgfatal
                .global _dbgstack

_start:         jr      __main


/*************************************************
  helper function            pc-fx location $8004
 *************************************************/

_jmp_r1:        jmp     [r1]
                nop


/*************************************************
  void dbgbreak (void)       pc-fx location $8008
 *************************************************/

_dbgbreak:      jmp     [lp]
                nop


/*************************************************
  void dbgfatal (void)       pc-fx location $800C 
 *************************************************/

_dbgfatal:      halt
                br      _dbgfatal


/*************************************************
  void dbgstack (void)       pc-fx location $8010 
 *************************************************/

_dbgstack:      halt
                br      _dbgstack


/*************************************************
  void exit (int code)       pc-fx location $8014
 *************************************************/

                .global _exit
                .type   _exit,@function

                /* jump to _exit */
_exit:          jr      __exit

                .size   _exit, .-_exit


/*************************************************
  void _exit (void)          pc-fx location $8018
 *************************************************/

                .global __exit
                .type   __exit,@function

__exit:         trap    30
                halt

                .size   __exit, .-__exit


/*************************************************
  startup code               pc-fx location $801C
 *************************************************/

                /* initialize registers */
__main:         movhi   hi(__stack),r0,sp
                movea   lo(__stack),sp,sp
                movhi   hi(__gp),r0,gp
                movea   lo(__gp),gp,gp
                movhi   hi(__tp),r0,tp
                movea   lo(__tp),tp,tp
                mov     r0,fp

                /* disable-clear-enable cache */
                ldsr    r0,chcw
                ori     0x8001,r0,r1
                ldsr    r1,chcw
                mov     2,r1
                ldsr    r1,chcw

                /* the .zdata segment contents are loaded into */
                /* memory at the beginning of the .bss segment */
                movhi   hi(_edata),r0,r6
                movea   lo(_edata),r6,r6
                ori     lo(__zpdat),r0,r7
                ori     lo(__zpbss),r0,r8
                ori     lo(__zplim),r0,r9

                /* hang if asked to overwrite bios data */
                ori     lo(__zpend),r0,r1
                cmp     r9,r1
1$:             bgt     1$

                /* copy .zdata segment to destination */
                /* 8-byte chunks, 8-byte aligned */
                cmp     r7,r8
                movea   -8,r8,r1
                be      3$
2$:             ld.w    0[r6],r10
                ld.w    4[r6],r11
                cmp     r1,r7
                st.w    r10,0[r7]
                movea   8,r6,r6
                st.w    r11,4[r7]
                movea   8,r7,r7
                bl      2$

                /* clear .zbss segment. */
                /* 8-byte chunks, 8-byte aligned */
3$:             cmp     r8,r9
                movea   -8,r9,r1
                be      5$
4$:             st.w    r0,0[r8]
                cmp     r1,r8
                st.w    r0,4[r8]
                movea   8,r8,r8
                bl      4$

                /* clear .sbss & .bss segments & main ram */
                /* 8-byte chunks, 8-byte aligned */
5$:             movhi   hi(_edata),r0,r6
                movea   lo(_edata),r6,r6
                movea   -8,sp,r1
6$:             st.w    r0,0[r6]
                cmp     r1,r6
                st.w    r0,4[r6]
                movea   8,r6,r6
                bl      6$

                /* c++ static constructors */
                movhi   hi(___ctors),r0,r28
                movea   lo(___ctors),r28,r28
                movhi   hi(___ctors_end),r0,r29
                movea   lo(___ctors_end),r29,r29
                br      8$
7$:             ld.w    -4[r29],r1
                add     -4,r29
                jal     _jmp_r1
8$:             cmp     r28,r29
                bne     7$

                /* call main function */
                mov     r0,r6
                mov     r0,r7
                jal     _main

                /* jump to exit */
                mov     r10,r6
                jr      _exit

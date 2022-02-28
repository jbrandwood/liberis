/*
        liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011              Alex Marshall "trap15" <trap15@raidenii.net>
Copyright (C) 2016-2022         John Brandwood <john@telzey.com>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*************************************************
  PC-FX Memory Layout ...

  2MB RAM is located from $00000000-$001FFFFF.

  BIOS loads code from CD using parameters in the
  boot sector.

  By default, we're loading and running at $8000.

  BIOS reserves $7E00-$7FFF for itself.
  liberis reserves $7C00-$7DFF for CD directory.

  BIOS "fsys" functions use the lowest 84 bytes
  of memory addressed by the gp register (r4).

  That's -32768[gp] to -32685[gp].

  The PC-FX linker script reserves this space so
  that the "fsys" functions can be used.
 *************************************************/


/*************************************************
  startup code               pc-fx location $8000
 *************************************************/

                .section .text
                .align  2

                .global _start
                .global _dbgbreak
                .global _dbgfatal
                .global _dbgstack
                .global _jmp_r1
                .global __main

_start:         br      __main
                nop


/*************************************************
  void dbgbreak (void)       pc-fx location $8004
 *************************************************/

_dbgbreak:      jmp     [lp]
                nop


/*************************************************
  void dbgfatal (void)       pc-fx location $8008
 *************************************************/

_dbgfatal:      halt
                br      _dbgfatal


/*************************************************
  void dbgstack (void)       pc-fx location $800C
 *************************************************/

_dbgstack:      halt
                br      _dbgstack


/*************************************************
  helper function            pc-fx location $8010
 *************************************************/

_jmp_r1:        jmp     [r1]
                nop


/*************************************************
  void _exit (void)          pc-fx location $8014
 *************************************************/

                .global __exit
                .type   __exit,@function

__exit:         trap    30
                halt

                .size   __exit, .-__exit


/*************************************************
  void exit (int code)       pc-fx location $8018
 *************************************************/

                .global _exit
                .type   _exit,@function

                /* jump to _exit */
_exit:          jr      __exit

                .size   _exit, .-_exit


/*************************************************
  startup code               pc-fx location $801C
 *************************************************/

                .global __main
                .type   __main,@function

                /* initialize registers */
                /* preserve current sp if __stack == 0 */
__main:         movhi   hi(__stack),r0,r1
                movea   lo(__stack),r1,r1
                cmp     0,r1
                be      .L_skip_sp
                mov     r1,sp
.L_skip_sp:     mov     r0,fp
                movhi   hi(__gp),r0,gp
                movea   lo(__gp),gp,gp
                movhi   hi(__tp),r0,tp
                movea   lo(__tp),tp,tp

                /* disable-clear-enable cache */
                ldsr    r0,chcw
                movea   0x8001,r0,r1
                ldsr    r1,chcw
                mov     2,r1
                ldsr    r1,chcw

                /* preserve isolink cd-rom directory from where the */
                /* pc-fx firmware loads the 2nd cd sector into ram */
                ld.h    0x7C00[r0],r1
                cmp     0,r1
                mov     r0,r26
                mov     r0,r27
                bne     .L_skip_cd
                movea   512*8,r0,r28
                movea   0x7C00,r0,r29
                movea   0x6600,r0,r30
                movbsu

                /* hang if asked to overwrite reserved memory */
                /* i.e. if __zdaend > __zdalimit */
.L_skip_cd:     movea   lo(__zdalimit),r0,r6
                movea   lo(__zdaend),r0,r1
                cmp     r1,r6
.L_hang:        bn      .L_hang

                /* the .zdata segment contents are loaded from */
                /* memory at the beginning of the .bss segment */
.L_zdadata:     movea   lo(__zdabss),r0,r28
                movea   lo(__zdadata),r0,r29
                sub     r29,r28
                movhi   hi(__edata),r0,r30
                movea   lo(__edata),r30,r30
                mov     r30,r7
                be      .L_zdabss
                shl     3,r28
                movbsu

                /* clear .zbss segment (to __zdalimit) */
                /* 8-byte chunks, 8-byte aligned */
.L_zdabss:      addi    -8,r6,r6
                cmp     r6,r29
                bh      .L_sdabss
.L_zdafill:     st.w    r0,0[r29]
                cmp     r6,r29
                st.w    r0,4[r29]
                movea   8,r29,r29
                bl      .L_zdafill

                /* clear .sbss & .bss segments & main ram (to __sp) */
                /* 8-byte chunks, 8-byte aligned */
.L_sdabss:      mov     -8,r1
                and     sp,r1
                addi    -8,r1,r1
.L_bssfill:     st.w    r0,0[r7]
                cmp     r1,r7
                st.w    r0,4[r7]
                movea   8,r7,r7
                bl      .L_bssfill

                /* c++ static constructors */
                movhi   hi(___ctors),r0,r28
                movea   lo(___ctors),r28,r28
                movhi   hi(___ctors_end),r0,r29
                movea   lo(___ctors_end),r29,r29
                br      .L_next_ctor
.L_ctor_loop:   ld.w    -4[r29],r1
                add     -4,r29
                jal     _jmp_r1
.L_next_ctor:   cmp     r28,r29
                bne     .L_ctor_loop

                /* call main function */
                mov     r0,r6
                mov     r0,r7
                jal     _main

                /* jump to exit */
                mov     r10,r6
                br      _exit

                .size   __main, .-__main

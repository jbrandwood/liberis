/*
	liberis -- A set of libraries for controlling the NEC PC-FX

Copyright (C) 2011		Alex Marshall "trap15" <trap15@raidenii.net>

# This code is licensed to you under the terms of the MIT license;
# see file LICENSE or http://www.opensource.org/licenses/mit-license.php
*/

/*
6.31.30  V850 Function Attributes
The V850 back end supports these function attributes:
__attribute__ ((interrupt))
__attribute__ ((interrupt_handler))
Use these attributes to indicate that the specified function is an interrupt han-
dler.  The compiler generates function entry and exit sequences suitable for use
in an interrupt handler when either attribute is present

6.32.13  V850 Variable Attributes
These variable attributes are supported by the V850 back end:
sda
Use this attribute to explicitly place a variable in the small data area, which
can hold up to 64 kilobytes.
tda
Use this attribute to explicitly place a variable in the tiny data area, which can
hold up to 256 bytes in total.
zda
Use this attribute to explicitly place a variable in the first 32 kilobytes of mem-
ory
*/

// #include <stdlib.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <eris/types.h>
#include <eris/std.h>
#include <eris/v810.h>
#include <eris/king.h>
#include <eris/tetsu.h>
#include <eris/romfont.h>

const int __attribute__ ((zda)) zda_constant         = 0xDEADBEEF;
volatile int __attribute__ ((zda)) zda_initialized   = 0x12345678;
volatile int __attribute__ ((zda)) zda_uninitialized = 0;
volatile int sda_frame_count = 0;

/* Declare this "noinline" to ensure that my_irq1() is not a leaf. */
__attribute__ ((noinline)) void increment_sda_frame_count (void)
{
  sda_frame_count++;
}

/* Simple test interrupt_handler that is not a leaf. */
__attribute__ ((interrupt_handler)) void my_irq1 (void)
{
  for (int i = 0; i < 100; i++)
    increment_sda_frame_count();
}

/* Simple test interrupt_handler that is a leaf. */
__attribute__ ((interrupt_handler)) void my_irq2 (void)
{
  for (int i = 0; i < 100; i++)
  {
    zda_uninitialized++;
    zda_initialized += zda_constant; 
  }
}

void printch(u32 sjis, u32 kram, int tall);
void printstr(const char* str, int x, int y, int tall);

int fake_sprintf(char *str, const char *fmt, ...)
{
  va_list ap;

  va_start( ap, fmt );

  int val = va_arg( ap, int );

  if (val == 0xdeadbeef)
    strcpy(str, "Got DEADBEEF!");
  else
    strcpy(str, "Not DEADBEEF!");

  va_end( ap );

  return (13);
}

int main(int argc, char *argv[])
{
	int i;
	char str[256];
	u16 microprog[16];

	eris_king_init();
	eris_tetsu_init();
	
	eris_tetsu_set_priorities(0, 0, 1, 0, 0, 0, 0);
	eris_tetsu_set_king_palette(0, 0, 0, 0);
	eris_tetsu_set_rainbow_palette(0);

	eris_king_set_bg_prio(KING_BGPRIO_3, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, KING_BGPRIO_HIDE, 0);
	eris_king_set_bg_mode(KING_BGMODE_4_PAL, 0, 0, 0);
	eris_king_set_kram_pages(0, 0, 0, 0);

	for(i = 0; i < 16; i++) {
		microprog[i] = KING_CODE_NOP;
	}

	microprog[0] = KING_CODE_BG0_CG_0;
	eris_king_disable_microprogram();
	eris_king_write_microprogram(microprog, 0, 16);
	eris_king_enable_microprogram();

	eris_tetsu_set_palette(0, 0x0088);
	eris_tetsu_set_palette(1, 0xE088);
	eris_tetsu_set_palette(2, 0xE0F0);
	eris_tetsu_set_palette(3, 0x602C);
	eris_tetsu_set_video_mode(TETSU_LINES_262, 0, TETSU_DOTCLOCK_5MHz, TETSU_COLORS_16,
				TETSU_COLORS_16, 0, 0, 1, 0, 0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0, 0, 0);
	eris_king_set_bat_cg_addr(KING_BG0SUB, 0, 0);
	eris_king_set_scroll(KING_BG0, 0, 0);
	eris_king_set_bg_size(KING_BG0, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256, KING_BGSIZE_256);

	eris_king_set_kram_read(0, 1);
	eris_king_set_kram_write(0, 1);
	// Clear BG0's RAM
	for(i = 0x0; i < 0x1E00; i++) {
		eris_king_kram_write(0);
	}
	eris_king_set_kram_write(0, 1);

	printstr("Hello World!", 10, 0x20, 1);
	printstr("Love, NEC", 11, 0x38, 0);

	i = fake_sprintf(str, "Eat %X!", 0xdeadbeef);
//	i = sprintf(str, "Eat %X!", 0xdeadbeef);
	printstr(str, ((32 - i) / 2), 0x48, 0);

	return 0;
}

void printstr(const char* str, int x, int y, int tall)
{
	int i;
	u32 kram = x + (y << 5);
	int len = strlen(str);
	for(i = 0; i < len; i++) {
		printch(str[i], kram + i, tall);
	}
}

void printch(u32 sjis, u32 kram, int tall)
{
	u16 px;
	int x, y;
	u8* glyph = eris_romfont_get(sjis, tall ? ROMFONT_ANK_8x16 : ROMFONT_ANK_8x8);
	for(y = 0; y < (tall ? 16 : 8); y++) {
		eris_king_set_kram_write(kram + (y << 5), 1);
		px = 0;
		for(x = 0; x < 8; x++) {
			if((glyph[y] >> x) & 1) {
				px |= 1 << (x << 1);
			}
		}
		eris_king_kram_write(px);
	}
}

#if 0
//#include <_ansi.h>
//#include <sys/types.h>
#include <sys/stat.h>

caddr_t
sbrk (int incr)
{
  extern char   heap_start[];	/* Defined by the linker script.  */
  static char * heap_end = NULL;
  char *        prev_heap_end;
  char *        sp = (char *) & sp;

  if (heap_end == NULL)
    heap_end = heap_start;

  prev_heap_end = heap_end;

  if (heap_end + incr > sp)
    {
/*
#define MESSAGE "Heap and stack collision\n"
      _write (1, MESSAGE, sizeof MESSAGE);
      _write (STDERR_FILENO, "Heap and stack collision\n", 25);
      errno = ENOMEM;
      abort ();
*/

      return (caddr_t) -1;
    }

  heap_end += incr;

  return (caddr_t) prev_heap_end;
}
#endif

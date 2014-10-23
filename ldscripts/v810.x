OUTPUT_FORMAT("elf32-v810")
OUTPUT_ARCH(v810)
ENTRY(_start)

SECTIONS
{
  . = 0x00008000; /* after the reserved work area */

  . = ALIGN(4);
  __text_start = .;
  .text		: {
    *(.text)
    *(.text.*)
  }
  __text_end = .;

  . = ALIGN(4);
  .rodata	: { *(.rodata) *(.rodata.*) }
  .data		: { *(.data) *(.data.*) }
  .got		: { *(.got.plt) *(.got) }
  .dynamic	: { *(.dynamic) }

  . = ALIGN(4);
  __gp = . + 0x8000;
  .sdata : { *(.sdata) }

  __bss_start = .;
  .sbss : { *(.sbss) *(.scommon) }
  .bss :  { *(.dynbss) *(.bss) *(COMMON) }
  __bss_end = . ;

  /* User stack, located at the highest position in memory */
  __stack = 0x00200000;
}

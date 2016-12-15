/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-v810", "elf32-v810", "elf32-v810")
OUTPUT_ARCH(v810)
ENTRY(_start)
SEARCH_DIR(.);
EXTERN(__gp __tp __tpend __zpdat __zpbss __zpend);
SECTIONS
{
  /* Read-only sections, merged into text segment.  */
  . = 0x8000;
  .text		ALIGN (4) :
  {
    *(.text)
    *(.text.*)
    /* .gnu.warning sections are handled specially by elf32.em.  */
    *(.gnu.warning)
    *(.gnu.linkonce.t*)
  } =0
  _etext = .;
  PROVIDE (etext = .);
  .init		: { KEEP (*(.init)) } =0
  .fini		: { KEEP (*(.fini)) } =0
  .rodata	ALIGN (4) :
  {
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r*)
  }
  .rodata1	: { *(.rodata1) }
  .data         ALIGN (4) :
  {
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d*)
    CONSTRUCTORS
  }
  .data1	: { *(.data1) }
  .ctors	ALIGN (4) :
  {
    ___ctors = .;
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend(.ctors))
    ___ctors_end = .;
  }
  /* Discard these sections on PC-FX & VirtualBoy.  */
  /DISCARD/     :
  {
    *(.dtors)
    *(.dtors.*)
    *(.gcc_except_table)
  }
  /* Extra section for 32KB/64KB of tp (aka R5) relative addressing.
     This could for thread-local variables instead if we get fancy.  */
  .tdata        ALIGN (8) :
  {
	PROVIDE (__tp = .);
	*(.tbyte)
	*(.tcommon_byte)
	*(.tdata)
	*(.tbss)
	*(.tcommon)
	. = ALIGN (8);
	PROVIDE (__tpend = .);
  }
  /* We want the small data sections together, so single-instruction offsets
     can access them all, and initialized data all before uninitialized, so
     we can shorten the on-disk segment size.  */
  .sdata        ALIGN (8) :
  {
	PROVIDE (__gp = . + 0x8000);
	. = 0x58;
	*(.sdata)
  }
  /* This is the read only part of the small data area.
     Having it as a seperate section prevents its
     attributes from being inherited by the sdata
     section.  Specifically it prevents the sdata
     section from being marked READONLY.  */
  .rosdata      ALIGN (4) :
  {
	*(.rosdata)
  }
  /* We place the .sbss data section AFTER the .rosdata section, so that
     it can directly preceed the .bss section.  This allows runtime startup
     code to initialise all the zero-data sections by simply taking the
     value of '_edata' and zeroing until it reaches '_end'.  */
  /* 8-byte align these sections to speed up clearing them in crt0.S  */
  . = ALIGN (8);
  .sbss         ALIGN (4) :
  {
	__sbss_start = .;
	*(.sbss)
	*(.scommon)
  }
  _edata  = DEFINED (__sbss_start) ? __sbss_start : . ;
  PROVIDE (edata = _edata);
  .bss          ALIGN (4) :
  {
	__bss_start = DEFINED (__sbss_start) ? __sbss_start : . ;
	__real_bss_start = . ;
	*(.dynbss)
	*(.bss)
	*(COMMON)
  }
  . = ALIGN (8);
  _end = . ;
  PROVIDE (end = .);
  PROVIDE (_heap_start = .);
  /* Put all initialized R0-relative data at the end of the output file on
     top of the .sbss/.bss sections so that it can be copied into place at
     startup and then wiped to zero for use as the .sbss/.bss  */
  . = 0x0000;
  /* 8-byte align these sections to speed up relocating them in crt0.S  */
  . = ALIGN (8);
  PROVIDE (__zpdat = .);
  .zdata : AT ( _edata )
  {
	*(.rozdata)
	*(.zdata)
        . = ALIGN (8);
  }
  PROVIDE (__zpbss = .);
  .zbss : AT ( ADDR (.zdata) + SIZEOF (.zdata) )
  {
	*(.zbss)
	*(.zcommon)
        . = ALIGN (8);
  }
  PROVIDE (__zpend = .);
  /* Stabs debugging sections.  */
  .stab 0		: { *(.stab) }
  .stabstr 0		: { *(.stabstr) }
  .stab.excl 0		: { *(.stab.excl) }
  .stab.exclstr 0	: { *(.stab.exclstr) }
  .stab.index 0		: { *(.stab.index) }
  .stab.indexstr 0	: { *(.stab.indexstr) }
  .comment 0		: { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0	: { *(.debug) }
  .line           0	: { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0	: { *(.debug_srcinfo) }
  .debug_sfnames  0	: { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0	: { *(.debug_aranges) }
  .debug_pubnames 0	: { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0	: { *(.debug_info) *(.gnu.linkonce.wi.*) }
  .debug_abbrev   0	: { *(.debug_abbrev) }
  .debug_line     0	: { *(.debug_line) }
  .debug_frame    0	: { *(.debug_frame) }
  .debug_str      0	: { *(.debug_str) }
  .debug_loc      0	: { *(.debug_loc) }
  .debug_macinfo  0	: { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions.  */
  .debug_weaknames 0	: { *(.debug_weaknames) }
  .debug_funcnames 0	: { *(.debug_funcnames) }
  .debug_typenames 0	: { *(.debug_typenames) }
  .debug_varnames  0	: { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  /* DWARF Extension.  */
  .debug_macro    0 : { *(.debug_macro) }
  /* User stack.  */
  .stack 0x200000	:
  {
	__stack = .;
	*(.stack)
  }
}

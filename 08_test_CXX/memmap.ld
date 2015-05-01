OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Entry)

MEMORY
{
   DDR0 : ORIGIN = 0x80000000, LENGTH = 0x20000000
}

C_STACK_SIZE   = 20k;
IRQ_STACK_SIZE = 256;
FIQ_STACK_SIZE = 256;
SVC_STACK_SIZE = 256;
ABT_STACK_SIZE = 256;
UND_STACK_SIZE = 256;
ALL_STACK_SIZE = UND_STACK_SIZE + ABT_STACK_SIZE + SVC_STACK_SIZE + FIQ_STACK_SIZE + IRQ_STACK_SIZE + C_STACK_SIZE;
SECTIONS
{

    .rsthand :
    {
        . = ALIGN(0x10000);
        KEEP(*(.isr_vector))
        *core.o (.text)
    } > DDR0
    
    . = ALIGN(4);
    .text :
    {
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
         *crtbegin.o(.dtors)
         *crtbegin?.o(.dtors)
         *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
         *(SORT(.dtors.*))
         *(.dtors)

        *(.rodata*)

        KEEP(*(.eh_frame*))
    } > DDR0

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > DDR0

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > DDR0
    __exidx_end = .;

        
    .data :
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(vtable)
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;

    } > DDR0

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > DDR0

    /*.ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > DDR0 */

   _end = . + 4 ;
   __stack = ORIGIN(DDR0)+LENGTH(DDR0);

   .stack :
   {
      . = ORIGIN(DDR0)+LENGTH(DDR0) - ALL_STACK_SIZE;
      __stack_start__ = .;
      . += IRQ_STACK_SIZE;
      . = ALIGN(4);
      __irq_stack_top__ = .;

      . += FIQ_STACK_SIZE;
      . = ALIGN(4);
      __fiq_stack_top__ = .;

      . += SVC_STACK_SIZE;
      . = ALIGN(4);
      __svc_stack_top__ = .;

      . += ABT_STACK_SIZE;
      . = ALIGN(4);
      __abt_stack_top__ = .;

      . += UND_STACK_SIZE;
      . = ALIGN(4);
      __und_stack_top__ = .;

      . += C_STACK_SIZE;
      . = ALIGN(4);
      __c_stack_top__ = .;

      __stack_end__ = .;
   } > DDR0
}



/*
The MIT License (MIT)

Copyright (c) 2015 Alexis Marquet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

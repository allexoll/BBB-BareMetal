OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(Entry)

MEMORY
{
   ram : ORIGIN = 0x402f0400, LENGTH = 0x1B400
   public_stack : ORIGIN = 0x4030B800, LENGTH = 0x1600
}

C_STACK_SIZE   = 2k;
IRQ_STACK_SIZE = 256;
FIQ_STACK_SIZE = 256;
SVC_STACK_SIZE = 256;
ABT_STACK_SIZE = 256;
UND_STACK_SIZE = 256;
SECTIONS
{


    .text : { *(.text*) } > ram
    .rodata : { *(.rodata*) } > ram
    .data : { *(.data*) } > ram


.bss : {
. = ALIGN(4);
__bss_start__ = .;
*(.bss*)
__bss_end__ = .;
} > ram
_end = . + 4 ;
stack_ptr = ORIGIN(ram)+LENGTH(ram);


.stack :
{
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
} > public_stack
}

. = 0x4030CE00;
__isr_table_start__ = .;


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

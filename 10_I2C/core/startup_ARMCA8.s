
.equ IRQ_MODE, 0x12
.equ FIQ_MODE, 0x11
.equ SVC_MODE, 0x13
.equ ABT_MODE, 0x17
.equ UND_MODE, 0x1B
.equ SYS_MODE, 0x1F

.equ I_BIT,    0x80
.equ F_BIT,    0x40

.text
.code 32

.global Entry
.func
Entry:

__isr_vectors:
   ldr pc,[pc,#24]
   ldr pc,[pc,#24]
   ldr pc,[pc,#24]
   ldr pc,[pc,#24]
   ldr pc,[pc,#24]
   ldr pc,[pc,#24]
   ldr pc,[pc,#24]
   ldr pc,[pc,#24]
   .long startup
   .long UNDEF_Handler
   .long SWI_Handler
   .long PREFETCH_Handler
   .long DATA_Handler
   .long 0
   .long IRQ_Handler
   .long FIQ_Handler

startup:
   ldr r0, =__isr_vectors
   mcr p15, 0, r0, c12, c0, 0


// Clear the .bss section (zero init) 
   ldr r1,=__bss_start__
   ldr r2,=__bss_end__
   mov r3,#0
1:
   cmp r1,r2
   stmltia r1!,{r3}
   blt 1b

   // Initialize stack pointers for all ARM modes
   msr cpsr_c,#(IRQ_MODE | I_BIT |F_BIT)
   ldr sp,=__irq_stack_top__     // set the IRQ stack pointer

   msr cpsr_c,#(FIQ_MODE | I_BIT |F_BIT)
   ldr sp,=__fiq_stack_top__     // set the FIQ stack pointer

   msr cpsr_c,#(SVC_MODE | I_BIT |F_BIT)
   ldr sp,=__svc_stack_top__     // set the SVC stack pointer

   msr cpsr_c,#(ABT_MODE | I_BIT |F_BIT)
   ldr sp,=__abt_stack_top__     // set the ABT stack pointer

   msr cpsr_c,#(UND_MODE | I_BIT |F_BIT)
   ldr sp,=__und_stack_top__     // set the UND stack pointer

   msr cpsr_c,#(SYS_MODE | I_BIT |F_BIT)
   ldr sp,=__c_stack_top__     // set the C stack pointer



   MRC   p15, #0, r3, c1, c0, #2    @ Read CPACR
   ORR   r3, r3, #0x00F00000        @ Enable access to CP10 and CP11
   MCR   p15, #0, r3, c1, c0, #2    @ Write CPACR
   MOV   r3, #0
   MOV   r0,#0x40000000
   FMXR  FPEXC,r0                   @ Set FPEXC bit 30 to enable VFP
   ISB

   ldr r10,=coreInit
   mov lr,pc
   bx r10

   ldr r10,=procInit
   mov lr,pc
   bx r10

   ldr r10,=boardInit
   mov lr,pc
   bx r10
   
   ldr r10,=__libc_init_array
   mov lr,pc
   bx r10

   ldr r10, =main
	mov lr,pc
	bx r10
	bl exit
.endfunc
.end

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
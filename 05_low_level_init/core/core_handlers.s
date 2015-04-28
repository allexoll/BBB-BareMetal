/**
 * @file core_handler.s
 * @author Alexis Marquet
 * @date 27 Feb 2015
 * @brief this files contains the EXC handlers.
 **/

.equ NO_IRQ,      0x80              // mask to disable IRQ
.equ NO_FIQ,      0x40              // mask to disable FIQ
.equ NO_INT,      (NO_IRQ|NO_FIQ)   // mask to disable IRQ & FIQ
.equ IRQ_MODE, 0x12
.equ USR_MODE, 0x10
.equ FIQ_MODE, 0x11
.equ SVC_MODE, 0x13
.equ ABT_MODE, 0x17
.equ UND_MODE, 0x1B
.equ SYS_MODE, 0x1F

.text
.code 32
.globl IRQ_Handler
.func IRQ_Handler
IRQ_Handler:
	stmfd sp!, {r0-r12, lr}	// save working registers and link register
	mrs r11, spsr           // save the spsr into r11
	ldr r0, =0x48200040
	ldr r0, [r0]
	and r0,r0,#0x7F
	ISB
	DSB
	blx procIrqHandler
	
	mov r0, #0x01           // get the new irq agr
	ldr r1, =0x48200048
	str r0, [r1]            // write the bit to allow new interrupts
   DSB                     // Data Synchronization Barrier
	msr spsr, r11
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c, r0
	ldmfd sp!, {r0-r12, lr}	// restore working registers and link register
	subs pc, lr, #4
   
.endfunc
/* }IRQ_exit */

.globl FIQ_Handler
FIQ_Handler:
   // GP devices does not support FIQ



.globl UNDEF_Handler
UNDEF_Handler:
   sub r0,lr,#4         // set line number to the exeption address
   b ARM_exept

.globl SWI_Handler
SWI_Handler:
   sub r0,lr,#4         // set line number to the exeption address
   b ARM_exept

.globl PREFETCH_Handler
PREFETCH_Handler:
   sub r0,lr,#4         // set line number to the exeption address
   b ARM_exept

.globl DATA_Handler
DATA_Handler:
   sub r0,lr,#4         // set line number to the exeption address
   b ARM_exept


.globl ARM_exept
ARM_exept:
   msr cpsr_c,#(SYS_MODE | NO_INT)  // system mode, int/fiq disabled
   ldr r12,=BSP_abort
   mov lr,pc // store the return address
   bx r12      // call the assertion handler (ARM/THUMB)
   /* the handler should never return, but in cas it does, loop infinitely */
   b .      // infinite loop



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



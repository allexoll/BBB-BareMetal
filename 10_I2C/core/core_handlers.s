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
 /*  mov r13, r0
   sub r0, lr #4
   mov lr, r1
   mrs r1, spsr

   msr cpsr_c, #(SYS_MODE | NO_IRQ)
   stmfd sp!, {r0,r1}
   stmfd sp!, {r2-r3,r12,lr}
   mov   r0, sp
   sub sp,sp, #(2*4)
   msr cpsr_c, #(IRQ_MODE | NO_IRQ)
   stmfd r0!, {r13,r14}

   msr cpsr_c, #(SYS_MODE | NO_IRQ)


   ldr r12, =procIrqHandler
   mov lr, pc
   bx r12

   msr cpsr_c, #(SYS_MODE | NO_INT)
   mov r0, sp
   add sp, sp, #(8*4)

   msr cpsr_c, #(IRQ_MODE | NO_INT)
   mov sp, r0
   ldr r0, [sp, #(7*4)]
   msr spsr_cxsf, r0

   ldmfd sp, {r0-r3, r12, lr}^
   nop
   ldr lr, [sp, #(6*4)]
   movs pc, lr
*/

.set ADDR_SIR_IRQ,        (0x48200000 + 0x40)
.set ADDR_SIR_FIQ,        (0x48200000 + 0x44)
.set ADDR_CONTROL,        (0x48200000 + 0x48)
.set ADDR_THRESHOLD,      (0x48200000 + 0x68)
.set ADDR_IRQ_PRIORITY,   (0x48200000 + 0x60)


   SUB      r14, r14, #4             // Apply lr correction
   STMFD    r13!, {r0-r3, r12, r14}  // Save context in IRQ stack
   MRS      r12, spsr                // Copy spsr
   VMRS     r1,  fpscr               // Copy fpscr
   STMFD    r13!, {r1, r12}          // Save fpscr and spsr
   VSTMDB   r13!, {d0-d7}            // Save D0-D7 NEON/VFP registers

   LDR      r0, =ADDR_THRESHOLD       // Get the IRQ Threshold
   LDR      r1, [r0, #0]
   STMFD    r13!, {r1}               // Save the threshold value

   LDR      r2, =ADDR_IRQ_PRIORITY    // Get the active IRQ priority
   LDR      r3, [r2, #0]
   STR      r3, [r0, #0]             // Set the priority as threshold
   LDR      r1, =ADDR_SIR_IRQ         // Get the Active IRQ
   LDR      r2, [r1]
   AND      r2, r2, #0x7F // Mask the Active IRQ number

   MOV      r0, #0x01           // To enable new IRQ Generation
   LDR      r1, =ADDR_CONTROL

   CMP      r3, #0                   // Check if non-maskable priority 0
   STRNE    r0, [r1]                 // if > 0 priority, acknowledge INTC
   DSB                               // Make sure acknowledgement is completed


   // Enable IRQ and switch to system mode. But IRQ shall be enabled
   // only if priority level is > 0. Note that priority 0 is non maskable.
   // Interrupt Service Routines will execute in System Mode.

   MRS      r14, cpsr                // Read cpsr
   ORR      r14, r14, #SYS_MODE
   BICNE    r14, r14, #0x80         // Enable IRQ if priority > 0
   MSR      cpsr_cxsf, r14

   STMFD    r13!, {r14}              // Save lr_usr
   LDR      r0, =_fnRAMVectors        // Load the base of the vector table
   ADD      r14, pc, #0              // Save return address in LR
   LDR      pc, [r0, r2, lsl #2]     // Jump to the ISR

   LDMFD    r13!, {r14}              // Restore lr_usr

   // Disable IRQ and change back to IRQ mode

   CPSID    i, #IRQ_MODE

   LDR      r0, =ADDR_THRESHOLD       // Get the IRQ Threshold
   LDR      r1, [r0, #0]
   CMP      r1, #0                   // If priority 0
   MOVEQ    r2, #0x01           // Enable new IRQ Generation
   LDREQ    r1, =ADDR_CONTROL
   STREQ    r2, [r1]
   LDMFD    r13!, {r1}
   STR      r1, [r0, #0]             // Restore the threshold value
   VLDMIA   r13!, {d0-d7}            // Restore D0-D7 Neon/VFP registers
   LDMFD    r13!, {r1, r12}          // Get fpscr and spsr
   MSR      spsr_cxsf, r12           // Restore spsr
   VMSR     fpscr, r1                // Restore fpscr
   LDMFD    r13!, {r0-r3, r12, pc}^  // Restore the context and return



/*	ldr r0, =0x48200040
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
	subs pc, lr, #4*/

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



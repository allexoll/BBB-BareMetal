/**
 * @file llma.s
 * @author Alexis Marquet
 * @date 27 Feb 2015
 * @brief contains Low Level Memory Access functions
 **/


.globl PUT32
PUT32:
	str r1,[r0]
	bx lr
	
.globl GET32
GET32:
	ldr r0,[r0]
	bx lr
	
.globl PUT16
PUT16:
	strh r1,[r0]
	bx lr
	
.globl GET16
GET16:
	ldrh r0,[r0]
	bx lr
	
.globl PUT8
PUT8:
	strb r1,[r0]
	bx lr
	
.globl GET8
GET8:
	ldrb r0,[r0]
	bx lr

.globl BRANCHTO
BRANCHTO:
   mov pc, r0
   bx lr //never happens


.globl CPU_irqE
CPU_irqE:
   dsb
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr_c, r0
   DSB
   ISB
   bx lr

.globl CPU_irqD
CPU_irqD:
   dsb
   mrs r0, cpsr
   orr r0, r0, #0x80
   msr cpsr_c, r0
   DSB
   ISB
   bx lr
   
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

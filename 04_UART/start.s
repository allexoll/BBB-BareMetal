
.globl _start
_start:
   mrs r0, cpsr
   bic r0, r0, #0x1F ;@ clear mode bits
   orr r0, r0, #0x13 ;@ set SVC mode
   orr r0, r0, #0xC0 ;@ disable FIQ and IRQ
   msr cpsr, r0

   mrc p15,0,r0,c1,c0,2    ;@ read cp access register
   orr r0,r0,#0x00F00000   ;@ enable full access to neon/vfp (coproc 10&11)
   mcr p15,0,r0,c1,c0,2    ;@ write cp access register
   isb                     ;@ instruction synchronization barrier
   mov r0,#0x40000000      ;@ switch on vfp & neon
   vmsr fpexc,r0           ;@ set EN bit in fpexc

   ldr sp, =0x4030CDFC  ;@6kB public stack  TRM 26.1.3.2

   bl _main


.loop: b .loop


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

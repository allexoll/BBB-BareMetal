/*
 * armDivision.s: Optimized ARM division routines
 *
 * End of the file for licence details.
 *
 * You need to provide the method void __div0(void) in your code
 *  to handle divide by zero.
 *
 */

 /**
 * @file __aeabi.s
 * @author Alexis Marquet
 * @date 28 Apr 2015
 * @brief this file contains implementations for integer division and modulo operations
 **/

.text
.code 32

__div0:
	mov r0,r0
	b __div0


.macro ARM_DIV_BODY dividend, divisor, result, curbit
		clz			\curbit, \divisor
		clz			\result, \dividend
		sub			\result, \curbit, \result
		mov			\curbit, #1
		mov			\divisor, \divisor, lsl \result
		mov			\curbit, \curbit, lsl \result
		mov			\result, #0
1:
		cmp			\dividend, \divisor												@ Division loop
		subhs		\dividend, \dividend, \divisor
		orrhs		\result,   \result,   \curbit
		cmp			\dividend, \divisor,  lsr #1
		subhs		\dividend, \dividend, \divisor, lsr #1
		orrhs		\result,   \result,   \curbit,  lsr #1
		cmp			\dividend, \divisor,  lsr #2
		subhs		\dividend, \dividend, \divisor, lsr #2
		orrhs		\result,   \result,   \curbit,  lsr #2
		cmp			\dividend, \divisor,  lsr #3
		subhs		\dividend, \dividend, \divisor, lsr #3
		orrhs		\result,   \result,   \curbit,  lsr #3
		cmp			\dividend, #0			@ Early termination?
		movnes	\curbit,   \curbit,  lsr #4								@ No, any more bits to do?
		movne		\divisor,  \divisor, lsr #4
		bne			1b
.endm

.macro ARM_DIV2_ORDER divisor, order
		clz			\order, \divisor
		rsb			\order, \order, #31
.endm

.macro ARM_MOD_BODY dividend, divisor, order, spare
		clz			\order, \divisor
		clz			\spare, \dividend
		sub			\order, \order, \spare
		mov			\divisor, \divisor, lsl \order

		@ Perform all needed substractions to keep only the reminder.
		@ Do comparisons in batch of 4 first.
		subs		\order, \order, #3												@ yes, 3 is intended here
		blt			2f
1:
		cmp			\dividend, \divisor
		subhs		\dividend, \dividend, \divisor
		cmp			\dividend, \divisor,  lsr #1
		subhs		\dividend, \dividend, \divisor, lsr #1
		cmp			\dividend, \divisor,  lsr #2
		subhs		\dividend, \dividend, \divisor, lsr #2
		cmp			\dividend, \divisor,  lsr #3
		subhs		\dividend, \dividend, \divisor, lsr #3
		cmp			\dividend, #1
		mov			\divisor, \divisor, lsr #4
		subges	\order, \order, #4
		bge			1b
		tst			\order, #3
		teqne		\dividend, #0
		beq			5f
		@ Either 1, 2 or 3 comparison/substractions are left.
2:
		cmn			\order, #2
		blt			4f
		beq			3f
		cmp			\dividend, \divisor
		subhs		\dividend, \dividend, \divisor
		mov			\divisor,  \divisor,  lsr #1
3:
		cmp			\dividend, \divisor
		subhs		\dividend, \dividend, \divisor
		mov			\divisor,  \divisor,  lsr #1
4:
		cmp			\dividend, \divisor
		subhs		\dividend, \dividend, \divisor
5:
.endm

.align 4,0x90
.globl __udivsi3
.globl __aeabi_uidiv
__udivsi3:
__aeabi_uidiv:
		subs		r2, r1, #1
		moveq		pc, lr
		bcc			Ldiv0
		cmp			r0, r1
		bls			11f
		tst			r1, r2
		beq			12f
		ARM_DIV_BODY r0, r1, r2, r3
		mov			r0, r2
		mov			pc, lr
11:
		moveq		r0, #1
		movne		r0, #0
		mov			pc, lr
12:
		ARM_DIV2_ORDER r1, r2
		mov			r0, r0, lsr r2
		mov			pc, lr

.align 4,0x90
.globl __umodsi3
__umodsi3:
		subs		r2, r1, #1				@ compare divisor with 1
		bcc			Ldiv0
		cmpne		r0, r1						@ compare dividend with divisor
		moveq   r0, #0
		tsthi		r1, r2						@ see if divisor is power of 2
		andeq		r0, r0, r2
		movls		pc, lr
		ARM_MOD_BODY r0, r1, r2, r3
		mov			pc, lr

.align 4,0x90
.globl __divsi3
.globl __aeabi_idiv
__divsi3:
__aeabi_idiv:
		cmp			r1, #0
		eor			ip, r0, r1				@ save the sign of the result.
		beq			Ldiv0
		rsbmi		r1, r1, #0				@ loops below use unsigned.
		subs		r2, r1, #1				@ division by 1 or -1 ?
		beq			10f
		movs		r3, r0
		rsbmi		r3, r0, #0				@ positive dividend value
		cmp			r3, r1
		bls			11f
		tst			r1, r2						@ divisor is power of 2 ?
		beq			12f
		ARM_DIV_BODY r3, r1, r0, r2
		cmp			ip, #0
		rsbmi		r0, r0, #0
		mov			pc, lr
10:
		teq			ip, r0						@ same sign ?
		rsbmi		r0, r0, #0
		mov			pc, lr
11:
		movlo		r0, #0
		moveq		r0, ip, asr #31
		orreq		r0, r0, #1
		mov			pc, lr
12:
		ARM_DIV2_ORDER r1, r2
		cmp			ip, #0
		mov			r0, r3, lsr r2
		rsbmi		r0, r0, #0
		mov			pc, lr

.align 4,0x90
.globl __modsi3
__modsi3:
		cmp			r1, #0
		beq			Ldiv0
		rsbmi		r1, r1, #0				@ loops below use unsigned.
		movs		ip, r0						@ preserve sign of dividend
		rsbmi		r0, r0, #0				@ if negative make positive
		subs		r2, r1, #1				@ compare divisor with 1
		cmpne		r0, r1						@ compare dividend with divisor
		moveq		r0, #0
		tsthi		r1, r2						@ see if divisor is power of 2
		andeq		r0, r0, r2
		bls			10f
		ARM_MOD_BODY r0, r1, r2, r3
10:
		cmp			ip, #0
		rsbmi		r0, r0, #0
		mov			pc, lr

Ldiv0:
		str			lr, [sp, #-8]!
		bl			__div0
		mov			r0, #0
		ldr			pc, [sp], #8


/*
 * Modified July 2012 by Ischus (www.ischus.com), for Raspberry Pi bare metal,
 *
 * to remove dependencies on other files in the Linux distribution.
 * Original is:
 *
 * Author: Nicolas Pitre <nico@fluxnic.net>
 *   - contributed to gcc-3.4 on Sep 30, 2003
 *   - adapted for the Linux kernel on Oct 2, 2003
 * linux/arch/arm/lib/lib1funcs.S: Optimized ARM division routines
 */

/* Copyright 1995, 1996, 1998, 1999, 2000, 2003 Free Software Foundation, Inc.

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file into combinations with other programs,
and to distribute those combinations without any restriction coming
from the use of this file.  (The General Public License restrictions
do apply in other respects; for example, they cover modification of
the file, and distribution when not linked into a combine
executable.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */




/* Runtime ABI for the ARM Cortex-M0  
 * uldivmod.S: unsigned 64 bit division
 *
 * Copyright (c) 2012 Jörg Mische <bobbl@gmx.de>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */





@ unsigned long long __udivdi3(unsigned long long num, unsigned long long denom)
@
@ libgcc wrapper: just an alias for __aeabi_uldivmod(), the remainder is ignored
@
        .global __udivdi3
__udivdi3:



@ {unsigned long long quotient, unsigned long long remainder}
@ __aeabi_uldivmod(unsigned long long numerator, unsigned long long denominator)
@
@ Divide r1:r0 by r3:r2 and return the quotient in r1:r0 and the remainder
@ in r3:r2 (all unsigned)
@
        .global __aeabi_uldivmod
__aeabi_uldivmod:
	
	cmp	r3, #0
	bne	L_large_denom
	cmp	r2, #0
	beq	L_divison_by_0
	cmp	r1, #0
	beq	L_fallback_32bits



	@ case 1: num >= 2^32 and denom < 2^32
	@ Result might be > 2^32, therefore we first calculate the upper 32
	@ bits of the result. It is done similar to the calculation of the
	@ lower 32 bits, but with a denominator that is shifted by 32.
	@ Hence the lower 32 bits of the denominator are always 0 and the
	@ costly 64 bit shift and sub operations can be replaced by cheap 32
	@ bit operations.

	push	{r4, r5, r6, r7, lr}

	@ shift left the denominator until it is greater than the numerator
	@ denom(r7:r6) = r3:r2 << 32

	movs	r5, #1		@ bitmask
	adds	r7, r2, #0	@ dont shift if denominator would overflow
	bmi	L_upper_result
	cmp	r1, r7
	blo	L_upper_result
	
L_denom_shift_loop1:
	lsls	r5, #1
	lsls	r7, #1
	bmi	L_upper_result	@ dont shift if overflow
	cmp	r1, r7
	bhs	L_denom_shift_loop1
	
L_upper_result:
	mov	r3, r1
	mov	r2, r0
	movs	r1, #0		@ upper result = 0

L_sub_loop1:	
	cmp	r3, r7
	bcc	L_dont_sub1	@ if (num>denom)

	subs	r3, r7		@ num -= denom
	orrs	r1, r5		@ result(r7:r6) |= bitmask(r5)
L_dont_sub1:

	lsrs	r7, #1		@ denom(r7:r6) >>= 1
	lsrs	r5, #1		@ bitmask(r5) >>= 1
	bne	L_sub_loop1
	
	movs	r5, #1
	lsls	r5, #31
	movs	r6, #0
	b	L_lower_result



	@ case 2: division by 0
	@ call __aeabi_ldiv0
	
L_divison_by_0:
	b	Ldiv0



	@ case 3: num < 2^32 and denom < 2^32
	@ fallback to 32 bit division

L_fallback_32bits:
	mov	r1, r2
	push	{lr}
	bl	__aeabi_uidiv
	mov	r2, r1
	movs	r1, #0
	movs	r3, #0
	pop	{pc}



	@ case 4: denom >= 2^32
	@ result is smaller than 2^32
	
L_large_denom:
	push	{r4, r5, r6, r7, lr}

	mov	r7, r3
	mov	r6, r2
	mov	r3, r1
	mov	r2, r0

	@ Shift left the denominator until it is greater than the numerator

	movs	r1, #0		@ high word of result is 0
	movs	r5, #1		@ bitmask
	adds	r7, #0		@ dont shift if denominator would overflow
	bmi	L_lower_result
	cmp	r3, r7
	blo	L_lower_result
	
L_denom_shift_loop4:
	lsls	r5, #1
	lsls	r7, #1
	lsls	r6, #1
	adcs	r7, r1		@ r1=0
	bmi	L_lower_result	@ dont shift if overflow
	cmp	r3, r7
	bhs	L_denom_shift_loop4



L_lower_result:
	movs	r0, #0
	
L_sub_loop4:
	mov	r4, r3
	cmp	r2, r6
	sbcs	r4, r7
	bcc	L_dont_sub4	@ if (num>denom)

	subs	r2, r6		@ numerator -= denom
	sbcs	r3, r7
	orrs	r0, r5		@ result(r1:r0) |= bitmask(r5)
L_dont_sub4:

	lsls	r4, r7, #31	@ denom(r7:r6) >>= 1
	lsrs	r6, #1
	lsrs	r7, #1
	orrs	r6, r4
	lsrs	r5, #1		@ bitmask(r5) >>= 1
	bne	L_sub_loop4

	pop	{r4, r5, r6, r7, pc}

.end

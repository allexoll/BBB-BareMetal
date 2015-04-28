/**
 * @file main.c
 * @author Alexis Marquet
 * @date 28 Apr 2015
 * @brief contains the main application
 **/


/**
 * @mainpage
 * 06_stdlib: this example tests stdlib
 **/
#include <stdint.h>
#include "../board/LED.h"
#include "../proc/UART.h"
#include "../core/llma.h"
#include "../proc/clock_module.h"
#include <stdio.h>
#include <stdlib.h>

#define NVIC 0x48200000


/**
 * @fn void RTCINT_IRQHandler(void)
 * @brief               Interrupt service routine for RTC
 **/
void RTCINT_IRQHandler(void)
{
   static int i = 0;
   LED_setValue(++i);
   i &= 0xF;
   PUT32(NVIC+0xD4, 1<< 11);
   if(i == 0xF)
   {
      PUT32(NVIC+0xCC,1<<11);
   }
   printf("i = %X\n",i);
}


int main (void)
{
   printf("newlib testing\n");
   printf("0xDEADBEEF = %X\n",0xDEADBEEF);
   printf("\"test 1 2 3\" = %s\n","test 1 2 3");
   printf("0.0 = %f\n",0.0);
   printf("1.5 = %f\n",1.5);
   printf("-0.0003 = %f\n",-0.0003);
   
   uint32_t* p = (uint32_t *)malloc(200);
   if(p)
   {
      printf("malloc(200) sucessful\n");
   }
   else
   {
      printf("malloc(200) failed!\n");
   }

   
   CKM_setCLKModuleRegister(0x44E00800,0x4,0x2);   // software wakeup on RTC power domain
   CKM_setCLKModuleRegister(0x44E00800,0x0,0x2);   // enable RTC clock power domain

   PUT32(0x44E3E000+0x6C,0x83E70B13);     // disable protection on register
   PUT32(0x44E3E000+0x70,0x95A4F1E0);     // disable protection on register

   PUT32(0x44E3E000+0x40,0x1);      // run RTC

   PUT32(0x44E3E000+0x54,1<<3 | 1<<6); // enable 32khz (bit 6) & select 32 khz osc

   while(GET32(0x44E3E000+0x44)&0x1);  // wait until RTC is done updating

   PUT32(0x44E3E000+0x48,0x4);   // enable interrupt, every second

   PUT32(NVIC+0xC8,1<<11); // enable nvic rtc interrupt

   while(1)
   {
	  asm volatile ("wfi");    // wait for interrupt
   }
   return 0;
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


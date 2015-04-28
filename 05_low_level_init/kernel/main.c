/**
 * @file main.c
 * @author Alexis Marquet
 * @date 28 Apr 2015
 * @brief contains the main application
 **/


/**
 * @mainpage
 * 05_low_level_init: this example changes the structur of the code to be more 
 * modular. Interrupt handlers is now supported. this example prints "rtc irq" 
 * every seconds and the leds count at the same rate.
 **/
#include <stdint.h>
#include "../board/LED.h"
#include "../proc/UART.h"
#include "../core/llma.h"
#include "../proc/clock_module.h"

#define NVIC 0x48200000


/**
 * @fn void RTCINT_IRQHandler(void)
 * @brief               Interrupt service routine for RTC
 **/
void RTCINT_IRQHandler(void)
{
   static int i = 0;
   LED_setValue(i++);
   i &= 0xF;
   PUT32(0x48200000+0xD4, 1<< 11);
   UART_putString(UART0,"rtc irq\n",8);
}


int main (void)
{
   LED_setValue(0x9);
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


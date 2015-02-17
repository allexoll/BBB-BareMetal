//#include "start.h"

#include "GPIO.h"
#include "LED.h"
#include "UART.h"

#define TIME 500000


/**
 * @mainpage   
 * 04_UART: implements the UART0 at 115200N8. This example writes "UART0 Initialized..." ,
 *          and the proceeds to repeat everything received. this is polling-only, no interrupt.
 **/
void _main (void)
{
   LED_init();
   
   UART_initUART(UART0,115200,STOP1,PARITY_NONE,FLOW_OFF);
   UART_putString(UART0,"UART0 Initialized...\n",21);
   while(1)
   {
      UART_putC(UART0,UART_getC(UART0));
   }
   return;
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

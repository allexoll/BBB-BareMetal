/**
 * @file proc_init.c
 * @author Alexis Marquet
 * @date 28 Apr 2015
 * @brief Initialize the processor and its needed peripherals
 **/

#include "../core/llma.h"
#include "../proc/UART.h"

#define NVIC 0x48200000
#define CM_WKUP 0x44E00400
void procInit()
{
   
   /* peripherals */
   PUT32(0x47400000+0x10,1);     // reset USB controller to get the internet connection back
   
   PUT32(NVIC+0x10,1);             // reset INTC controller
   while((GET32(NVIC+0x14)&0x1)==0); // wait until reset is done
   
   PUT32(NVIC+0x68,0xFF);	// disable interrupt threshold
   PUT32(NVIC+0x50,1);  // enable functional clock
   
   PUT32(NVIC+0x94,0xFFFFFFFF);  // clear INTC_ISR_CLEAR0
   PUT32(NVIC+0xB4,0xFFFFFFFF);  // clear INTC_ISR_CLEAR0
   PUT32(NVIC+0xD4,0xFFFFFFFF);  // clear INTC_ISR_CLEAR0
   PUT32(NVIC+0xF4,0xFFFFFFFF);  // clear INTC_ISR_CLEAR0

   CPU_irqE();

   UART_initUART(UART0,115200,STOP1,PARITY_NONE,FLOW_OFF);
   
   UART_putString(UART0,"$UART0 Initialized... compiled at " __TIME__ "\n",43);

   
}
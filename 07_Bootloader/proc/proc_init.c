/**
 * @file proc_init.c
 * @author Alexis Marquet
 * @date 28 Apr 2015
 * @brief Initialize the processor and its needed peripherals
 **/

#include "../core/llma.h"
#include "UART.h"
#include "PLL.h"
#include "EMIF.h"
#include "DDR.h"
#include <stdio.h>

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

   
   uint32_t clkin = GetInputClockFrequency();
   if(clkin==24)
   {
      MPU_PLL_Config (clkin, 23, 500,  1);
      CORE_PLL_Config(clkin, 23, 1000, 10, 8, 4);
      DDR_PLL_Config (clkin, 23, 400,  1);
      PER_PLL_Config (clkin, 23, 960,  5);
      DISP_PLL_Config(clkin, 23, 48,   1);
   }
   else
   {
      printf("error, clkin invalid\n");
      while(1);
   }
   //RAM
   DDR3_EMIF_Config();
   config_ddr_x();// this works
}
/**
 * @file UART.c
 * @author Alexis Marquet
 * @date 04 Dec 2014
 * @brief Implementation concerning UARTs peripherals: TRM 19, Datasheet 4.2
 **/

#include "UART.h"
#include "start.h"
#include "GPIO.h"
#include "pad.h"
#include "control_module.h"
#include "clock_module.h"
#include "types.h"
#include "LED.h"

#define UARTx_OP_R_RHR 			0x0
#define UARTx_OP_R_IER			0x4
#define UARTx_OP_R_IIR			0x8
#define UARTx_OP_R_LCR			0xC
#define UARTx_OP_R_MCR			0x10
#define UARTx_OP_R_LSR			0x14
#define UARTx_OP_R_MSRTCR		0x18
#define UARTx_OP_R_SPRTLR		0x1C
#define UARTx_OP_R_MDR1			0x20
#define UARTx_OP_R_MDR2			0x24
#define UARTx_OP_R_SFLSR		0x28
#define UARTx_OP_R_RESUME		0x2C
#define UARTx_OP_R_SFREGL		0x30
#define UARTx_OP_R_SFREGH		0x34
#define UARTx_OP_R_BLR			0x38
#define UARTx_OP_R_ACREG		0x3C
#define UARTx_OP_R_SCR			0x40
#define UARTx_OP_R_SSR			0x44
#define UARTx_OP_R_EBLR			0x48
#define UARTx_OP_R_MVR			0x50
#define UARTx_OP_R_SYSC			0x54
#define UARTx_OP_R_SYSS			0x58
#define UARTx_OP_R_WER			0x5C
#define UARTx_OP_R_CFPS			0x60
#define UARTx_OP_R_RXFIFO_LVL	0x64
#define UARTx_OP_R_TXFIFO_LVL	0x68
#define UARTx_OP_R_IER2			0x6C
#define UARTx_OP_R_ISR2			0x70
#define UARTx_OP_R_FREQ_SEL	0x74
#define UARTx_OP_R_MDR3			0x80
#define UARTx_OP_R_TXDMA		0x84

#define UARTx_OP_W_THR			0x0
#define UARTx_OP_W_IER			0x4
#define UARTx_OP_W_FCR			0x8
#define UARTx_OP_W_LCR			0xC
#define UARTx_OP_W_MCR			0x10
#define UARTx_OP_W_TCR			0x18
#define UARTx_OP_W_SPRTLR		0x1C
#define UARTx_OP_W_MDR1			0x20
#define UARTx_OP_W_MDR2			0x24
#define UARTx_OP_W_TXFLL		0x28
#define UARTx_OP_W_TXFLH		0x2C
#define UARTx_OP_W_RXFLL		0x30
#define UARTx_OP_W_RXFLH		0x34
#define UARTx_OP_W_BLR			0x38
#define UARTx_OP_W_ACREG		0x3C
#define UARTx_OP_W_SCR			0x40
#define UARTx_OP_W_SSR			0x44
#define UARTx_OP_W_EBLR			0x48
#define UARTx_OP_W_SYSC			0x54
#define UARTx_OP_W_WER			0x5C
#define UARTx_OP_W_CFPS			0x60
#define UARTx_OP_W_RXFIFO_LVL	0x64
#define UARTx_OP_W_TXFIFO_LVL	0x68
#define UARTx_OP_W_IER2			0x6C
#define UARTx_OP_W_ISR2			0x70
#define UARTx_OP_W_FREQ_SEL	0x74
#define UARTx_OP_W_MDR3			0x80
#define UARTx_OP_W_TXDMA		0x84

// uart address map if UARTx_LCR[7:0] != 0xBF  (Configuration Mode A)
#define UARTx_MA_R_DLL			0x0
#define UARTx_MA_R_DLH			0x4
#define UARTx_MA_R_IIR			0x8
#define UARTx_MA_R_LCR			0xC
#define UARTx_MA_R_MCR			0x10
#define UARTx_MA_R_LSR			0x14
#define UARTx_MA_R_MSRTCR		0x18
#define UARTx_MA_R_SPRTLR		0x1C
#define UARTx_MA_R_MDR1			0x20
#define UARTx_MA_R_MDR2			0x24
#define UARTx_MA_R_SFLR			0x28
#define UARTx_MA_R_RESUME		0x2C
#define UARTx_MA_R_SFREGL		0x30
#define UARTx_MA_R_SFREGH		0x34
#define UARTx_MA_R_UASR			0x38
#define UARTx_MA_R_SCR			0x40
#define UARTx_MA_R_SSR			0x44
#define UARTx_MA_R_				0x48
#define UARTx_MA_R_MVR			0x50
#define UARTx_MA_R_SYSC			0x54
#define UARTx_MA_R_SYSS			0x58
#define UARTx_MA_R_WER			0x5C
#define UARTx_MA_R_CFPS			0x60
#define UARTx_MA_R_RXFIFO_LVL	0x64
#define UARTx_MA_R_TXFIFO_LVL	0x68
#define UARTx_MA_R_IER2			0x6C
#define UARTx_MA_R_ISR2			0x70
#define UARTx_MA_R_FREQ_SEL	0x74
#define UARTx_MA_R_MDR3			0x80
#define UARTx_MA_R_TXDMA		0x84

#define UARTx_MA_W_DLL			0x00
#define UARTx_MA_W_DLH			0x04
#define UARTx_MA_W_FCR			0x08
#define UARTx_MA_W_LCR			0x0C
#define UARTx_MA_W_MCR			0x10
#define UARTx_MA_W_TCR			0x18
#define UARTx_MA_W_SPRTLR		0x1C
#define UARTx_MA_W_MDR1			0x20
#define UARTx_MA_W_MDR2			0x24
#define UARTx_MA_W_TXFLL		0x28
#define UARTx_MA_W_TXFLH		0x2C
#define UARTx_MA_W_RXFLL		0x30
#define UARTx_MA_W_RXFLH		0x34
#define UARTx_MA_W_SCR			0x40
#define UARTx_MA_W_SSR			0x44
#define UARTx_MA_W_SYSC			0x54
#define UARTx_MA_W_WER			0x5C
#define UARTx_MA_W_CFPS			0x60
#define UARTx_MA_W_RXFIFO_LVL	0x64
#define UARTx_MA_W_TXFIFO_LVL	0x68
#define UARTx_MA_W_IER2			0x6C
#define UARTx_MA_W_ISR2			0x70
#define UARTx_MA_W_FREQ_SEL	0x74
#define UARTx_MA_W_MDR3			0x80
#define UARTx_MA_W_TXDMA		0x84

// uart address map if UARTx_LCR[7:0] == 0xBF  (Configuration Mode B)
#define UARTx_MB_R_DLL			0x00
#define UARTx_MB_R_DLH			0x04
#define UARTx_MB_R_EFR			0x08
#define UARTx_MB_R_LCR			0x0C
#define UARTx_MB_R_XON1ADDR2	0x10
#define UARTx_MB_R_XON2ADDR2	0x14
#define UARTx_MB_R_XOFF1TCR	0x18
#define UARTx_MB_R_XOFF2TLR	0x1C
#define UARTx_MB_R_MDR1			0x20
#define UARTx_MB_R_MDR2			0x24
#define UARTx_MB_R_SFLSR		0x28
#define UARTx_MB_R_RESUME		0x2C
#define UARTx_MB_R_SFREGL		0x30
#define UARTx_MB_R_SFREGH		0x34
#define UARTx_MB_R_UASR			0x38
#define UARTx_MB_R_SCR			0x40
#define UARTx_MB_R_SSR			0x44
#define UARTx_MB_R_MVR			0x50
#define UARTx_MB_R_SYSC			0x54
#define UARTx_MB_R_SYSS			0x58
#define UARTx_MB_R_WER			0x5C
#define UARTx_MB_R_CFPS			0x60
#define UARTx_MB_R_RXFIFO_LVL	0x64
#define UARTx_MB_R_TXFIFO_LVL	0x68
#define UARTx_MB_R_IER2			0x6C
#define UARTx_MB_R_ISR2			0x70
#define UARTx_MB_R_FREQ_SEL	0x74
#define UARTx_MB_R_MDR3			0x80
#define UARTx_MB_R_TXDMA		0x84


#define UARTx_MB_W_DLL			0x00
#define UARTx_MB_W_DLH			0x04
#define UARTx_MB_W_EFR			0x08
#define UARTx_MB_W_LCR			0x0C
#define UARTx_MB_W_XON1ADDR1	0x10
#define UARTx_MB_W_XON2ADDR2	0x14
#define UARTx_MB_W_XOFF1TCR	0x18
#define UARTx_MB_W_XOFF2TLR	0x1C
#define UARTx_MB_W_MDR1			0x20
#define UARTx_MB_W_MDR2			0x24
#define UARTx_MB_W_SFLSR		0x28
#define UARTx_MB_W_RESUME		0x2C
#define UARTx_MB_W_SFREGL		0x30
#define UARTx_MB_W_SFREGH		0x34
#define UARTx_MB_W_UASR			0x38
#define UARTx_MB_W_SCR			0x40
#define UARTx_MB_W_SSR			0x44
#define UARTx_MB_W_MVR			0x50
#define UARTx_MB_W_SYSC			0x54
#define UARTx_MB_W_SYSS			0x58
#define UARTx_MB_W_WER			0x5C
#define UARTx_MB_W_CFPS			0x60
#define UARTx_MB_W_RXFIFO_LVL	0x64
#define UARTx_MB_W_TXFIFO_LVL	0x68
#define UARTx_MB_W_IER2			0x6C
#define UARTx_MB_W_ISR2			0x70
#define UARTx_MB_W_FREQ_SEL	0x74
#define UARTx_MB_W_MDR3			0x80
#define UARTx_MB_W_TXDMA		0x84


static const unsigned int UART_ARRAY_BASE[] = {0x44E09000, 0x48022000, 0x48024000, 0x481A6000, 0x481A8000, 0x481AA000};

static bool UART_checkValidUart(UART_t uart)
{
   if((uart < UART0) || (uart > UART5))
   {
      // TODO: raise error (Uart number is either too big or negative: /uart)
      return false;
   }
   return true;
}
void UART_initUART(UART_t uart, unsigned int baudrate, STOP_BIT_t stopBit, PARITY_BIT_t parity, FLOW_t flowControl)
{
   if(UART_checkValidUart(uart))
   {
      unsigned int uart_base = UART_ARRAY_BASE[uart];
      switch(uart)
      {
         case UART0: // tx=1.11  rx=1.10  cts=1.8  rts=1.9
            
            GPIO_initPort(GPIO1);
            CM_setCtrlModule(CM_conf_uart0_txd,0); // do nothing on UART0_tx
            CM_setCtrlModule(CM_conf_uart0_rxd,(1<<4)|(1<<5)); // set pullup/pulldown & receiver enabled on UART0_rx
            PAD_setMode(CM_conf_uart0_txd,MODE_0); // set p1.11 as UART0_tx
            PAD_setMode(CM_conf_uart0_rxd,MODE_0); // set p1.10 as UART0_rx
            
            unsigned int temp = CKM_getCLKModuleRegister(CKM_WKUP,CKM_WKUP_CLKSTCTRL);
            temp &= ~(0b11);
            temp |= 0b10;      // software-forced wake-up transition on the "always on clock domain", TRM Table 8-92
            CKM_setCLKModuleRegister(CKM_WKUP,CKM_WKUP_CLKSTCTRL,temp);
            
            temp = CKM_getCLKModuleRegister(CKM_PER,CKM_PER_L4HS_CLKSTCTRL);
            temp &= ~(0b11);
            temp |= 0b10;      // software-forced wake up transition on the L4 high speed domain
                   CKM_setCLKModuleRegister(CKM_PER,CKM_PER_L4HS_CLKSTCTRL,temp);

            temp = CKM_getCLKModuleRegister(CKM_WKUP,CKM_WKUP_UART0_CLKCTRL);
            temp &= ~(0b11);
            temp |= 0b10;      // Module is explicitly enabled,    TRM Table 8-137
                   CKM_setCLKModuleRegister(CKM_WKUP,CKM_WKUP_UART0_CLKCTRL,temp);
            while((CKM_getCLKModuleRegister(CKM_WKUP, CKM_WKUP_UART0_CLKCTRL) & (0b11<<16)) != 0); // wait until clock transition is complete
            
            // TODO: verifiy it next block is needed for uart0
            // warning, why would the UART1 registers need modification when configuring UART0?
            temp = CKM_getCLKModuleRegister(CKM_PER,CKM_PER_UART1_CLKCTRL);
            temp &= ~(0b11);
            temp |= 0b10;      // Module is explicitly enabled,    TRM Table 8-137
                   CKM_setCLKModuleRegister(CKM_PER,CKM_PER_UART1_CLKCTRL,temp);
            
            temp = GET32(uart_base+0x54);    // SYSC
            temp |= 0x2;      // uart module reset
            PUT32(uart_base+0x54,temp);
            
            while((GET32(uart_base+0x58)&1)==0);   // wait for reset to be complete
            
            temp = GET8(uart_base+0x54);
            temp |= (0x1<<3); // no idle
            PUT8(uart_base+0x54,temp);
            
            while(((GET32(uart_base+0x14)&0x40)!=0x40));    // wait for txfifo to be empty
            
            
            float div = 48000000.0/(16.0*(float)baudrate);
            unsigned int intdiv = (unsigned int) div;
            PUT8(uart_base+0x04,0);
            PUT8(uart_base+0x20,0x7);        // Disable modeselect (default) TRM table 19-50
            PUT8(uart_base+0x0C,~(0x7C));    // divisor latch enable, access DLL DHL, set uart as 8bit
            PUT8(uart_base+0x00,0);          // DLL = 0
            PUT8(uart_base+0x04,0);          // DHL = 0
            PUT8(uart_base+0x0C,0x3);        // set uart as 8bit
            PUT8(uart_base+0x10,0x3);        // force /rts & /drt to active (low) (?!)
            PUT8(uart_base+0x08,0x7);        // clear rx&tx FIFOs, and enables them (each 64 bytes deep)
            PUT8(uart_base+0x0C,~(0x7C));    // divisor latch enable, access DLL DHL, set uart as 8bit
            PUT8(uart_base+0x00,intdiv&0xFF);          // DLL = 0
            PUT8(uart_base+0x04,(intdiv>>8)&0x3F);          // DHL = 0

//            PUT8(uart_base+0x00,26);         // DLL/DHL value for 115200
            PUT8(uart_base+0x0C,0x3);        // set uart as 8 bit
            PUT8(uart_base+0x20,0);          // uart 16x oversampling
            
            break;
         // TODO: implement UART1-5
         case UART1:
            break;
         case UART2:
            break;
         case UART3:
            break;
         case UART4:
            break;
         case UART5:
            break;
      }
   }
}

void UART_putC(UART_t uart, char c)
{
   unsigned int uart_base = UART_ARRAY_BASE[uart];
   while((GET8(uart_base+0x14)&0x20)!=0x20);   //wait until txfifo is empty
    
   PUT8(uart_base +0,c);
}

char UART_getC(UART_t uart)
{
   unsigned int uart_base = UART_ARRAY_BASE[uart];
   while((GET8(uart_base+0x14)&0x1)==0);     //wait for a character to be in the rx fifo
   return GET8(uart_base+0x0);
}

int UART_putString(UART_t uart, char *str, unsigned int length)
{
   for(int i = 0; i < length; i++)
   {
      UART_putC(uart,str[i]);
   }
   return length;
}

int UART_getString(UART_t uart, char *buf, unsigned int length)
{
   for(int i = 0; i < length; i ++)
   {
      buf[i] = UART_getC(uart);
   }
   return length;
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

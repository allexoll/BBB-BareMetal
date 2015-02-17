/**
 * @file clock_module.h
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief File containing types & function prototypes concerning clock module usage: TRM 8
 **/
#ifndef __clock_module_H
#define __clock_module_H

/**
 * @brief Clock Modules Power Enable Registers & their coresponding offsets: TRM 8.1.12
 **/
typedef enum
{
   CKM_PER_L4LS_CLKSTCTRL      = 0x000,
   CKM_PER_L3S_CLKSTCTRL       = 0x004,
   CKM_PER_L4FW_CLKSTCTRL      = 0x008,
   CKM_PER_L3_CLKSTCTRL        = 0x00C,
   CKM_PER_CPGMAC0_CLKCTRL     = 0x014,
   CKM_PER_LCDC_CLKCTRL        = 0x018,
   CKM_PER_USB0_CLKCTRL        = 0x01C,
   CKM_PER_TPTC0_CLKCTRL       = 0x024,
   CKM_PER_EMIF_CLKCTRL        = 0x028,
   CKM_PER_OCMCRAM_CLKCTRL     = 0x02C,
   CKM_PER_GPMC_CLKCTRL        = 0x030,
   CKM_PER_MCASP0_CLKCTRL      = 0x034,
   CKM_PER_UART5_CLKCTRL       = 0x038,
   CKM_PER_MMC0_CLKCTRL        = 0x03C,
   CKM_PER_ELM_CLKCTRL         = 0x040,
   CKM_PER_I2C2_CLKCTRL        = 0x044,
   CKM_PER_I2C1_CLKCTRL        = 0x048,
   CKM_PER_SPI0_CLKCTRL        = 0x04C,
   CKM_PER_SPI1_CLKCTRL        = 0x050,
   CKM_PER_L4LS_CLKCTRL        = 0x060,
   CKM_PER_L4FW_CLKCTRL        = 0x064,
   CKM_PER_MCASP1_CLKCTRL      = 0x068,
   CKM_PER_UART1_CLKCTRL       = 0x06C,
   CKM_PER_UART2_CLKCTRL       = 0x070,
   CKM_PER_UART3_CLKCTRL       = 0x074,
   CKM_PER_UART4_CLKCTRL       = 0x078,
   CKM_PER_TIMER7_CLKCTRL      = 0x07C,
   CKM_PER_TIMER2_CLKCTRL      = 0x080,
   CKM_PER_TIMER3_CLKCTRL      = 0x084,
   CKM_PER_TIMER4_CLKCTRL      = 0x088,
   CKM_PER_GPIO1_CLKCTRL       = 0x0AC,
   CKM_PER_GPIO2_CLKCTRL       = 0x0B0,
   CKM_PER_GPIO3_CLKCTRL       = 0x0B4,
   CKM_PER_TPCC_CLKCTRL        = 0x0BC,
   CKM_PER_DCAN0_CLKCTRL       = 0x0C0,
   CKM_PER_DCAN1_CLKCTRL       = 0x0C4,
   CKM_PER_EPWMSS1_CLKCTRL     = 0x0CC,
   CKM_PER_EMIF_FW_CLKCTRL     = 0x0D0,
   CKM_PER_EPWMSS0_CLKCTRL     = 0x0D4,
   CKM_PER_EPWMSS2_CLKCTRL     = 0x0D8,
   CKM_PER_L3_INSTR_CLKCTRL    = 0x0DC,
   CKM_PER_L3_CLKCTRL          = 0x0E0,
   CKM_PER_IEEE5000_CLKCTRL    = 0x0E4,
   CKM_PER_PRU_ICSS_CLKCTRL    = 0x0E8,
   CKM_PER_TIMER5_CLKCTRL      = 0x0EC,
   CKM_PER_TIMER6_CLKCTRL      = 0x0F0,
   CKM_PER_MMC1_CLKCTRL        = 0x0F4,
   CKM_PER_MMC2_CLKCTRL        = 0x0F8,
   CKM_PER_TPTC1_CLKCTRL       = 0x0FC,
   CKM_PER_TPTC2_CLKCTRL       = 0x100,
   CKM_PER_SPINLOCK_CLKCTRL    = 0x10C,
   CKM_PER_MAILBOX0_CLKCTRL    = 0x110,
   CKM_PER_L4HS_CLKSTCTRL      = 0x11C,
   CKM_PER_L4HS_CLKCTRL        = 0x120,
   CKM_PER_OCPWP_L3_CLKSTCTRL  = 0x12C,
   CKM_PER_OCPWP_CLKCTRL       = 0x130,
   CKM_PER_PRU_ICSS_CLKSTCTRL  = 0x140,
   CKM_PER_CPSW_CLKSTCTRL      = 0x144,
   CKM_PER_LCDC_CLKSTCTRL      = 0x148,
   CKM_PER_CLKDIV32K_CLKCTRL   = 0x14C,
   CKM_PER_CLK_24MHZ_CLKSTCTRL = 0x150,
}CKM_MODULE_REG;

/**
 * @fn void CKM_setCLKModuleRegister(CKM_MODULE_REG module, unsigned int value)
 * @brief               Set the clock module to a certain value.
 * @param[in]  module   Module to set value.
 * @param[in]  value    Value to set module to.
 * @return              void
 **/
void CKM_setCLKModuleRegister(CKM_MODULE_REG module, unsigned int value);


/**
 * @fn unsigned int CKM_getCLKModuleRegister(CKM_MODULE_REG module)
 * @brief               Get the clock module value.
 * @param[in]  module   Module to get the value from.
 * @return              value of the clock module.
 **/
unsigned int CKM_getCLKModuleRegister(CKM_MODULE_REG module);

#endif /* defined(__clock_module__H) */


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

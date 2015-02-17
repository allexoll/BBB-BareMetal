/**
 * @file clock_module.h
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief Types & function prototypes concerning clock module usage: TRM 8
 **/
#ifndef __clock_module_H
#define __clock_module_H

/**
 * @brief Clock Modules Registers & their coresponding offsets from their chapter/domain/memory zone: TRM 8.1.12
 **/
typedef enum
{
   // CKM_PER zone
   CKM_PER_L4LS_CLKSTCTRL        = 0x000,
   CKM_PER_L3S_CLKSTCTRL         = 0x004,
   CKM_PER_L4FW_CLKSTCTRL        = 0x008,
   CKM_PER_L3_CLKSTCTRL          = 0x00C,
   CKM_PER_CPGMAC0_CLKCTRL       = 0x014,
   CKM_PER_LCDC_CLKCTRL          = 0x018,
   CKM_PER_USB0_CLKCTRL          = 0x01C,
   CKM_PER_TPTC0_CLKCTRL         = 0x024,
   CKM_PER_EMIF_CLKCTRL          = 0x028,
   CKM_PER_OCMCRAM_CLKCTRL       = 0x02C,
   CKM_PER_GPMC_CLKCTRL          = 0x030,
   CKM_PER_MCASP0_CLKCTRL        = 0x034,
   CKM_PER_UART5_CLKCTRL         = 0x038,
   CKM_PER_MMC0_CLKCTRL          = 0x03C,
   CKM_PER_ELM_CLKCTRL           = 0x040,
   CKM_PER_I2C2_CLKCTRL          = 0x044,
   CKM_PER_I2C1_CLKCTRL          = 0x048,
   CKM_PER_SPI0_CLKCTRL          = 0x04C,
   CKM_PER_SPI1_CLKCTRL          = 0x050,
   CKM_PER_L4LS_CLKCTRL          = 0x060,
   CKM_PER_L4FW_CLKCTRL          = 0x064,
   CKM_PER_MCASP1_CLKCTRL        = 0x068,
   CKM_PER_UART1_CLKCTRL         = 0x06C,
   CKM_PER_UART2_CLKCTRL         = 0x070,
   CKM_PER_UART3_CLKCTRL         = 0x074,
   CKM_PER_UART4_CLKCTRL         = 0x078,
   CKM_PER_TIMER7_CLKCTRL        = 0x07C,
   CKM_PER_TIMER2_CLKCTRL        = 0x080,
   CKM_PER_TIMER3_CLKCTRL        = 0x084,
   CKM_PER_TIMER4_CLKCTRL        = 0x088,
   CKM_PER_GPIO1_CLKCTRL         = 0x0AC,
   CKM_PER_GPIO2_CLKCTRL         = 0x0B0,
   CKM_PER_GPIO3_CLKCTRL         = 0x0B4,
   CKM_PER_TPCC_CLKCTRL          = 0x0BC,
   CKM_PER_DCAN0_CLKCTRL         = 0x0C0,
   CKM_PER_DCAN1_CLKCTRL         = 0x0C4,
   CKM_PER_EPWMSS1_CLKCTRL       = 0x0CC,
   CKM_PER_EMIF_FW_CLKCTRL       = 0x0D0,
   CKM_PER_EPWMSS0_CLKCTRL       = 0x0D4,
   CKM_PER_EPWMSS2_CLKCTRL       = 0x0D8,
   CKM_PER_L3_INSTR_CLKCTRL      = 0x0DC,
   CKM_PER_L3_CLKCTRL            = 0x0E0,
   CKM_PER_IEEE5000_CLKCTRL      = 0x0E4,
   CKM_PER_PRU_ICSS_CLKCTRL      = 0x0E8,
   CKM_PER_TIMER5_CLKCTRL        = 0x0EC,
   CKM_PER_TIMER6_CLKCTRL        = 0x0F0,
   CKM_PER_MMC1_CLKCTRL          = 0x0F4,
   CKM_PER_MMC2_CLKCTRL          = 0x0F8,
   CKM_PER_TPTC1_CLKCTRL         = 0x0FC,
   CKM_PER_TPTC2_CLKCTRL         = 0x100,
   CKM_PER_SPINLOCK_CLKCTRL      = 0x10C,
   CKM_PER_MAILBOX0_CLKCTRL      = 0x110,
   CKM_PER_L4HS_CLKSTCTRL        = 0x11C,
   CKM_PER_L4HS_CLKCTRL          = 0x120,
   CKM_PER_OCPWP_L3_CLKSTCTRL    = 0x12C,
   CKM_PER_OCPWP_CLKCTRL         = 0x130,
   CKM_PER_PRU_ICSS_CLKSTCTRL    = 0x140,
   CKM_PER_CPSW_CLKSTCTRL        = 0x144,
   CKM_PER_LCDC_CLKSTCTRL        = 0x148,
   CKM_PER_CLKDIV32K_CLKCTRL     = 0x14C,
   CKM_PER_CLK_24MHZ_CLKSTCTRL   = 0x150,
   
   // CKM_WKUP zone
   CKM_WKUP_CLKSTCTRL            = 0x00,
   CKM_WKUP_CONTROL_CLKCTRL      = 0x04,
   CKM_WKUP_GPIO0_CLKCTRL        = 0x08,
   CKM_WKUP_L4WKUP_CLKCTRL       = 0x0C,
   CKM_WKUP_TIMER0_CLKCTRL       = 0x10,
   CKM_WKUP_DEBUGSS_CLKCTRL      = 0x14,
   CKM_L3_AON_CLKSTCTRL          = 0x18,
   CKM_AUTOIDLE_DPLL_MPU         = 0x1C,
   CKM_IDLEST_DPLL_MPU           = 0x20,
   CKM_SSC_DELTAMSTEP_DPLL_MPU   = 0x24,
   CKM_SSC_MODFREQDIV_DPLL_MPU   = 0x28,
   CKM_CLKSEL_DPLL_MPU           = 0x2C,
   CKM_AUTOIDLE_DPLL_DDR         = 0x30,
   CKM_IDLEST_DPLL_DDR           = 0x34,
   CKM_SSC_DELTAMSTEP_DPLL_DDR   = 0x38,
   CKM_SSC_MODFREQDIV_DPLL_DDR   = 0x3C,
   CKM_CLKSEL_DPLL_DDR           = 0x40,
   CKM_AUTOIDLE_DPLL_DISP        = 0x44,
   CKM_IDLEST_DPLL_DISP          = 0x48,
   CKM_SSC_DELTAMSTEP_DPLL_DISP  = 0x4C,
   CKM_SSC_MODFREQDIV_DPLL_DISP  = 0x50,
   CKM_CLKSEL_DPLL_DISP          = 0x54,
   CKM_AUTOIDLE_DPLL_CORE        = 0x58,
   CKM_IDLEST_DPLL_CORE          = 0x5C,
   CKM_SSC_DELTAMSTEP_DPLL_CORE  = 0x60,
   CKM_SSC_MODFREQDIV_DPLL_CORE  = 0x64,
   CKM_CLKSEL_DPLL_CORE          = 0x68,
   CKM_AUTOIDLE_DPLL_PER         = 0x6C,
   CKM_IDLEST_DPLL_PER           = 0x70,
   CKM_SSC_DELTAMSTEP_DPLL_PER   = 0x74,
   CKM_SSC_MODFREQDIV_DPLL_PER   = 0x78,
   CKM_CLKDCOLDO_DPLL_PER        = 0x7C,
   CKM_DIV_M4_DPLL_CORE          = 0x80,
   CKM_DIV_M5_DPLL_CORE          = 0x84,
   CKM_CLKMODE_DPLL_MPU          = 0x88,
   CKM_CLKMODE_DPLL_PER          = 0x8C,
   CKM_CLKMODE_DPLL_CORE         = 0x90,
   CKM_CLKMODE_DPLL_DDR          = 0x94,
   CKM_CLKMODE_DPLL_DISP         = 0x98,
   CKM_CLKSEL_DPLL_PERIPH        = 0x9C,
   CKM_DIV_M2_DPLL_DDR           = 0xA0,
   CKM_DIV_M2_DPLL_DISP          = 0xA4,
   CKM_DIV_M2_DPLL_MPU           = 0xA8,
   CKM_DIV_M2_DPLL_PER           = 0xAC,
   CKM_WKUP_WKUP_M3_CLKCTRL      = 0xB0,
   CKM_WKUP_UART0_CLKCTRL        = 0xB4,
   CKM_WKUP_I2C0_CLKCTRL         = 0xB8,
   CKM_WKUP_ADC_TSC_CLKCTRL      = 0xBC,
   CKM_WKUP_SMARTREFLEX0_CLKCTRL = 0xC0,
   CKM_WKUP_TIMER1_CLKCTRL       = 0xC4,
   CKM_WKUP_SMARTREFLEX1_CLKCTRL = 0xC8,
   CKM_L4_WKUP_AON_CLKSTCTRL     = 0xCC,
   CKM_WKUP_WDT1_CLKCTRL         = 0xD4,
   CKM_DIV_M6_DPLL_CORE          = 0xD8
}CKM_MODULE_REG;


/**
 * @brief Clock Modules Domaines bases: TRM 2.1
 **/
typedef enum
{
   CKM_PER     = 0x44E00000,
   CKM_WKUP    = 0x44E00400,
   CKM_DPLL    = 0x44E00500,
   CKM_MPU     = 0x44E00600,
   CKM_DEVICE  = 0x44E00700,
   CKM_RTC     = 0x44E00800,
   CKM_GFX     = 0X44E00900,
   CKM_CEFUSE  = 0X44E00A00
}CLK_MODULE_t;

/**
 * @fn void CKM_setCLKModuleRegister(CLK_MODULE_t module, CKM_MODULE_REG reg, unsigned int value)
 * @brief               Set the clock register to a certain value.
 * @param[in]  module   Parent module of register
 * @param[in]  reg      Register to set value.
 * @param[in]  value    Value to set register to.
 * @return              void
 **/
void CKM_setCLKModuleRegister(CLK_MODULE_t module, CKM_MODULE_REG reg, unsigned int value);


/**
 * @fn unsigned int CKM_getCLKModuleRegister(CLK_MODULE_t module, CKM_MODULE_REG reg)
 * @brief               Get the clock register value.
 * @param[in]  module   Parent module of register
 * @param[in]  reg      Register to get the value from.
 * @return              value of the clock register.
 **/
unsigned int CKM_getCLKModuleRegister(CLK_MODULE_t module, CKM_MODULE_REG reg);

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


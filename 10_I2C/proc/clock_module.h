/**
 * @file clock_module.h
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief Types & function prototypes concerning clock module usage: TRM 8
 **/
#ifndef __clock_module_H
#define __clock_module_H


/**
 * @brief Clock Modules Registers & their coresponding offsets from their domainx: TRM 8.1.12
 **/
typedef enum
{
   // CLKM_PER zone
   CLKM_PER_L4LS_CLKSTCTRL        = 0x000,
   CLKM_PER_L3S_CLKSTCTRL         = 0x004,
   CLKM_PER_L4FW_CLKSTCTRL        = 0x008,
   CLKM_PER_L3_CLKSTCTRL          = 0x00C,
   CLKM_PER_CPGMAC0_CLKCTRL       = 0x014,
   CLKM_PER_LCDC_CLKCTRL          = 0x018,
   CLKM_PER_USB0_CLKCTRL          = 0x01C,
   CLKM_PER_TPTC0_CLKCTRL         = 0x024,
   CLKM_PER_EMIF_CLKCTRL          = 0x028,
   CLKM_PER_OCMCRAM_CLKCTRL       = 0x02C,
   CLKM_PER_GPMC_CLKCTRL          = 0x030,
   CLKM_PER_MCASP0_CLKCTRL        = 0x034,
   CLKM_PER_UART5_CLKCTRL         = 0x038,
   CLKM_PER_MMC0_CLKCTRL          = 0x03C,
   CLKM_PER_ELM_CLKCTRL           = 0x040,
   CLKM_PER_I2C2_CLKCTRL          = 0x044,
   CLKM_PER_I2C1_CLKCTRL          = 0x048,
   CLKM_PER_SPI0_CLKCTRL          = 0x04C,
   CLKM_PER_SPI1_CLKCTRL          = 0x050,
   CLKM_PER_L4LS_CLKCTRL          = 0x060,
   CLKM_PER_L4FW_CLKCTRL          = 0x064,
   CLKM_PER_MCASP1_CLKCTRL        = 0x068,
   CLKM_PER_UART1_CLKCTRL         = 0x06C,
   CLKM_PER_UART2_CLKCTRL         = 0x070,
   CLKM_PER_UART3_CLKCTRL         = 0x074,
   CLKM_PER_UART4_CLKCTRL         = 0x078,
   CLKM_PER_TIMER7_CLKCTRL        = 0x07C,
   CLKM_PER_TIMER2_CLKCTRL        = 0x080,
   CLKM_PER_TIMER3_CLKCTRL        = 0x084,
   CLKM_PER_TIMER4_CLKCTRL        = 0x088,
   CLKM_PER_GPIO1_CLKCTRL         = 0x0AC,
   CLKM_PER_GPIO2_CLKCTRL         = 0x0B0,
   CLKM_PER_GPIO3_CLKCTRL         = 0x0B4,
   CLKM_PER_TPCC_CLKCTRL          = 0x0BC,
   CLKM_PER_DCAN0_CLKCTRL         = 0x0C0,
   CLKM_PER_DCAN1_CLKCTRL         = 0x0C4,
   CLKM_PER_EPWMSS1_CLKCTRL       = 0x0CC,
   CLKM_PER_EMIF_FW_CLKCTRL       = 0x0D0,
   CLKM_PER_EPWMSS0_CLKCTRL       = 0x0D4,
   CLKM_PER_EPWMSS2_CLKCTRL       = 0x0D8,
   CLKM_PER_L3_INSTR_CLKCTRL      = 0x0DC,
   CLKM_PER_L3_CLKCTRL            = 0x0E0,
   CLKM_PER_IEEE5000_CLKCTRL      = 0x0E4,
   CLKM_PER_PRU_ICSS_CLKCTRL      = 0x0E8,
   CLKM_PER_TIMER5_CLKCTRL        = 0x0EC,
   CLKM_PER_TIMER6_CLKCTRL        = 0x0F0,
   CLKM_PER_MMC1_CLKCTRL          = 0x0F4,
   CLKM_PER_MMC2_CLKCTRL          = 0x0F8,
   CLKM_PER_TPTC1_CLKCTRL         = 0x0FC,
   CLKM_PER_TPTC2_CLKCTRL         = 0x100,
   CLKM_PER_SPINLOCK_CLKCTRL      = 0x10C,
   CLKM_PER_MAILBOX0_CLKCTRL      = 0x110,
   CLKM_PER_L4HS_CLKSTCTRL        = 0x11C,
   CLKM_PER_L4HS_CLKCTRL          = 0x120,
   CLKM_PER_OCPWP_L3_CLKSTCTRL    = 0x12C,
   CLKM_PER_OCPWP_CLKCTRL         = 0x130,
   CLKM_PER_PRU_ICSS_CLKSTCTRL    = 0x140,
   CLKM_PER_CPSW_CLKSTCTRL        = 0x144,
   CLKM_PER_LCDC_CLKSTCTRL        = 0x148,
   CLKM_PER_CLKDIV32K_CLKCTRL     = 0x14C,
   CLKM_PER_CLK_24MHZ_CLKSTCTRL   = 0x150,
   
   // CLKM_WKUP zone
   CLKM_WKUP_CLKSTCTRL            = 0x00,
   CLKM_WKUP_CONTROL_CLKCTRL      = 0x04,
   CLKM_WKUP_GPIO0_CLKCTRL        = 0x08,
   CLKM_WKUP_L4WKUP_CLKCTRL       = 0x0C,
   CLKM_WKUP_TIMER0_CLKCTRL       = 0x10,
   CLKM_WKUP_DEBUGSS_CLKCTRL      = 0x14,
   CLKM_L3_AON_CLKSTCTRL          = 0x18,
   CLKM_AUTOIDLE_DPLL_MPU         = 0x1C,
   CLKM_IDLEST_DPLL_MPU           = 0x20,
   CLKM_SSC_DELTAMSTEP_DPLL_MPU   = 0x24,
   CLKM_SSC_MODFREQDIV_DPLL_MPU   = 0x28,
   CLKM_CLKSEL_DPLL_MPU           = 0x2C,
   CLKM_AUTOIDLE_DPLL_DDR         = 0x30,
   CLKM_IDLEST_DPLL_DDR           = 0x34,
   CLKM_SSC_DELTAMSTEP_DPLL_DDR   = 0x38,
   CLKM_SSC_MODFREQDIV_DPLL_DDR   = 0x3C,
   CLKM_CLKSEL_DPLL_DDR           = 0x40,
   CLKM_AUTOIDLE_DPLL_DISP        = 0x44,
   CLKM_IDLEST_DPLL_DISP          = 0x48,
   CLKM_SSC_DELTAMSTEP_DPLL_DISP  = 0x4C,
   CLKM_SSC_MODFREQDIV_DPLL_DISP  = 0x50,
   CLKM_CLKSEL_DPLL_DISP          = 0x54,
   CLKM_AUTOIDLE_DPLL_CORE        = 0x58,
   CLKM_IDLEST_DPLL_CORE          = 0x5C,
   CLKM_SSC_DELTAMSTEP_DPLL_CORE  = 0x60,
   CLKM_SSC_MODFREQDIV_DPLL_CORE  = 0x64,
   CLKM_CLKSEL_DPLL_CORE          = 0x68,
   CLKM_AUTOIDLE_DPLL_PER         = 0x6C,
   CLKM_IDLEST_DPLL_PER           = 0x70,
   CLKM_SSC_DELTAMSTEP_DPLL_PER   = 0x74,
   CLKM_SSC_MODFREQDIV_DPLL_PER   = 0x78,
   CLKM_CLKDCOLDO_DPLL_PER        = 0x7C,
   CLKM_DIV_M4_DPLL_CORE          = 0x80,
   CLKM_DIV_M5_DPLL_CORE          = 0x84,
   CLKM_CLKMODE_DPLL_MPU          = 0x88,
   CLKM_CLKMODE_DPLL_PER          = 0x8C,
   CLKM_CLKMODE_DPLL_CORE         = 0x90,
   CLKM_CLKMODE_DPLL_DDR          = 0x94,
   CLKM_CLKMODE_DPLL_DISP         = 0x98,
   CLKM_CLKSEL_DPLL_PERIPH        = 0x9C,
   CLKM_DIV_M2_DPLL_DDR           = 0xA0,
   CLKM_DIV_M2_DPLL_DISP          = 0xA4,
   CLKM_DIV_M2_DPLL_MPU           = 0xA8,
   CLKM_DIV_M2_DPLL_PER           = 0xAC,
   CLKM_WKUP_WKUP_M3_CLKCTRL      = 0xB0,
   CLKM_WKUP_UART0_CLKCTRL        = 0xB4,
   CLKM_WKUP_I2C0_CLKCTRL         = 0xB8,
   CLKM_WKUP_ADC_TSC_CLKCTRL      = 0xBC,
   CLKM_WKUP_SMARTREFLEX0_CLKCTRL = 0xC0,
   CLKM_WKUP_TIMER1_CLKCTRL       = 0xC4,
   CLKM_WKUP_SMARTREFLEX1_CLKCTRL = 0xC8,
   CLKM_L4_WKUP_AON_CLKSTCTRL     = 0xCC,
   CLKM_WKUP_WDT1_CLKCTRL         = 0xD4,
   CLKM_DIV_M6_DPLL_CORE          = 0xD8,
   
   //CLKM_RTC zone
   CLKM_RTC_RTC_CLKCTRL           = 0x00,
   CLKM_RTC_CLKSTCTRL             = 0x04
}CLK_MODULE_REG;


/**
 * @brief Clock Modules Domaines bases: TRM 2.1
 **/
typedef enum
{
   CLKM_PER     = 0x44E00000,
   CLKM_WKUP    = 0x44E00400,
   CLKM_DPLL    = 0x44E00500,
   CLKM_MPU     = 0x44E00600,
   CLKM_DEVICE  = 0x44E00700,
   CLKM_RTC     = 0x44E00800,
   CLKM_GFX     = 0X44E00900,
   CLKM_CEFUSE  = 0X44E00A00
}CLK_MODULE_t;

/**
 * @fn void CLKM_setCLKModuleRegister(CLK_MODULE_t module, CLKM_MODULE_REG reg, uint32_t value)
 * @brief               Set the clock register to a certain value.
 * @param[in]  module   Parent module of register
 * @param[in]  reg      Register to set value.
 * @param[in]  value    Value to set register to.
 * @return              void
 **/
void CLKM_setCLKModuleRegister(CLK_MODULE_t module, CLK_MODULE_REG reg, uint32_t value);


/**
 * @fn uint32_t CLKM_getCLKModuleRegister(CLK_MODULE_t module, CLKM_MODULE_REG reg)
 * @brief               Get the clock register value.
 * @param[in]  module   Parent module of register
 * @param[in]  reg      Register to get the value from.
 * @return              value of the clock register.
 **/
uint32_t CLKM_getCLKModuleRegister(CLK_MODULE_t module, CLK_MODULE_REG reg);



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


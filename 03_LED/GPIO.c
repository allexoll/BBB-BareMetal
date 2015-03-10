/**
 * @file GPIO.c
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief Implementation concerning GPIO usage: TRM 9.3.51, TRM 25, Datasheet 4
 **/

#include "GPIO.h"
#include "start.h"
#include "clock_module.h"
#include "control_module.h"
#include "pad.h"
#include "types.h"
#define GPIO_REVISION           0x000
#define GPIO_SYSCONFIG          0x010
#define GPIO_EOI                0x020
#define GPIO_IRQSTATUS_RAW_0    0x024
#define GPIO_IRQSTATUS_RAW_1    0x028
#define GPIO_IRQSTATUS_0        0x02C
#define GPIO_IRQSTATUS_1        0x030
#define GPIO_IRQSTATUS_SET_0    0x034
#define GPIO_IRQSTATUS_SET_1    0x038
#define GPIO_IRQSTATUS_CLR_0    0x03C
#define GPIO_IRQSTATUS_CLR_1    0x040
#define GPIO_IRQWAKEN_0         0x044
#define GPIO_IRQWAKEN_1         0x048
#define GPIO_SYSSTATUS          0x114
#define GPIO_CTRL               0x130
#define GPIO_OE                 0x134
#define GPIO_DATAIN             0x138
#define GPIO_DATAOUT            0x13C
#define GPIO_LEVELDETECT0       0x140
#define GPIO_LEVELDETECT1       0x144
#define GPIO_RISINGDETECT       0x148
#define GPIO_FALLINGDETECT      0x14C
#define GPIO_DEBOUNCENABLE      0x150
#define GPIO_DEBOUNCINGTIME     0x154
#define GPIO_CLEARDATAOUT       0x190
#define GPIO_SETDATAOUT         0x194


static const unsigned int GPIO_BASE_ARRAY[4] = {0x44E07000, 0x4804C000, 0x481AC000, 0x481AE000};

// inject [pin, port], get CM_conf adress
// Datasheet 4.3.2
static const CONTROL_MODULE GPIO_CTRL_MODULE_ARRAY[32][4] = {
    //p0                          //p1                          //p2                          //p3
   {CM_conf_mdio                 ,CM_conf_gpmc_ad0             ,CM_conf_gpmc_csn3            ,CM_conf_mii1_col       },//.0
   {CM_conf_mdc                  ,CM_conf_gpmc_ad1             ,CM_conf_gpmc_clk             ,CM_conf_mii1_crs       },//.1
   {CM_conf_spi0_sclk            ,CM_conf_gpmc_ad2             ,CM_conf_gpmc_advn_ale        ,CM_conf_mii1_rx_er     },//.2
   {CM_conf_spi0_d0              ,CM_conf_gpmc_ad3             ,CM_conf_gpmc_oen_ren         ,CM_conf_mii1_tx_en     },//.3
   {CM_conf_spi0_d1              ,CM_conf_gpmc_ad4             ,CM_conf_gpmc_wen             ,CM_conf_mii1_rx_dv     },//.4
   {CM_conf_spi0_cs0             ,CM_conf_gpmc_ad5             ,CM_conf_gpmc_ben0_cle        ,CM_conf_i2c0_sda       },//.5
   {CM_conf_spi0_cs1             ,CM_conf_gpmc_ad6             ,CM_conf_lcd_data0            ,CM_conf_i2c0_scl       },//.6
   {CM_conf_ecap0_in_pwm0_out    ,CM_conf_gpmc_ad7             ,CM_conf_lcd_data1            ,CM_conf_emu0           },//.7
   {CM_conf_lcd_data12           ,CM_conf_uart0_ctsn           ,CM_conf_lcd_data2            ,CM_conf_emu1           },//.8
   {CM_conf_lcd_data13           ,CM_conf_uart0_rtsn           ,CM_conf_lcd_data3            ,CM_conf_mii1_tx_clk    },//.9
   {CM_conf_lcd_data14           ,CM_conf_uart0_rxd            ,CM_conf_lcd_data4            ,CM_conf_mii1_rx_clk    },//.10
   {CM_conf_lcd_data15           ,CM_conf_uart0_txd            ,CM_conf_lcd_data5            ,-1                     },//.11
   {CM_conf_uart1_ctsn           ,CM_conf_gpmc_ad12            ,CM_conf_lcd_data6            ,-1                     },//.12
   {CM_conf_uart1_rtsn           ,CM_conf_gpmc_ad13            ,CM_conf_lcd_data7            ,CM_conf_usb1_drvvbus   },//.13
   {CM_conf_uart1_rxd            ,CM_conf_gpmc_ad14            ,CM_conf_lcd_data8            ,CM_conf_mcasp0_aclkx   },//.14
   {CM_conf_uart1_txd            ,CM_conf_gpmc_ad15            ,CM_conf_lcd_data9            ,CM_conf_mcasp0_fsx     },//.15
   {CM_conf_mii1_txd3            ,CM_conf_gpmc_a0              ,CM_conf_lcd_data10           ,CM_conf_mcasp0_axr0    },//.16
   {CM_conf_mii1_txd2            ,CM_conf_gpmc_a1              ,CM_conf_lcd_data11           ,CM_conf_mcasp0_ahclkr  },//.17
   {CM_conf_usb0_drvvbus         ,CM_conf_gpmc_a2              ,CM_conf_mii1_rxd3            ,CM_conf_mcasp0_aclkr   },//.18
   {CM_conf_xdma_event_intr0     ,CM_conf_gpmc_a3              ,CM_conf_mii1_rxd2            ,CM_conf_mcasp0_fsr     },//.19
   {CM_conf_xdma_event_intr1     ,CM_conf_gpmc_a4              ,CM_conf_mii1_rxd1            ,CM_conf_mcasp0_axr1    },//.20
   {CM_conf_mii1_txd1            ,CM_conf_gpmc_a5              ,CM_conf_mii1_rxd0            ,CM_conf_mcasp0_ahclkx  },//.21
   {CM_conf_gpmc_ad8             ,CM_conf_gpmc_a6              ,CM_conf_lcd_vsync            ,-1                     },//.22
   {CM_conf_gpmc_ad9             ,CM_conf_gpmc_a7              ,CM_conf_lcd_hsync            ,-1                     },//.23
   {-1                           ,CM_conf_gpmc_a8              ,CM_conf_lcd_pclk             ,-1                     },//.24
   {-1                           ,CM_conf_gpmc_a9              ,CM_conf_lcd_ac_bias_en       ,-1                     },//.25
   {CM_conf_gpmc_ad10            ,CM_conf_gpmc_a10             ,CM_conf_mmc0_dat3            ,-1                     },//.26
   {CM_conf_gpmc_ad11            ,CM_conf_gpmc_a11             ,CM_conf_mmc0_dat2            ,-1                     },//.27
   {CM_conf_mii1_txd0            ,CM_conf_gpmc_ben1            ,CM_conf_mmc0_dat1            ,-1                     },//.28
   {CM_conf_rmii1_ref_clk        ,CM_conf_gpmc_csn0            ,CM_conf_mmc0_dat0            ,-1                     },//.29
   {CM_conf_gpmc_wait0           ,CM_conf_gpmc_csn1            ,CM_conf_mmc0_clk             ,-1                     },//.30
   {CM_conf_gpmc_wpn             ,CM_conf_gpmc_csn2            ,CM_conf_mmc0_cmd             ,-1                     },//.31
};

bool GPIO_checkValidPortPin(GPIO_t port, pin_t pin)
{
   if((port < GPIO0) || (port > GPIO3))
   {
      // TODO: raise error (port is either too big or negative: /port)
      return false;
   }
   if((pin < 0) || (pin > 31))
   {
      // TODO: raise error (pin is either too big or negative: /pin)
      return false;
   }
   if(GPIO_CTRL_MODULE_ARRAY[pin][port] == -1)
   {
      // TODO: raise error (pin/port combinaison isnt present on this chip: /port./pin)
      return false;
   }
   return true;
}


static bool GPIO_CheckValidDirection(pin_direction_t dir)
{
   if((dir!=INPUT) && (dir!=OUTPUT))
   {
      // TODO: raise error (direction not valid: /dir)
      return false;
   }
   return true;
}

void GPIO_initPort(GPIO_t port)
{
   if(GPIO_checkValidPortPin(port,0))  // pin 0 always exist
   {
      unsigned int setting = (1<<18) | (0x2<<0);   //enable functional clock & enable module, TRM 8.1.12.1.32
      switch(port)
      {
         case GPIO0:
            return;        // GPIO0 doesnt have a clock module register, TRM 8.1.12.1
            break;
         case GPIO1:
            CKM_setCLKModuleRegister(CKM_PER, CKM_PER_GPIO1_CLKCTRL, setting);
            while((CKM_getCLKModuleRegister(CKM_PER, CKM_PER_GPIO1_CLKCTRL) & (0x3<<16)) != 0)
            break;
         case GPIO2:
            CKM_setCLKModuleRegister(CKM_PER, CKM_PER_GPIO2_CLKCTRL, setting);
            while((CKM_getCLKModuleRegister(CKM_PER, CKM_PER_GPIO2_CLKCTRL) & (0x3<<16)) != 0)
            break;
         case 3:
            CKM_setCLKModuleRegister(CKM_PER, CKM_PER_GPIO3_CLKCTRL, setting);
            while((CKM_getCLKModuleRegister(CKM_PER, CKM_PER_GPIO3_CLKCTRL) & (0x3<<16)) != 0)
            break;
         default:
            // TODO: raise error (not possible, checked port before: /port)
            break;
      }
   }
}


void GPIO_initPin(GPIO_t port, pin_t pin)
{
   if(GPIO_checkValidPortPin(port,pin))
   {
      CONTROL_MODULE module = GPIO_CTRL_MODULE_ARRAY[pin][port];  // get conf <module> <pin> for port/pin combination
      PAD_setMode(module, MODE_7);  //set mode to GPIO, Datasheet 4.3.2
      return;
   }
}
void GPIO_setDirection(GPIO_t port, pin_t pin, pin_direction_t dir)
{
   if(GPIO_checkValidPortPin(port,pin))
   {
      if(GPIO_CheckValidDirection(dir))
      {
         unsigned int addr_temp = GPIO_BASE_ARRAY[port] + GPIO_OE;// GPIOx base + output enable offset, TRM 2.1 & 25.4.1.16
         unsigned int val_temp = GET32(addr_temp);                   // not overwriting previous port setting
         val_temp &= ~(1<<pin);
         val_temp |= (dir<<pin);
         PUT32(addr_temp,val_temp);    // writing new port setting
      }
   }
}
pin_direction_t GPIO_getDirection(GPIO_t port, pin_t pin)
{
   if(GPIO_checkValidPortPin(port,pin))
   {
      unsigned int addr_temp = GPIO_BASE_ARRAY[port] + GPIO_OE;      // GPIOx base + output enable offset, TRM 2.1 & 25.4.1.16
      unsigned int val_temp = GET32(addr_temp);
      if(val_temp & (1<<pin)) // masking for wanted pin
      {
         return INPUT;
      }
      else
      {
         return OUTPUT;
      }
   }
   else
   {
      return -1;     // isn't a valid port/pin combination or doesnt exist
   }
}

void GPIO_setPin(GPIO_t port, pin_t pin)
{
   if(GPIO_checkValidPortPin(port,pin))
   {
      unsigned int addr_temp = GPIO_BASE_ARRAY[port] + GPIO_SETDATAOUT; // GPIOx base + set data out offset, TRM 2.1 & 25.4.1.26
      unsigned int val_temp = 1<<pin;
      PUT32(addr_temp, val_temp);
   }
}
void GPIO_clrPin(GPIO_t port, pin_t pin)
{
   if(GPIO_checkValidPortPin(port,pin))
   {
      unsigned int addr_temp = GPIO_BASE_ARRAY[port]+GPIO_CLEARDATAOUT;  // GPIOx base+clear data out offset, TRM 2.1 & 25.4.1.25
      unsigned int val_temp = 1<<pin;
      PUT32(addr_temp, val_temp);
   }
}

level_t GPIO_getPin(GPIO_t port, pin_t pin)
{
   if(GPIO_checkValidPortPin(port,pin))
   {
      unsigned int addr_temp = GPIO_BASE_ARRAY[port] + GPIO_DATAIN; // GPIOx base + data in offset, TRM 2.1 & 25.4.1.17
      unsigned int val_temp = GET32(addr_temp);
      if(val_temp & (1<<pin))
      {
         return HIGH;
      }
      else
      {
         return LOW;
      }
   }
   else
   {
      return -1;  // isnt a valid port/pin combination or doesnt exist
   }
}


unsigned int GPIO_getPort(GPIO_t port)
{
   if(GPIO_checkValidPortPin(port,0)) // pin 0 always exist
   {
      unsigned int addr_temp = GPIO_BASE_ARRAY[port] + GPIO_DATAIN;  // GPIOx base + data in offset, TRM 2.1 & 25.4.1.17
      return GET32(addr_temp);
   }
   return -1;
}


void GPIO_setPort(GPIO_t port, unsigned int value)
{
   if(GPIO_checkValidPortPin(port,0)) // pin 0 always exist
   {
      unsigned int addr_temp = GPIO_BASE_ARRAY[port] + GPIO_DATAOUT;  // GPIOx base + data in offset, TRM 2.1 & 25.4.1.18
      PUT32(addr_temp, value);
   }
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

/**
 * @file LED.c
 * @author Alexis Marquet
 * @date 04 Dec 2014
 * @brief Implementation for the BeagleBone Black onboard leds: BBB_SCH p.3 
 **/

#include "LED.h"
#include "GPIO.h"
#include "types.h"
void LED_init(void)
{
   // init GPIO1 port
   GPIO_initPort(GPIO1);
   // init GPIO1.21-24 pins
   GPIO_initPin(GPIO1,USER_LED0);
   GPIO_initPin(GPIO1,USER_LED1);
   GPIO_initPin(GPIO1,USER_LED2);
   GPIO_initPin(GPIO1,USER_LED3);
   // set GPIO1.21-24 as OUTPUT
   GPIO_setDirection(GPIO1,USER_LED0,OUTPUT);
   GPIO_setDirection(GPIO1,USER_LED1,OUTPUT);
   GPIO_setDirection(GPIO1,USER_LED2,OUTPUT);
   GPIO_setDirection(GPIO1,USER_LED3,OUTPUT);
   // clear on init
   GPIO_clrPin(GPIO1,USER_LED0);
   GPIO_clrPin(GPIO1,USER_LED1);
   GPIO_clrPin(GPIO1,USER_LED2);
   GPIO_clrPin(GPIO1,USER_LED3);

}

static bool LED_checkValidLed(USER_LED_t led)
{
   if((led < USER_LED0) || (led > USER_LED3))
   {
      // TODO: raise error (led is either too big or negative: /led)
      return false;
   }
   return true;
}
void LED_on(USER_LED_t led)
{
   if(LED_checkValidLed(led))
   {
      GPIO_setPin(GPIO1,led);
   }
}
void LED_off(USER_LED_t led)
{
   if(LED_checkValidLed(led))
   {
      GPIO_clrPin(GPIO1,led);
   }
}
void LED_invert(USER_LED_t led)
{
   if(LED_checkValidLed(led))
   {
      level_t actual = GPIO_getPin(GPIO1,led);
      if(actual == HIGH)
      {
         GPIO_clrPin(GPIO1,led);
      }
      else
      {
         GPIO_setPin(GPIO1,led);
      }
   }
}
void LED_setValue(unsigned char value)
{
   unsigned int old_port = GPIO_getPort(GPIO1);
   value &= 0x0F; // mask 4 lsb
   old_port &= ~(0x0F<<21); // set to 0
   old_port |= (value<<21);
   GPIO_setPort(GPIO1,old_port);
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

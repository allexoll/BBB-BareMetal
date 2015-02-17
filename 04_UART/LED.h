/**
 * @file LED.h
 * @author Alexis Marquet
 * @date 04 Dec 2014
 * @brief File containing function prototypes for the BeagleBone Black onboard leds: BBB_SCH p.3
 **/

#ifndef __LED_H
#define __LED_H

/**
 * @brief User led number (0-3)
 **/
typedef enum
{
   USER_LED0 = 21,
   USER_LED1 = 22,
   USER_LED2 = 23,
   USER_LED3 = 24
}USER_LED_t;

/**
 * @fn void LED_init(void)
 * @brief         Initialize the Leds GPIOs
 * return         void
 **/
void LED_init(void);

/**
 * @fn void LED_on(USER_LED_t led)
 * @brief            Turn a led on.
 * @param[in] led    Led to turn on.
 * @return           void
 **/
void LED_on(USER_LED_t led);


/**
 * @fn void LED_off(USER_LED_t led)
 * @brief            Turn a led off.
 * @param[in] led    Led to turn off.
 * @return           void
 **/
void LED_off(USER_LED_t led);

/**
 * @fn void LED_invert(USER_LED_t led)
 * @brief            Invert a led on.
 * @param[in] led    Led to turn invert.
 * @return           void
 **/
void LED_invert(USER_LED_t led);


/**
 * @fn void LED_setValue(unsigned char value)
 * @brief            Set a value on the 4 user leds.
 * @param[in] value  Value to set on the user leds.
 * @return           void
 **/
void LED_setValue(unsigned char value);
#endif /* defined(__LED_H) */



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


/**
 * @file GPIO.h
 * @author Alexis Marquet
 * @date 02 Dec 2014
 * @brief Types & function prototypes concerning GPIO usage: TRM 9.3.51, TRM 25, Datasheet 4
 **/
#ifndef __GPIO_h
#define __GPIO_h

/**
 * @brief GPIO pin number (0-31)
 */
typedef unsigned char pin_t;

/**
 * @brief Logic HIGH (1) or logic LOW (0).
 */
typedef enum
{
   HIGH = 1,
   LOW = 0
}level_t;

/**
 * @brief GPIO port number (GPIO0-GPIO3).
 **/
typedef enum
{
   GPIO0 = 0,
   GPIO1 = 1,
   GPIO2 = 2,
   GPIO3 = 3
} GPIO_t;

/**
 * @brief GPIO pin direction (INPUT/OUTPUT).
 **/
typedef enum
{
   INPUT = 1,  
   OUTPUT = 0
}pin_direction_t;

/**
 * @fn void GPIO_initPort(GPIO_t port)
 * @brief      Initialize port.
 * @param[in]  port  Port to initialize.
 * @return     void
 **/
void GPIO_initPort(GPIO_t port);


/**
 * @fn void GPIO_initPin(GPIO_t port, pin_t pin)
 * @brief      Initialize port.pin.
 * @param[in]  port  Parent port of pin.
 * @param[in]  pin   Pin of port to initialize.
 * @return     void
 **/
void GPIO_initPin(GPIO_t port, pin_t pin);


/**
 * @fn void GPIO_setDirection(GPIO_t port, pin_t pin, pin_direction_t dir)
 * @brief      Set the direction for port.pin.
 * @param[in]  port  Parent port of pin.
 * @param[in]  pin   Pin of port to set the direction of.
 * @param[in]  dir   Direction to set port.pin to.
 * @return     void
 **/
void GPIO_setDirection(GPIO_t port, pin_t pin, pin_direction_t dir);


/**
 * @fn pin_direction_t GPIO_getDirection(GPIO_t port, pin_t pin)
 * @brief      Get the port.pin direction.
 * @param[in]  port  Parent port of pin.
 * @param[in]  pin   Pin of port to get the direction of.
 * @return           The direction of port.pin.
 **/
pin_direction_t GPIO_getDirection(GPIO_t port, pin_t pin);

/**
 * @fn void GPIO_setPin(GPIO_t port, pin_t pin)
 * @brief            Set port.pin to HIGH (port.pin must be set as OUTPUT previously).
 * @param[in]  port  Parent port of pin.
 * @param[in]  pin   Pin of port to set.
 * @return           void
 **/
void GPIO_setPin(GPIO_t port, pin_t pin);


/**
 * @fn void GPIO_clrPin(GPIO_t port, pin_t pin)
 * @brief            Set Port.pin to LOW (port.pin must be set as OUTPUT previously).
 * @param[in]  port  Parent port of pin.
 * @param[in]  pin   Pin of port to clear.
 * @return           void
 **/
void GPIO_clrPin(GPIO_t port, pin_t pin);


/**
 * @fn level_t GPIO_getPin(GPIO_t port, pin_t pin)
 * @brief            Get the level of port.pin (port.pin must be set as INPUT previously).
 * @param[in]  port  Parent port of pin.
 * @param[in]  pin   Pin of port to get.
 * @return           The level of port.pin.
 **/
level_t GPIO_getPin(GPIO_t port, pin_t pin);


/**
 * @fn void GPIO_setPort(GPIO_t port, unsigned int value)
 * @brief            Set the data on the port.
 * @param[in]  port  Port to write.
 * @param[in]  value Value to write on the port
 * @return           void
 **/
void GPIO_setPort(GPIO_t port, unsigned int value);


/**
 * @fn unsigned int GPIO_getPort(GPIO_t port)
 * @brief            Get the data on the port.
 * @param[in] port   Port to read.
 * @return           data read on the port.
 **/
unsigned int GPIO_getPort(GPIO_t port);


#endif



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


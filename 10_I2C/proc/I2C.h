/**
 * @file I2C.h
 * @author Alexis Marquet
 * @date 25 May 2015
 * @brief Types & function prototypes concerning I2C peripherals for AM335x: TRM 21, Datasheet 4.2
 **/

#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>
#include <vector>

using namespace std;

/**
 * @brief I2C number [0-2]
 **/
typedef enum
{
   I2C0 = 0,
   I2C1 = 1,
   I2C2 = 2
}I2C_t;

/**
 * @fn void I2C_initI2C(I2C_t i2c, uint32_t clkSpeed)
 * @brief                  Init an instance of I2C for the AM335x
 * @param[in]  i2c         I2C instance to init (I2C0, I2C1, I2C2).
 * @param[in]  clkSpeed    clock speed parameter for this instance in Hz.
 * @return     void
 **/
void I2C_initI2C(I2C_t i2c, uint32_t clkSpeed);

/**
 * @fn uint32_t I2C_write(I2C_t i2c, uint8_t slave_addr, uint8_t* b, uint32_t length)
 * @brief                  write procedure for I2C
 * @param[in]  i2c         I2C instance to use (I2C0, I2C1, I2C2).
 * @param[in]  slave_addr  address of the slave to communicate with.
 * @param[in]  b           buffer containing the data to send.
 * @param[in]  length      length of the buffer b.
 * @return                 The length written.
 *
 * This function write [length] byte from [b] to the chip answering to the address [slave_addr].\n
 * If the device answers and all goes well during the transfer, return value should be equal to [length]\n
 * if the device does not answer for whatever reason, the return value will be 0.
 **/
uint32_t I2C_write(I2C_t i2c, uint8_t slave_addr, uint8_t* b, uint32_t length);

/**
 * @fn uint32_t I2C_read(I2C_t i2c, uint8_t slave_addr, uint8_t* b, uint32_t length)
 * @brief                  read procedure for I2C
 * @param[in]  i2c         I2C instance to use (I2C0, I2C1, I2C2).
 * @param[in]  slave_addr  address of the slave to communicate with.
 * @param[in]  b           buffer to save the data to.
 * @param[in]  length      length of the data to read.
 * @return                 The length read.
 *
 * This function read [length] byte and saves it to [b] from the chip answering to the address [slave_addr].\n
 * If the device answers and all goes well during the transfer, return value should be equal to [length]\n
 * if the device does not answer for whatever reason, the return value will be 0.
 **/
uint32_t I2C_read(I2C_t i2c, uint8_t slave_addr, uint8_t* b, uint32_t length);

/**
 * @fn vector <uint8_t> I2C_busProbe(I2C_t i2c)
 * @brief                  This function probes the I2C bus for answering devices.
 * @param[in]  i2c         I2C instance to use (I2C0, I2C1, I2C2).
 * @return                 A list containing the address to which a device answered (no Nack)
 **/
vector <uint8_t> I2C_busProbe(I2C_t i2c);

#endif /* defined(__I2C_H) */

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

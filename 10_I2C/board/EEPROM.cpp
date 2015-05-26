/**
 * @file 24XX32A.cpp
 * @author Alexis Marquet
 * @date 26 May 2015
 * @brief Types & function implementation for reading the on-board EEPROM (24XX32A Serial EEPROM).
 * The EEPROM can only be read because the WP pin is tied to VDD with a pull-up.
 **/
extern "C"
{
#include <stdint.h>
#include <stdio.h>
}
#include "../proc/I2C.h"

#include "EEPROM.h"

#include <iostream>

#define Address_24XX32A (0xa0)

using namespace std;

uint32_t EEPROM_read(uint32_t startAddress, uint8_t *b, uint32_t length)
{
   uint8_t rxb[5];
   rxb[0] = (uint8_t) startAddress >> 4;
   rxb[1] = (uint8_t) startAddress & 0xFF;

   if(I2C_write(I2C0,0xa0,&rxb[0],2))
   {
      return I2C_read(I2C0,0xa0,b,length);
   }
   return 0;
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
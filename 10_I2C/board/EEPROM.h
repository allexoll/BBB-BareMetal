/**
 * @file 24XX32A.h
 * @author Alexis Marquet
 * @date 26 May 2015
 * @brief Types & function prototypes for reading the on-board EEPROM (24XX32A Serial EEPROM). 
 * The EEPROM can only be read because the WP pin is tied to VDD with a pull-up.
 **/

#ifndef __24XX32A_H
#define __24XX32A_H

#include <stdio.h>
using namespace std;
/**
 * @brief board ID info, referenced in http://processors.wiki.ti.com/index.php/AM335x_Starter_Kit_ID_Memory_Programming
 **/
struct EEPROM_ID
{
#pragma pack(1)
   /**
    * @brief Magic number, should be equal to 0xEE3355AA
    **/
   uint32_t magic;
   /**
    * @brief boardName, version, serialNumber are all NON-null-terminated strings
    **/
   uint8_t boardName[8];
   uint8_t version[4];
   uint8_t serialNumber[12];
   
   uint8_t configOption[32];
};

/**
 * @fn uint32_t EEPROM_read(uint32_t startAddress, uint8_t *b, uint32_t length)
 * @brief                     read function for the 24XX32A Serial EEPROM
 * @param[in]  startAddress   address from which to start the read sequence
 * @param[in]  b              buffer in which to store the data read from the chip
 * @param[in]  length         length of the data to read.
 * @return                    the lenght read.
 * If the device did not answer, the return value will be 0, otherwise 
 * it will be equal to [length] in cas of success
 **/
uint32_t EEPROM_read(uint32_t startAddress, uint8_t *b, uint32_t length);

#endif /* defined(__24XX32A_H) */

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
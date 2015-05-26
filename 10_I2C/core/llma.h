/**
 * @file llma.h
 * @author Alexis Marquet
 * @date 27 Feb 2015
 * @brief Prototypes for low level memory access function
 **/

#ifndef __llma_h
#define __llma_h


   
#include <stdint.h>

#define REG32(addr)  (*((volatile uint32_t*) (addr)))
#define REG16(addr)  (*((volatile uint16_t*) (addr)))
#define REG8(addr)   (*((volatile uint8_t *) (addr)))


/**
 * @fn void PUT32(uint32_t address, uint32_t value)
 * @brief               Put a 32bit word at an address.
 * @param[in] address   Address to put the word to.
 * @param[in] value     32bit word to write at the address.
 * @return              void (always succeed)
 **/
void PUT32(uint32_t address, uint32_t value);


/**
 * @fn uint32_t GET32 (uint32_t address)
 * @brief               Get a 32bit word at an address.
 * @param[in] address   Address to get the word from.
 * @return              the value read at said address.
 **/
uint32_t GET32 (uint32_t address);


/**
 * @fn void PUT16(uint32_t address, uint32_t value)
 * @brief               Put a 16bit word at an address.
 * @param[in] address   Address to put the word to.
 * @param[in] value     16bit word to write at the address.
 * @return              void (always succeed)
 **/
void PUT16(uint32_t address, uint16_t value);


/**
 * @fn uint32_t GET16 (uint32_t address)
 * @brief               Get a 16bit word at an address.
 * @param[in] address   Address to get the word from.
 * @return              the value read at said address.
 **/
uint16_t GET16 (uint32_t address);


/**
 * @fn void PUT8(uint32_t address, uint32_t value)
 * @brief               Put a 8bit word at an address.
 * @param[in] address   Address to put the word to.
 * @param[in] value     8bit word to write at the address.
 * @return              void (always succeed)
 **/
void PUT8(uint32_t address, uint8_t value);


/**
 * @fn uint32_t GET8 (uint32_t address)
 * @brief               Get a 8bit word at an address.
 * @param[in] address   Address to get the word from.
 * @return              the value read at said address.
 **/
uint8_t GET8 (uint32_t address);


/**
 * @fn void BRANCHTO (uint32_t address)
 * @brief               branch to address. this should never return
 * @param[in] address   Address to branch to
 **/
void BRANCHTO (uint32_t address);

/**
 * @fn void CPU_irqE()
 * @brief               enable Master Irq in CPSR (clears the I bit)
 **/
void CPU_irqE();

/**
 * @fn void CPU_irqD()
 * @brief               disable Master Irq in CPSR (sets the I bit)
 **/
void CPU_irqD();



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

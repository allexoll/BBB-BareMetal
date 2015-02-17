/**
 * @file clock_module.c
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief Implementation concerning clock module usage: TRM 8
 **/

#include "clock_module.h"
#include "start.h"
#include "types.h"


// TODO: implement module/reg validity check

void CKM_setCLKModuleRegister(CLK_MODULE_t module, CKM_MODULE_REG reg, unsigned int value)
{
   unsigned int addr_temp = module + reg;    // clock module base + module offset, TRM 2.1 & 8.1.12.1
   PUT32(addr_temp, value);
}
unsigned int CKM_getCLKModuleRegister(CLK_MODULE_t module, CKM_MODULE_REG reg)
{
   
   unsigned int addr_temp = module + reg;    // clock module base + module offset, TRM 2.1 & 8.1.12.1
   return GET32(addr_temp);
   
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

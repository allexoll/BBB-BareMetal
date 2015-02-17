//
//  clock_module.c
//
//  Created by Alexis Marquet on 03/12/14.
//
//

#include "clock_module.h"
#include "start.h"
#include "types.h"


#define CKM_PER_BASE    0x44E00000  // clock module power enable register base, TMR 2.1
static bool CKM_checkValidModule(CKM_MODULE_REG module)
{
   if((module >CKM_PER_CLK_24MHZ_CLKSTCTRL))
   {
      // TODO: raise error (CKM_MODULE_REG too big: /module)
      return false;
   }
   return true;
}
void CKM_setCLKModuleRegister(CKM_MODULE_REG module, unsigned int value)
{
   if(CKM_checkValidModule(module))
   {
      unsigned int addr_temp = CKM_PER_BASE + module;    // clock module base + module offset, TRM 2.1 & 8.1.12.1
      PUT32(addr_temp, value);
   }
}
unsigned int CKM_getCLKModuleRegister(CKM_MODULE_REG module)
{
   if(CKM_checkValidModule(module))
   {
      unsigned int addr_temp = CKM_PER_BASE + module;    // clock module base + module offset, TRM 2.1 & 8.1.12.1
      return GET32(addr_temp);
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
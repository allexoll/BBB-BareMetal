/**
 * @file control_module.c
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief Implementation concerning control module usage: TRM 9, TRM 9.3
 **/

#include "control_module.h"
#include "start.h"

#define CM_MODULE_REGISTER_BASE  0x44E10000


void CM_setCtrlModule(CONTROL_MODULE module, unsigned int value)
{
   PUT32(CM_MODULE_REGISTER_BASE + module, value);
}

unsigned int CM_getCtrlModule(CONTROL_MODULE module)
{
   return GET32(CM_MODULE_REGISTER_BASE + module);
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

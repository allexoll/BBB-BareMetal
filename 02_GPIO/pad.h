//
//  pad.h
//
//  Created by Alexis Marquet on 03/12/14.
//
//
/**
 * @file pad.h
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief File containing types & function prototypes concerning pad usage: TRM 9.2.2.1, Datasheet 4
 **/
#ifndef __pad_H
#define __pad_H
#include "control_module.h"


typedef enum
{
   MODE_0 = 0,
   MODE_1 = 1,
   MODE_2 = 2,
   MODE_3 = 3,
   MODE_4 = 4,
   MODE_5 = 5,
   MODE_6 = 6,
   MODE_7 = 7
   
}pinmode_t;

void PAD_setMode(CONTROL_MODULE module, pinmode_t mode);
pinmode_t PAD_getMode(CONTROL_MODULE module);

#endif /* defined(__pad_H) */



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
//
//  pad.c
//
//  Created by Alexis Marquet on 03/12/14.
//
//

#include "pad.h"
#include "control_module.h"


void PAD_setMode(CONTROL_MODULE module, pinmode_t mode)
{
   if((module <= CM_conf_usb1_drvvbus ) && (module >= CM_conf_gpmc_ad0))
   {
      unsigned int temp = CM_getCtrlModule(module);
      temp &= ~(0b111);
      temp |= mode;
      CM_setCtrlModule(module, temp);
   }
   else
   {
      // TODO: raise error (control module isnt a "conf <module> <pin>" register)
      return;
   }
}
pinmode_t PAD_getMode(CONTROL_MODULE module)
{
   if((module <= CM_conf_usb1_drvvbus ) && (module >= CM_conf_gpmc_ad0))
   {
      unsigned int temp = CM_getCtrlModule(module);
      temp &= ~(0b111);
      return (pinmode_t) temp;
   }
   else
   {
      // TODO: raise error (control module isnt a "conf <module> <pin>" register)
      return -1;
   }
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
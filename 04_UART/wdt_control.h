/*
 * wdt_control.c - Watchdog Timer control in a baremetal application for BeagleBone Black
 *
 * Description:
 * This program demonstrates how to access and control the Watchdog Timer (WDT) in a baremetal
 * application for the BeagleBone Black. It provides a function to clear the WDT_WTGR (Watchdog Timer
 * Global Register), preventing the watchdog from resetting the system.
 *
 * License:
 * MIT License
 *
 * Copyright (c) 2024 Jesus Humberto Ontiveros Mayorquin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdint.h>

// Watchdog Timer Global Register (WDT_WTGR) address for BeagleBone Black
#define WDT_WTGR_REG_ADDR   0x44E35030
#define WDT_WSPR_ADDR       0x44E35048
#define WDT_WWPS_ADDR       0x44E35034

#define XXXX_AAAA           0x0000AAAA
#define XXXX_5555           0x00005555
#define XXXX_BBBB           0x0000BBBB
#define XXXX_4444           0x00004444
#define W_PEND_WSPR         0X00000010// Bit 4 in WDT_WWPS register

//Funtion to disable the Watchdog Timer
void disable_watchdog_timer();

//Funtion to enable the Watchdog Timer
void enable_watchdog_timer();
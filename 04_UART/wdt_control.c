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

#include "wdt_control.h"
#include "start.h"

void disable_watchdog_timer() {
    volatile uint32_t *wdt_wspr = (volatile uint32_t *)WDT_WSPR_ADDR;
    volatile uint32_t *wdt_wwps = (volatile uint32_t *)WDT_WWPS_ADDR;

    // Step 1: Write XXXX AAAAh
    *wdt_wspr = (uint32_t)XXXX_AAAA;

    // Step 2: Poll for completion
    while ((*wdt_wwps & W_PEND_WSPR) != 0) {}  // Wait until write completion

    // Step 3: Write XXXX 5555h
    *wdt_wspr = (uint32_t)XXXX_5555;

    // Step 4: Poll for completion
    while ((*wdt_wwps & W_PEND_WSPR) != 0) {}  // Wait until write completion
}

void enable_watchdog_timer() {
    volatile uint32_t *wdt_wspr = (volatile uint32_t *)WDT_WSPR_ADDR;
    volatile uint32_t *wdt_wwps = (volatile uint32_t *)WDT_WWPS_ADDR;

    // Step 1: Write XXXX BBBBh
    *wdt_wspr = (uint32_t)XXXX_BBBB;

    // Step 2: Poll for completion
    while ((*wdt_wwps & W_PEND_WSPR) != 0) {}  // Wait until write completion

    // Step 3: Write XXXX 4444h
    *wdt_wspr = (uint32_t)XXXX_4444;

    // Step 4: Poll for completion
    while ((*wdt_wwps & W_PEND_WSPR) != 0) {}  // Wait until write completion
}

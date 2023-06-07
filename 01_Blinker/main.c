extern void PUT32 (unsigned int address, unsigned int value);
extern unsigned int GET32 (unsigned int address);

#define GPIO1_BASE		0x4804C000
#define GPIO_SYSCONFIG	0x10
#define GPIO_SYSSTATUS	0x114
#define GPIO_OE			0x134
#define GPIO_CLRDATAOUT	0x190
#define GPIO_SETDATAOUT	0x194

#define CM_PER_BASE		0x44e00000
#define CM_PER_GPIO1		0xAC

#define TIME 500000
void _main (void)
{
	volatile unsigned int ra;
		PUT32(CM_PER_BASE+CM_PER_GPIO1, 1<<18 | 2);
		ra = GET32(GPIO1_BASE+GPIO_OE);
		ra &= ~(15<<21);
		PUT32(GPIO1_BASE+GPIO_OE,ra);
	for(;;)
	{
		PUT32(GPIO1_BASE+GPIO_SETDATAOUT, (15<<21));
		for(ra = 0; ra < TIME; ra ++);
		PUT32(GPIO1_BASE+GPIO_CLRDATAOUT,15<<21);
		for(ra = 0; ra < TIME; ra ++);
	}
   return;
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

/**
 * @file main.c
 * @author Alexis Marquet
 * @date 30 Apr 2015
 * @brief contains the main application
 **/


/**
 * @mainpage
 * 07_Bootloader: This sample implements a bootloader. after initializing the board, including the DDR chip.
 * it it then prints the code destination (0x80000000) and waits for a file to be sent.
 * The structure of the executable is as follows:
 * | 4 bytes | variable | 8 bytes |
 * | length  | data     | checksum|
 * The checksum is just  a sum on the complete file, byte by byte. not the best integrity check, but good enough.
 * after the file is recieved, the bootloader compares both checksums (the one received, and the one computed)
 * and if they match, it branches to the entry point.
 * The \005 character is because i programmed my terminal to automatically send the file when this character
 * is encountered.
 * If you want to send the file via xmodem, there's plenty of information on the web, including example, on
 * how to implement that.
 **/

#include <stdint.h>
#include "../board/LED.h"
#include "../proc/UART.h"
#include "../core/llma.h"
#include "../proc/clock_module.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BASE_ADRESS (0x80000000)
unsigned char a;
unsigned short b ;
unsigned int c ;

int main (void)
{
   
   unsigned int length = 0;
   unsigned long long int sumcheck = 0;
   unsigned long long int sum = 0;
   char *mem = (char*)BASE_ADRESS;
   
   printf(" (c) Alexis Marquet\n");
   printf("Bootloader ready, code destination = 0x%X\n",(unsigned int)mem);
   printf("Asking for boot file....... \005 \n");
   
   
   int l = read(0,&length,sizeof(length));
   int m = read(0,mem,length);
   int s = read(0,&sum,sizeof(sum));
   
   for(uint32_t i = 0; i < length; i++)
   {
      sumcheck += mem[i];
   }
   if(sum!=sumcheck)
   {
      fprintf(stderr,"Error when checking SUM, %llx != %llx\n",sum, sumcheck);
      while(1);
   }
   printf("about to branch...\n");
   BRANCHTO(BASE_ADRESS);
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


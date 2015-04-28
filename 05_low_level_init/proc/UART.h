/**
 * @file UART.h
 * @author Alexis Marquet
 * @date 04 Dec 2014
 * @brief Types & function prototypes concerning UARTs peripherals: TRM 19, Datasheet 4.2
 **/

#ifndef __UART_H
#define __UART_H

/**
 * @brief UART number (0-5)
 **/
typedef enum
{
   UART0 = 0,
   UART1 = 1,
   UART2 = 2,
   UART3 = 3,
   UART4 = 4,
   UART5 = 5
}UART_t;


/**
 * @brief Flow control
 **/
typedef enum
{
   FLOW_OFF = 0,
   FLOW_ON = 1
}FLOW_t;


/**
 * @brief Parity control
 **/
typedef enum
{
   PARITY_NONE,
   PARITY_EVEN,
   PARITY_ODD
}PARITY_BIT_t;


/**
 @brief Stop bit size
 **/
typedef enum
{
   STOP1,
   STOP1_5,
   STOP2
}STOP_BIT_t;


/**
 * @fn int UART_initUART(UART_t uart, unsigned int baudrate, STOP_BIT_t stopBit, PARITY_BIT_t parity, FLOW_t flowControl)
 * @brief                  Initialize an UART with coresponding parameters.
 * @param[in] uart         Uart to Initialize (0-5).
 * @param[in] baudrate     Baudrate to initialize the uart to.
 * @param[in] stopBit      Size of the stopBit.
 * @param[in] parity       Parity setting.
 * @param[in] flowControl  Flow Control setting.
 * @return                 void
 **/
void UART_initUART(UART_t uart, unsigned int baudrate, STOP_BIT_t stopBit, PARITY_BIT_t parity, FLOW_t flowControl);


/**
 * @fn void UART_putC(UART_t uart, char c)
 * @brief                  Send a character.
 * @param[in] uart         Uart to send the character through.
 * @param[in] c            Character to send.
 * @return                 void
 **/
void UART_putC(UART_t uart, char c);


/**
 * @fn char UART_getC(UART_t uart)
 * @brief                  Get a character.
 * @param[in] uart         Uart to get the character from.
 * @return                 The character gotten from the uart.
 **/
char UART_getC(UART_t uart);


/**
 * @fn int UART_putString(UART_t uart, char *str, unsigned int length)
 * @brief                  Send a string.
 * @param[in] uart         Uart to send the string through.
 * @param[in] str          Pointer to the string to send.
 * @param[in] length       Length of the string to send.
 * @return                 The length sent.
 **/
int UART_putString(UART_t uart, char *str, unsigned int length);

/**
 * @fn int UART_getString(UART_t uart, char *buf, unsigned int length)
 * @brief                  Get a string.
 * @param[in]  uart        Uart to get the string from.
 * @param[out] str         Pointer to the location where to put the string read.
 * @param[in]  length      Length to read.
 * @return                 The lenght read
 **/
int UART_getString(UART_t uart, char *buf, unsigned int length);


#endif /* defined(__UART_H) */



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

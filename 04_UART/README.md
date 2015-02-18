04_UART
===================

This example implements the UART. Thes code structure is setup for easy implementation for all UARTs, 0 trough 5, but this example implements only the UART0 peripheral, wich is the one on J1 connector. The UART will be used for log & debuging purposes. One new thing in this example is that the VFP & NEON coprocessor are enabled (sources from https://github.com/auselen under GNU GPL). See **UART.h** for function prototypes.
This example first prints something and then echoes what it sent to the UART.
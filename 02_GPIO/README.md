02_GPIO
=================

This example implements GPIO functions. it actually does the same as the 01_blinker example, although it is vary modular and generic. 
It is also documented using doxygen-style comments.

=================

First thing first, the **memmap.ld** is modified to use global & constant variables in the programm, by setting the ram origin to the right value (0x402f0400), doccumented in the "Initialisation sequence" in the *TRM*. 

the first thing to do (after startup) is to initialise the GPIO port. 
**GPIO_initPort()** does that. It enable the **CKM_MODULE_REG** for the port wanted.

Then you need to initialise the pin you want
**GPIO_initPin()** sets the pad related to the "GPIO" function using the **PAD_setMode()** func.

the last step of the GPIO initialisation is the direction. this example blinks the led, so you need to set it as output
**GPIO_setDirection()** only sets the GPIO Output Enable or not.

Then you can change the state of the GPIO using **GPIO_setPin()** & **GPIO_clrPin()**
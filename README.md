BBB-BareMetal
===============

Works on the beaglebone black (bare metal)


This rep will contain bare metal programs, examples, and code for the AM335x, wich is the processor on the BeagleBone Black board, sold by TI. I have been working on the raspberry pi for 2 years, but i switched because the BCM2835 wasn't documented enough for my tastes. 

a few very important links:

The AM335x Technical Reference Manual (yes, 4000+ pages) 

http://www.ti.com/lit/ug/spruh73k/spruh73k.pdf

The AM335x Datasheet (250 pages) 

http://www.ti.com/lit/ds/symlink/am3352.pdf

The BeagleBone Black Schematics 

https://github.com/CircuitCo/BeagleBone-Black/blob/master/BBB_SCH.pdf?raw=true

The BeagleBone Black elinux wiki 

http://elinux.org/Beagleboard:BeagleBoneBlack

For the boot procedure, you should look up this: 

https://github.com/auselen/down-to-the-bone  
(I was not able to boot from anything else than USB tftp/bootp as of now, but if you found how, HMU.)

Raspberry Pi related baremetal from Dwelch67, loads of examples 

https://github.com/dwelch67/raspberrypi


*keep in mind, all those examples are loaded via USB (tftp/boop) in the on-chip RAM, not in the external DDR as it does when working with Code Composer Studio, UNTIL sample 08_test_CXX where it IS supposed to run from 0x8000000.


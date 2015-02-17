01_Blinker
====================

This example was the first one, to see if my boot procedure was working. I just wanted to blink the onboard leds without any fuss. it is inspired by Ali Utku Selen (https://github.com/auselen under GNU GPL) in the down-to-the-bone repository. 

====================
A few important points here:
* the *_start* symbol **must** be the entrypoint
* for the simplest peripheral access, i used assembly (namely *PUT32* and *GET32*)
* the *memmap.ld* isn't complete in this example, as the origin is set to *0x0*
* the copy target in the makefile is only specific to my boot setup (dnsmasq loading spl.boot)
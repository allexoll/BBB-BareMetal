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

## Loading Bare Metal App via U-Boot
This section guides you to configuring U-Boot for loading a bare metal application via SD Card into the external RAM as an alternative to USB (tftp/boop) method.

# Explanation
U-Boot's uEnv.txt file specifies how the board will boot and, in the case of a bare metal 
application, specifies what image to load. However, we don't want to have to 
boot to Linux on the target each time we want to change the file to load, so, we tell U-Boot via uEnv.txt 
to load your bare metal application binary (`your_application.bin`, ` spl.boot`, etc, ...).

1. **Prepare the SD Card:**
   - Format your microSD card using FAT32 filesystem.
   - Download and copy U-Boot bootloader binary (`MLO` and `u-boot.img`) onto the SD card boot directory.
   - Place your bare metal application binary (`your_application.bin`, ` spl.boot`, etc, ...) on the SD card.

2. **Create your uEnv.txt file:**
   - On your host, create a text file called uEnv.txt somewhere which can hold the UBoot command. It’s easier
     to edit this way in a text editor than inside the UBoot prompt.
   - Copy the `uEnv.txt` file onto the SD card boot directory. This file should contain:
     ```
     uenvcmd=setenv loadaddr 0x80000000; fatload mmc 1:0 ${loadaddr} spl.boot; echo *** Booting 
     to BareMetal ***;go ${loadaddr};
     ```
   - Save and eject the SD card.

3. **Boot from SD Card:**
   - Insert the prepared SD card into the BeagleBone Black.
   - Push the SD Card boot button(`SW2`) and then Power on the board.
   - U-Boot will load and execute `MLO`, then `u-boot.img` from the SD card.
   - You should see U-Boot prompt:
     ```
      Boot 2018.01-00002-g9aa111a004 (Jan 20 2018 - 12:45:29 -0600), Build: jenkinsgithub_Bootloader-Builder-32
      CPU : AM335X-GP rev 2.1
      I2C: ready
      DRAM: 512 MiB
      No match for driver 'omap_hsmmc'
      No match for driver 'omap_hsmmc'
      Some drivers were not found
      Reset Source: Global external warm reset has occurred.
      Reset Source: watchdog reset has occurred.
      Reset Source: Global warm SW reset has occurred.
      Reset Source: Power-on reset has occurred.
      MMC: OMAP SD/MMC: 0, OMAP SD/MMC: 1
      Using default environment
      Board: BeagleBone Black
      <ethaddr> not set. Validating first E-fuse MAC
      BeagleBone Black:
      Model: SeeedStudio BeagleBone Green:
      debug: process_cape_part_number:[BB-BONE-ZEN-01]
      debug: process_cape_part_number:[42422D424F4E452D5A454E2D3031]
       ....
      Scanning mmc 1:1...
      gpio: pin 56 (gpio 56) value is 0
      gpio: pin 55 (gpio 55) value is 0
      gpio: pin 54 (gpio 54) value is 0
      gpio: pin 53 (gpio 53) value is 1
      switch to partitions #0, OK
      mmc1(part 0) is current device
      gpio: pin 54 (gpio 54) value is 1
      Checking for: /uEnv.txt ...
      286 bytes read in 27 ms (9.8 KiB/s)
      gpio: pin 55 (gpio 55) value is 1
      Loaded environment from /uEnv.txt
      Importing environment from mmc ...
      Checking if uenvcmd is set ...
      gpio: pin 56 (gpio 56) value is 1
      Running uenvcmd ...
      using musb-hdrc, OUT ep1out IN ep1in STATUS ep2in
      MAC b0:d5:cc:47:00:d5
      HOST MAC de:ad:be:af:00:00
      RNDIS ready
      musb-hdrc: peripheral reset irq lost!
      high speed config #2: 2 mA, Ethernet Gadget, using RNDIS
      USB RNDIS network up!
      Using usb_ether device
      TFTP from server 192.168.7.1; our IP address is 192.168.7.2
      Filename '/home/brian/cmpt433/public/baremetal/download.bin'.
      Load address: 0x80000000
      Loading: *##
       100.6 KiB/s
      done
      Bytes transferred = 8496 (2130 hex)
      *** Booting to BareMetal ***
      ## Starting application at 0x80000000 ...
      StarterWare AM335X UART Interrupt appl
     ```

     

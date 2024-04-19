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

### Explanation
U-Boot's uEnv.txt file specifies how the board will boot and, in the case of a bare metal 
application, specifies what image to load. However, we don't want to have to 
boot to Linux on the target each time we want to change the file to load, so, we tell U-Boot via uEnv.txt 
to load your bare metal application binary (`your_application.bin`, ` spl.boot`, `etc`).

1. **Prepare the SD Card:**
   - Format your microSD card using FAT32 filesystem.
   - Download and copy the U-Boot bootloader binary (MLO and u-boot.img) to the SD card's boot directory,
       (MLO and u-boot.img prebuilt images available in the [Uboot](Uboot) folder).
   - Place your bare metal application binary (`your_application.bin`, ` spl.boot`, `etc`) on the SD card.

2. **Create your uEnv.txt file:**
   - On your host, create a text file called uEnv.txt somewhere which can hold the UBoot command. It’s easier
     to edit this way in a text editor than inside the UBoot prompt.
   - Copy the `uEnv.txt` file onto the SD card boot directory. This file should contain:
     ```
     uenvcmd=setenv loadaddr 0x80000000; fatload mmc 0 ${loadaddr} spl.boot; echo *** Booting 
     to BareMetal ***;go ${loadaddr};
     ```
   - Save and eject the SD card.

3. **Boot from SD Card:**
   - Insert the prepared SD card into the BeagleBone Black.
   - Push the SD Card boot button(`S2`) and then Power on the board.
   - U-Boot will load and execute `MLO`, then `u-boot.img` from the SD card.
   - You should see U-Boot prompt:
     ```
    U-Boot SPL 2017.05-rc2 (May 02 2017 - 08:53:40)
    Trying to boot from MMC1
    *** Warning - bad CRC, using default environment

    reading u-boot.img
    reading u-boot.img


    U-Boot 2017.05-rc2 (May 02 2017 - 08:53:40 +0530)

    CPU  : AM335X-GP rev 2.1
    I2C:   ready
    DRAM:  512 MiB
    MMC:   OMAP SD/MMC: 0, OMAP SD/MMC: 1
    *** Warning - bad CRC, using default environment

    <ethaddr> not set. Validating first E-fuse MAC
    Net:   cpsw, usb_ether
    Press SPACE to abort autoboot in 2 seconds
    switch to partitions #0, OK
    mmc0 is current device
    SD/MMC found on device 0
    reading boot.scr
    ** Unable to read file boot.scr **
    reading uEnv.txt
    122 bytes read in 6 ms (19.5 KiB/s)
    Loaded env from uEnv.txt
    Importing environment from mmc0 ...
    Running uenvcmd ...
    reading spl.boot
    4750 bytes read in 8 ms (579.1 KiB/s)
    *** Booting to BareMetal ***
    ## Starting application at 0x80000000 ...
    UART0 Initialized...
     ```

     

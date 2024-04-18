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

## SD Card Boot Procedure
If you want to boot your bare metal aplications from the SD Card into the external ram, you should follow these steps:

1. **Prepare the SD Card:**
   - Format your microSD card using FAT32 filesystem.
   - Download and copy U-Boot bootloader binary (`MLO` and `u-boot.img`) onto the SD card root directory.
   - Place your bare metal application binary (`your_application.bin`) on the SD card.

2. **Configure U-Boot:**
   - Connect your BeagleBone Black to a computer via USB cable.
   - Power on the board while holding down the "Boot" button.
   - The board will enter USB boot mode, and you will see a new drive named "BEAGLEBONE".
   - Copy the `uEnv.txt` file onto the SD card root directory. This file should contain:
     ```
     mmcdev=1
     bootpart=1:2
     mmcroot=/dev/mmcblk1p2 ro
     optargs=quiet drm.debug=7
     capemgr.disable_partno=
     ```
   - Save and eject the SD card.

3. **Boot from SD Card:**
   - Insert the prepared SD card into the BeagleBone Black.
   - Power on the board.
   - U-Boot will load and execute `MLO`, then `u-boot.img` from the SD card.
   - You should see U-Boot prompt.

   - **On Ubuntu Linux**:
     - Open a terminal window.
     - Use the `lsblk` command to identify the device node of your SD card (e.g., `/dev/sdX`, where X is a letter representing your SD card).
     - Unmount any partitions on the SD card using the `umount` command (e.g., `sudo umount /dev/sdX1`).
     - Execute the following commands to copy your application binary to the SD card:
       ```
       sudo cp your_application.bin /media/$USER/BEAGLEBONE
       sudo sync
       ```
     - Safely eject the SD card.
     

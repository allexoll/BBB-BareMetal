09_USB_Bootloader
==============

  09_USB_Bootloader: This example implements a USB DFU bootloader. the device is connected via the mini USB port on the board (USB0) and 
  enumerates itself as a DFU capable device. you then need to use dfu-util (http://dfu-util.sourceforge.net/) to download your code to the device.
  The code is launched from 0x80000000, like it was in 07_Bootloader. This bootloader is about 20 times faster than the previous one, which was 
  run via UART0.
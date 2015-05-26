10_I2C
==============

 10_i2C: This example implements I2C. a lot of the AM335x I2C-specific are 
 from the Starterware for Sitara processors, from TI ( http://processors.wiki.ti.com/index.php/StarterWare ). 
 Their read & write function were not working for me, so I had to rewrite them almost completely.\n
 First, The I2C0 part gets initialized. I then probe the bus to see which addresses are Ack-ing the 
 request. normaly, you should get (on the Beaglebone black) the addresses 0x48 (TPS65217 chip, which is 
 referenced as addres 0x24 (7bit) in its datasheed), 0x68 (TDA19988 chip, CEC core), and 0xa0 (24LC32A, 
 the EEPROM chip). I curently have no idea why the HDMI core of the TDA19988 does not answer to its 
 address (0xE0), and as the chip is under IP, that might be hard to find an answer...\n
 Secondly, I set the read pointer on the EEPROM chip to 0x000. I then read the EEPROM_ID 
 structure from it (referenced in http://processors.wiki.ti.com/index.php/AM335x_Starter_Kit_ID_Memory_Programming ) 
 and print it.\n
 A few notes, the read/write routines did not work after being used aprox. 32 times. the solution 
 I found was reinitialising the I2C part at the begining of each read/write operation. I still 
 can't figure out what's causing this bug.\n
 
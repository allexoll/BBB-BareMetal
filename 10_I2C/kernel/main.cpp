/**
 * @file main.c
 * @author Alexis Marquet
 * @date 26 May 2015
 * @brief contains the main application
 **/


/**
 * @mainpage
 * 10_i2C: This example implements I2C. a lot of the AM335x I2C-specific are 
 * from the Starterware for Sitara processors, from TI ( http://processors.wiki.ti.com/index.php/StarterWare ). 
 * Their read & write function were not working for me, so I had to rewrite them almost completely.\n
 *
 * First, The I2C0 part gets initialized. I then probe the bus to see which addresses are Ack-ing the 
 * request. normaly, you should get (on the Beaglebone black) the addresses 0x48 (TPS65217 chip, which is 
 * referenced as addres 0x24 (7bit) in its datasheed), 0x68 (TDA19988 chip, CEC core), and 0xa0 (24LC32A, 
 * the EEPROM chip). I curently have no idea why the HDMI core of the TDA19988 does not answer to its 
 * address (0xE0), and as the chip is under IP, that might be hard to find an answer...\n
 *
 * Secondly, I set the read pointer on the EEPROM chip to 0x000. I then read the EEPROM_ID 
 * structure from it (referenced in http://processors.wiki.ti.com/index.php/AM335x_Starter_Kit_ID_Memory_Programming ) 
 * and print it.\n
 *
 * A few notes, the read/write routines did not work after being used aprox. 32 times. the solution 
 * I found was reinitialising the I2C part at the begining of each read/write operation. I still 
 * can't figure out what's causing this bug.\n
 **/

extern "C" {
#include <stdint.h>
#include <stdio.h>
#include "../core/llma.h"
#include "../proc/clock_module.h"
#include "../proc/control_module.h"
#include "../proc/pad.h"
#include "../proc/interrupt.h"
#include "../board/LED.h"
}
#include "../proc/I2C.h"
#include "../board/EEPROM.h"
#include <vector>
#include <cstring>
#include <iostream>


using namespace std;

int main ()
{
   struct EEPROM_ID eepromID = {0,"","","",""};

   I2C_initI2C(I2C0, 100000);
   
   cout << endl;
   
   cout << "Starting I2C0 bus probing..." << endl;
   
   vector <uint8_t> availableDevices = I2C_busProbe(I2C0);
   
   cout << "Done probing bus, "<< availableDevices.size() << " active devices:" << endl;
   for(int i = 0; i < availableDevices.size(); i++)
   {
      cout << "Device at 0x" << hex << (uint32_t) availableDevices.at(i) << "\n";
   }
   
   cout << endl;
   
   cout << "reading data on EEPROM" << endl;
   EEPROM_read(0x000, (uint8_t*)&eepromID, sizeof(eepromID));

   
   // the strings are not null-terminated, so you need to specify the length
   // of the ascii string using stream.write method
   cout << "Magic number = 0x" << hex << eepromID.magic << endl;
   cout << "Board name = ";
   cout.write((const char*)eepromID.boardName,8);
   cout << endl;
   cout << "Version = ";
   cout.write((const char*)eepromID.version,4);
   cout << endl;
   cout << "serialNumber = ";
   cout.write((const char*)eepromID.serialNumber,12);
   cout << endl;

   for(;;){}
   return 0;
}

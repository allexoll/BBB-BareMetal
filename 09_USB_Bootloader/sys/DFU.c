/**
 * @file USB.c
 * @author Alexis Marquet
 * @date 21 May 2015
 * @brief Types and declarations for DFU module. reference: UNIVERSAL SERIAL BUS, DEVICE CLASS SPECIFICATION FOR DEVICE FIRMWARE UPGRADE.pdf V1.1
 *       The DFU class is a bit different than the other USB classes, as it communicates via ENDP0 (control endpoint) instead of a
 *       dedicated endpoint. the code in DFU.* and USB.* is very linked to each other.
 TODO: finish documenting this section...
 **/

#include <stdint.h>
#include "../core/llma.h"
#include "../proc/USB.h"
#include "../board/LED.h"
#include "DFU.h"
#include "types.h"


#ifdef DFU_DEBUG
#define DFU_DBG printf
#else
#define DFU_DBG dummy
#endif
enum USBDFU_State DFU_state = dfuIDLE;
bool DFU_update_ready = false;

const struct USBDFUFunctionalDescriptor DFUFunc =
{
   .bLength = sizeof(struct USBDFUFunctionalDescriptor), // should be 9
   .bDescriptorType = Descriptor_Type_DFU_FUNCTIONAL,  // DFU functional descriptor
   .bmAttributes = 0b00000001,   // see bitmap in DFU FUNCTIONAL
   .wDetachTimeOut = 15000,  // revert ton normal operation after 300ms?
   .wTransferSize = 64, // max endp 0 packet size
   .bcdDFUVersion = 0x0101 // DFU 1.01?
};

void USB_Setup_Class(struct USBSetupPacket s)
{
   struct USBDFU_GETSTATE_Answer dfu_get_status_answer;
   static uint32_t dfu_gotten = 0;
   static uint32_t prev_blc = 0;
   switch(s.bmRequestType & USB_Setup_Direction_Mask)
   {
      case Direction_HOST_TO_DEVICE:
         DFU_DBG("host->dev, ");
         switch(s.bRequest)
      {
         case 0x00:	// DFU_DETACH
            DFU_DBG("DFU_DETACH, ");
            break;
         case 0x01:	// DFU_DNLOAD
            DFU_DBG("DFU_DNLOAD, ");
            DFU_DBG("block num 0x%X, len = 0x%X", s.wValue, s.wLength);
            if(prev_blc != (s.wValue-1) && (prev_blc != 0))
            {
               printf("error: blc = 0x%X,prev = 0x%X, l= 0x%X\n",s.wValue,prev_blc,s.wLength);
            }
            prev_blc = s.wValue;
            LED_setValue(s.wValue>>7);
            if(s.wLength == 0)
            {
               DFU_state = dfuMANIFEST_WAIT_RESET;
               DFU_DBG("\nBranch to 0x80000000\n");
               DFU_update_ready = true;
            }
            else
            {
               DFU_state = dfuDNLOAD_IDLE;
               USB_getBuffer((uint8_t*)0x80000000+dfu_gotten,s.wLength,0);
               dfu_gotten += s.wLength;
            }
            break;
         case 0x04:	// DFU_CLRSTATUS
            DFU_DBG("DFU_CLRSTATUS, ");
            break;
         case 0x06:	// DFU_ABORT
            DFU_DBG("DFU_ABORT, ");
            DFU_state = dfuIDLE;
            break;
      }
         break;
      case Direction_DEVICE_TO_HOST:
         DFU_DBG("dev->host, ");
         switch(s.bRequest)
      {
         case 0x02:	// DFU_UPLOAD
            DFU_DBG("DFU_UPLOAD, ");
            break;
         case 0x03:	// DFU_GETSTATUS
            DFU_DBG("DFU_GETSTATUS, ");
            dfu_get_status_answer.bStatus = 0x00;	// no error
            dfu_get_status_answer.bwPollTimeout[0] = 0x01;
            dfu_get_status_answer.bwPollTimeout[1] = 0x00;
            dfu_get_status_answer.bwPollTimeout[2] = 0x00;
            dfu_get_status_answer.bState = DFU_state;
            dfu_get_status_answer.iString = 0x00;
            USB_putBuffer((uint8_t*) &dfu_get_status_answer,sizeof(struct USBDFU_GETSTATE_Answer),0);
            EP0_TX_routine();
            break;
         case 0x05:	// DFU_GETSTATE
            DFU_DBG("DFU_GETSTATE, ");
            break;
      }
         break;
   }
   DFU_DBG("\n");
}
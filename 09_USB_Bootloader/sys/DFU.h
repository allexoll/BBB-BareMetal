/**
 * @file DFU.h
 * @author Alexis Marquet
 * @date 21 May 2015
 * @brief Types and declarations for DFU module. reference: UNIVERSAL SERIAL BUS, DEVICE CLASS SPECIFICATION FOR DEVICE FIRMWARE UPGRADE.pdf V1.1
 *       The DFU class is a bit different than the other USB classes, as it communicates via ENDP0 (control endpoint) instead of a 
 *       dedicated endpoint. the code in DFU.* and USB.* is very linked to each other.
 **/

#ifndef ____DFU__
#define ____DFU__

#include <stdint.h>
#include "../proc/USB.h"
#include "types.h"


/**
 * @brief uncomment this line to print DFU Debug information
 **/
// #define DFU_DEBUG


/**
 * @brief DFU functional Descriptor, USB_DFU 4.1.3
 **/
struct USBDFUFunctionalDescriptor
{
#pragma pack(1)
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint8_t bmAttributes;
   uint16_t wDetachTimeOut;
   uint16_t wTransferSize;
   uint16_t bcdDFUVersion;
};


/** 
 * @brief DFU GetState request answer, USB_DFU 6.1.2
 **/
struct USBDFU_GETSTATE_Answer
{
#pragma pack(1)
   uint8_t bStatus;
   uint8_t bwPollTimeout[3];
   uint8_t bState;
   uint8_t iString;
};


/**
 * @brief DFU state machine, USB_DFU 6.1.2
 **/
enum USBDFU_State
{
   appIDLE = 0x00,
   appDETACH = 0x01,
   dfuIDLE = 0x02,
   dfuDNLOAD_SYNC = 0x03,
   dfuDNBUSY = 0x04,
   dfuDNLOAD_IDLE = 0x05,
   dfuMANIFEST_SYNC = 0x06,
   dfuMANIFEST = 0x07,
   dfuMANIFEST_WAIT_RESET = 0x08,
   dfuUPLOAD_IDLE = 0x09,
   dfuERROR = 0x0A
};

const struct USBDFUFunctionalDescriptor DFUFunc;

/**
 * @brief boolead is true when DFU has downloader all the firmware and put it in the ram (0x80000000).
 **/
bool DFU_update_ready;

/**
 * @fn void USB_Setup_Class(struct USBSetupPacket s)
 * @brief            This function is called from the ENDP0 interrupt. it deals with all the DFU class-specific setup packets
 * @param[in]  s     The setup packet containing the DFU specific request
 **/
void USB_Setup_Class(struct USBSetupPacket s);

#endif /* defined(____DFU__) */

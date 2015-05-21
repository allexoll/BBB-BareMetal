/**
 * @file USB.h
 * @author Alexis Marquet
 * @date 21 May 2015
 * @brief Types and declarations for the MUSBHDRC module, reference: AM335x TRM 16, and TMS320DM36x Digital Media System-on-Chip (DMSoC) Universal Serial Bus (USB).
 **/

#ifndef __USB_H
#define __USB_H

#include <stdint.h>
#include "interrupt.h"
#include "../sys/types.h"


/**
 * @brief uncomment this line to print USB debug information
 **/
// #define USB_DEBUG


/**
 * @brief enum describing Descriptor types (bDescriptorType)
 **/
enum USBDescriptorType
{
   Descriptor_Type_DEVICE = 0x01,
   Descriptor_Type_CONFIGURATION = 0x02,
   Descriptor_Type_STRING = 0x03,
   Descriptor_Type_INTERFACE = 0x04,
   Descriptor_Type_ENDPOINT = 0x05,
   Descriptor_Type_DEVICE_QUALIFIER = 0x06,
   Descriptor_Type_OTHER_SPEED_CONFIG = 0x07,
   
   Descriptor_Type_DFU_FUNCTIONAL = 0x21
};


/**
 * @brief Direction of setup packet (bmRequestType)
 **/
#define USB_Setup_Direction_Mask (0b10000000)
enum USB_Setup_Direction
{
   Direction_HOST_TO_DEVICE = 0x00,
   Direction_DEVICE_TO_HOST = 0x80
};

/**
 * @brief type of setup packet   (bmRequestType)
 **/
#define USB_Setup_Type_Mask (0b01100000)
enum USB_Setup_Type
{
   Setup_Type_STANDARD = 0b00000000,
   Setup_Type_CLASS = 0b00100000,
   Setup_Type_VENDOR = 0b01000000,
   Setup_Type_RESERVED = 0b01100000
};

/**
 * @brief recipient of setup packet (bmRequestType)
 **/
#define USB_Setup_Recipient_Mask (0b00011111)
enum USB_Setup_Recipient
{
   Setup_Recipient_DEVICE =    0b00000000,
   Setup_Recipient_INTERFACE = 0b00000001,
   Setup_Recipient_ENDPOINT =  0b00000010,
   Setup_Recipient_OTHER =     0b00000011
};

/**
 * @ request type of setup packet (bRequest)
 **/
enum USB_Request_Type
{
   GET_STATUS = 0x00,
   CLEAR_FEATURE = 0x01,
   SET_FEATURE = 0x03,
   SET_ADDRESS = 0x05,
   GET_DESCRIPTOR = 0x06,
   SET_DESCRIPTOR = 0x07,
   GET_CONFIGURATION = 0x08,
   SET_CONFIGURATION = 0x09,
   GET_INTERFACE = 0x0A,
   SET_INTERFACE = 0x0B,
   SYNCH_FRAME = 0x0C
};

/**
 * @brief setup packet structure
 **/
struct USBSetupPacket
{
#pragma pack(1)
   uint8_t bmRequestType;
   uint8_t bRequest;
   uint16_t wValue;
   uint16_t wIndex;
   uint16_t wLength;
};

/**
 * @brief descritor header structure
 **/
struct USBDescriptorHeader
{
#pragma pack(1)
   uint8_t bLength;
   uint8_t bDescriptorType;
};

/**
 * @brief Device Descriptor structure
 **/
struct USBDeviceDescriptor
{
#pragma pack(1)
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint16_t bcdUSB;
   uint8_t bDeviceClass;
   uint8_t bDeviceSubClass;
   uint8_t bDeviceProtocol;
   uint8_t bMaxPacketSize;
   uint16_t idVendor;
   uint16_t idProduct;
   uint16_t bcdDevice;
   uint8_t iManufacturer;
   uint8_t iProduct;
   uint8_t iSerialNumber;
   uint8_t bNumConfigurations;
};

/**
 * @brief Configuration Descriptor Structure
 **/
struct USBConfigurationDescriptor
{
#pragma pack(1)
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint16_t wTotalLength;
   uint8_t bNumInterfaces;
   uint8_t bConfigurationValue;
   uint8_t iConfiguration;
   uint8_t bmAttributes;
   uint8_t bMaxPower;
};

/**
 * @brief Interface Descriptor Structure
 **/
struct USBInterfaceDescriptor
{
#pragma pack(1)
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint8_t bInterfaceNumber;
   uint8_t bAlternateSetting;
   uint8_t bNumEndpoints;
   uint8_t bInterfaceClass;
   uint8_t bInterfaceSubClass;
   uint8_t bInterfaceProtocol;
   uint8_t iInterface;
};


/**
 * @brief Endpoint Descriptor structure
 **/
struct USBEndpointDescriptor
{
#pragma pack(1)
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint8_t bEndpointAddress;
   uint8_t bmAttributes;
   uint16_t wMaxPacketSize;
   uint8_t bInterval;
};

/**
 * @ String Descriptor Structure. bString is a UTF16-LE encoded String except for string descriptor 0, which is a language code string
 **/
struct USBStringDescriptor
{
#pragma pack(4)
   struct USBDescriptorHeader head;
   uint8_t *bString;
};

/**
 * @ DeviceQualifier Descriptor, sometimes asked for when using USB2.0
 **/
struct USBDeviceQualifier
{
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint16_t bcdUSB;
   uint8_t bDeviceClass;
   uint8_t bDeviceSubClass;
   uint8_t bDeviceProtocol;
   uint8_t bMaxPacketSize0;
   uint8_t bNumConfigurations;
   uint8_t bReserved;
};

/**
 * @fn void USB_init()
 * @brief   Initialize the USB module, and only returns when device enumeration is done
 **/
void USB_init();

/**
 * @fn void USB_putBuffer(uint8_t* src, uint32_t len,uint8_t endp)
 * @brief               put [len] bytes in endpoint [endp] out buffer (software, not hardware)
 * @param[in]  src      address of the source buffer to copy
 * @param[in]  len      length in bytes of [src]
 * @param[in]  endp     endpoint number
 **/
void USB_putBuffer(uint8_t* src, uint32_t len,uint8_t endp);

/**
 * @fn void EP0_TX_routine()
 * @brief               Use this routine to initiate transfer after using the USB_putBuffer function
 **/
void EP0_TX_routine();


/**
 * @fn void USB_getBuffer(uint8_t *dst, uint32_t len, uint8_t endp)
 * @brief               Use this function to initiate OUT packet. example with DFU: when the DFU_DNLOAD request is recieved in the setup packet,
                        this function is called to indicate where the data should be put when it is recieved.
 **/
void USB_getBuffer(uint8_t *dst, uint32_t len, uint8_t endp);


#endif // __USB_H



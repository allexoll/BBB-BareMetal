/**
 * @file USB.c
 * @author Alexis Marquet
 * @date 21 May 2015
 * @brief Types and definition for the MUSBHDRC module, reference: AM335x TRM 16, and TMS320DM36x Digital Media System-on-Chip (DMSoC) Universal Serial Bus (USB).
 TODO: finish documenting this section...
 **/


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../core/llma.h"
#include "../board/LED.h"
#include "USB.h"
#include "../sys/DFU.h"

#ifdef USB_DEBUG
#define USB_DBG printf
#else
#define USB_DBG   dummy
#endif


// AM335x USB memory map
#define USBSS     (0x47400000)

#define USB0      (0x47401000)
#define USB0_PHY  (0x47401300)
#define USB0_CORE (0x47401400)

#define USB1      (0x47401800)
#define USB1_PHY  (0x47401B00)
#define USB1_CORE (0x47401C00)

#define USB_CPPI_DMA_CONTROLLER  (0x47402000)
#define USB_CPPI_DMA_SCHEDULER   (0x47403000)
#define USB_QUEUE_MANAGER        (0x47404000)


// AM335x USBSS register map
enum USBSS_
{
   REVREG            =  0x00,
   SYSCONFIG         =  0x10,
   IRQSTATSTRAW      =  0x24,
   IRQSTAT           =  0x28,
   IRQENABLER        =  0x2C,
   IRQCLEARR         =  0x30,
   
   IRQDMATHOLDTX00   =  0x100,
   IRQDMATHOLDTX01   =  0x104,
   IRQDMATHOLDTX02   =  0x108,
   IRQDMATHOLDTX03   =  0x10C,
   
   IRQDMATHOLDRX00   =  0x110,
   IRQDMATHOLDRX01   =  0x114,
   IRQDMATHOLDRX02   =  0x118,
   IRQDMATHOLDRX03   =  0x11C,
   
   IRQDMATHOLDTX10   =  0x120,
   IRQDMATHOLDTX11   =  0x124,
   IRQDMATHOLDTX12   =  0x128,
   IRQDMATHOLDTX13   =  0x12C,
   
   IRQDMATHOLDRX10   =  0x130,
   IRQDMATHOLDRX11   =  0x134,
   IRQDMATHOLDRX12   =  0x138,
   IRQDMATHOLDRX13   =  0x13C,
   
   IRQDMAENABLE0     =  0x140,
   IRQDMAENABLE1     =  0x144,
   
   IRQFRAMETHOLDTX00 =  0x200,
   IRQFRAMETHOLDTX01 =  0x204,
   IRQFRAMETHOLDTX02 =  0x208,
   IRQFRAMETHOLDTX03 =  0x20C,
   
   IRQFRAMETHOLDRX00 =  0x210,
   IRQFRAMETHOLDRX01 =  0x214,
   IRQFRAMETHOLDRX02 =  0x218,
   IRQFRAMETHOLDRX03 =  0x21C,
   
   IRQFRAMETHOLDTX10 =  0x220,
   IRQFRAMETHOLDTX11 =  0x224,
   IRQFRAMETHOLDTX12 =  0x228,
   IRQFRAMETHOLDTX13 =  0x22C,
   
   IRQFRAMETHOLDRX10 =  0x230,
   IRQFRAMETHOLDRX11 =  0x234,
   IRQFRAMETHOLDRX12 =  0x238,
   IRQFRAMETHOLDRX13 =  0x23C,
   
   IRQFRAMEENABLE0   =  0x240,
   IRQFRAMEENABLE1   =  0x244,
   
};


// AM335x USB_CTRL register map
enum USBx_CRTL
{
   USBxREV           =  0x00,
   USBxCTRL          =  0x14,
   USBxSTAT          =  0x18,
   USBxIRQMSTAT      =  0x20,
   
   USBxIRQSTATRAW0   =  0x28,
   USBxIRQSTATRAW1   =  0x2C,
   
   USBxIRQSTAT0      =  0x30,
   USBxIRQSTAT1      =  0x34,
   
   USBxIRQENABLESET0 =  0x38,
   USBxIRQENABLESET1 =  0x3C,
   
   USBxIRQENABLECLR0 =  0x40,
   USBxIRQENABLECLR1 =  0x44,
   
   USBxTXMODE        =  0x70,
   USBxRXMODE        =  0x74,
   
   USBxGENRNDISEP1   =  0x80,
   USBxGENRNDISEP2   =  0x84,
   USBxGENRNDISEP3   =  0x88,
   USBxGENRNDISEP4   =  0x8C,
   USBxGENRNDISEP5   =  0x90,
   USBxGENRNDISEP6   =  0x94,
   USBxGENRNDISEP7   =  0x98,
   USBxGENRNDISEP8   =  0x9C,
   USBxGENRNDISEP9   =  0xA0,
   USBxGENRNDISEP10  =  0xA4,
   USBxGENRNDISEP11  =  0xA8,
   USBxGENRNDISEP12  =  0xAC,
   USBxGENRNDISEP13  =  0xB0,
   USBxGENRNDISEP14  =  0xB4,
   USBxGENRNDISEP15  =  0xB8,
   
   USBxAUTOREQ       =  0xD0,
   USBxSRPFIXTIME    =  0xD4,
   USBxTDOWN         =  0xD8,
   
   USBxUTMI          =  0xE0,
   USBxMGCUTMILB     =  0xE4,
   USBxMODE          =  0xE8
};

// AM335x USBx_PHY register map
enum USBx_PHY
{
   Termination_control     =  0x00,
   RX_CALIB                =  0x04,
   DLLHS_2                 =  0x08,
   RX_TEST_2               =  0x0C,
   
   CHRG_DET                =  0x14,
   PWR_CNTL                =  0x18,
   UTMI_INTERFACE_CNTL_1   =  0x1C,
   UTMI_INTERFACE_CNTL_2   =  0x20,
   BIST                    =  0x24,
   BIST_CRC                =  0x28,
   CDR_BIST2               =  0x2C,
   GPIO                    =  0x30,
   DLLHS                   =  0x34,
   
   USB2PHYCM_CONFIG        =  0x3C,
   AD_INTERFACE_REG1       =  0x44,
   AD_INTERFACE_REG2       =  0x48,
   AD_INTERFACE_REG3       =  0x4C,
   
   ANA_CONFIG2             =  0x54
};
// USB core register, according to
// MUSBMHDRC REGISTER MAP

// Common USB registers    [0x00 - 0x0F]
#define USB_COMMON	(0x400)
#define FADDR     (0x00)   // 8  , Function address register
#define POWER     (0x01)   // 8  , Power management register
#define INTRTX    (0x02)   // 16 , Interrupt register for Endpoint 0 plus TX Endpoint 1 to 15
#define INTRRX    (0x04)   // 16 , Interrupt register for Rx Endpoint 1 to 15
#define INTRTXE   (0x06)   // 16 , Interrupt enable register for INTRTX
#define INTRRXE   (0x08)   // 16 , Interrupt enable register for INTRRX
#define INTRUSB   (0x0A)   // 8  , Interrupt register for common USB interrupts.
#define INTRUSBE  (0x0B)   // 8  , Interrupt enable register for INTRUSB
#define FRAME     (0x0C)   // 16 , Frame number
#define INDEX     (0x0E)   // 8  , Index register dor selecting the endpoint status and control registers.
#define TESTMODE  (0x0F)   // 8  , Enables the USB 2.0 test modes.

// Indexed registers - peripheral mode [0x10 - 0x1F]
// (control status register for endpoint selected by the index register when DevCtl.D2 = 0)

#define TXMAXP    (0x10)   // 16 , Maximum Packet size for peripheral TX endpoint.
//      (INDEX register set to select Endpoint 1 - 15 only)
#define CSR0      (0x12)   // 16 , Control Status register for Endpoint 0.
//      (INDEX register se to select Endpoint 0)
#define TXCSR     (0x12)   // 16 , Control Status register for peripheral TX endpoint.
//      (INDEX register set to select Endpoints 1 - 15)
#define RXMAXP    (0x14)   // 16 , Maximum Packet size for peripheral Rx endpoint.
//      (INDEX register set to select Endpoint 1 - 15 only)
#define RXCSR     (0x16)   // 16 , Control Sttus register for peripheral Rx endpoint.
//      (INDEX register set to select Endpoints 1 - 15)
#define COUNT0    (0x18)   // 16 , Number of received bytes in Endpoint 0 FIFO.
//      (INDEX register set to select Endpoint 0)
#define RXCOUNT   (0x18)   // 16 , Number of byte to be read from peripheral Rx endpoint FIFO.
//      (INDEX register set to select Endpoint 1 - 15)
#define CONFIGDATA (0x1F)  // 8  , Returns details of core configuration.
//      (INDEX register set to select Endpoint 0.)


// TODO: implement register map, indexed register for HOST mode


// FIFOs [0x20 - 0x5F]
#define FIFOx     (0x20)   // 512, FIFOs for Endpoints 0 - 15

// Additional Control & Configuration Registers [0x60 - 0x7F]

#define DEVCTL    (0x60)   // 8  , OTG device control register
#define MISC      (0x61)   // 8  , Miscellaneous register
#define TXFIFOSZ  (0x62)   // 8  , TX Endpoint FIFO size
#define RXFIFOSZ  (0x63)   // 8  , RX Endpoint FIFO size
#define TXFIFOADD (0x64)   // 16 , TX Endpoint FIFO address
#define RXFIFOADD (0x66)   // 16 , RX Endpoint FIFO address
#define VCTRL     (0x68)   // 32 , UTMI+PHY Vendor register
#define EPINFO    (0x78)   // 8  , Information about number of TX and RX endpoints.
#define RAMINFO   (0x79)   // 8  , Information about the width of the ram and the number of DMA channels.
#define LINKINFO  (0x7A)   // 8  , Information about the delays to be applied
#define VPLEN     (0x7B)   // 8  , Duration of the VBus pulsing charge
#define HS_EOF1   (0x7C)   // 8  , Time buffer available on High-Speed transactions.
#define FS_EOF1   (0x7D)   // 8  , Time buffer available on Full-Speed transactions.
#define LS_EOF1   (0x7E)   // 8  , Time buffer available on Low-Speed transactions.
#define SOFT_RST  (0x7F)   // 8  , Soft Reset.


// TODO: implement register map, targer address register (HOST only)


// TODO: implement register map, Extended registers if DMA >= 1 channel


// Extended registers  [0x300 - 0x348]
#define RQPKTCOUNT(ENDp)   (0x300+4*(ENDp))  // 32*15, Number of requested packet for Receive Endpoint ENDp.
//      (Endpoint 1 - 15 only)
#define RXDPKTBUFDIS       (0x340)  // 16 , Double Packet buffer disable register for RX Endpoint 1 to 15
#define TXDPKTBUFDIS       (0x342)  // 16 , Double Packet buffer disable register for TX Endpoint 1 to 15
#define C_T_UCH            (0x344)  // 16 , This register sets the chirp timeout timer
#define C_T_HSRTN          (0x346)  // 16 , This register sets the delay from the end of High-Speed resume
//      signaling to enable UTM normal operating mode.
#define C_T_HSBT           (0x348)  // 8  , This register specifies the value added to the minimum
//      High-Speed Timeout period (736 bit times) in increments
//      of 64 High-Speed bit times.



static void USB0_ENDP0Handler();
enum USB_CONFIG_STATE
{
   DEFAULT,
   ADDRESSED,
   CONFIGURED
};
enum USB_STATE
{
   IDLE,
   RX,
   TX
};

const struct USBDeviceDescriptor dev[] =
{
   {
      .bLength = sizeof(struct USBDeviceDescriptor),
      .bDescriptorType = Descriptor_Type_DEVICE,   // device descriptor
      .bcdUSB = 0x0200, // USB 1.1
      .bDeviceClass = 0,   // each interface is its own class
      .bDeviceSubClass = 0,   // ?
      .bDeviceProtocol = 0,   // ?
      .bMaxPacketSize = 64,   // max packet size for endpoint 0
      .idVendor = 0x0451,  // ?
      .idProduct = 0xBEEF, // random
      .bcdDevice = 0x0001, // ?
      .iManufacturer = 0x01,  // manufacturer string descriptor index
      .iProduct = 0x02,    // product string descriptor index
      .iSerialNumber = 0x03,  // serial number string descriptor
      .bNumConfigurations = 1   // only one configuration
   }
};
const struct USBConfigurationDescriptor conf[] =
{
   {
      .bLength = 9,	// length
      .bDescriptorType = Descriptor_Type_CONFIGURATION,	// configuration descriptor
      .wTotalLength = sizeof(struct USBConfigurationDescriptor)+sizeof(struct USBInterfaceDescriptor),
      .bNumInterfaces = 1,	// one interface;
      .bConfigurationValue = 1,	// configuration number 1
      .iConfiguration = 0,	// no string
      .bmAttributes = 0b10000000,   // not self powered
      .bMaxPower = 250 // 500Ma
   }
};
const struct USBInterfaceDescriptor interface[] =
{
   {
      // DFU subclass interface descriptor, refer to the USB DFU subclass spec from USB-IF
      .bLength = sizeof(struct USBInterfaceDescriptor),   // should be 9
      .bDescriptorType = Descriptor_Type_INTERFACE, // interface descriptor
      .bInterfaceNumber = 0,  // interface number 0
      .bAlternateSetting = 0,
      .bNumEndpoints = 0,  // DFU uses the control pipe (EP0)
      .bInterfaceClass = 0xFE,   // Application specific Class code
      .bInterfaceSubClass = 0x01,   // Device firmware upgrade code
      .bInterfaceProtocol = 0x02,   // runtime protocol
      .iInterface = 0x00     // interface string descriptor
   }
};

const struct USBDeviceQualifier devQual[] =
{
   {
      .bLength = sizeof(struct USBDeviceQualifier),
      .bDescriptorType = Descriptor_Type_DEVICE_QUALIFIER,
      .bcdUSB = 0x0200,
      .bDeviceClass = 0,
      .bDeviceSubClass = 0,
      .bDeviceProtocol = 0,
      .bMaxPacketSize0 = 64,
      .bNumConfigurations = 1,
      .bReserved = 0
   }
};

const char sLangcode[] = {0x09,0x04};   // 0x409? English United States
const char sVendor[] = {'P',0,'A',0,'N',0,'D',0,'A',0,'C',0,'O',0,'R',0,'P',0,}; // PANDACORP
const char sProduct[] = {'B',0,'E',0,'A',0,'G',0,'L',0,'E',0,'S',0,'y',0,'n',0,'t',0,'h',0}; // BEAGLESynth
const char sInterface[] = {'D',0,'F',0,'U',0,'0',0,'1',0};  // DFU

struct USBStringDescriptor stringDesc [] =
{
   {
      .head.bLength = sizeof(sLangcode)+2,
      .head.bDescriptorType = Descriptor_Type_STRING,
      .bString = (uint8_t*) sLangcode
   },
   {
      .head.bLength = sizeof(sVendor)+2,
      .head.bDescriptorType = Descriptor_Type_STRING,
      .bString = (uint8_t*) sVendor
   },
   {
      .head.bLength = sizeof(sProduct)+2,
      .head.bDescriptorType = Descriptor_Type_STRING,
      .bString = (uint8_t*) sProduct
   },
   {
      .head.bLength = sizeof(sInterface)+2,
      .head.bDescriptorType = Descriptor_Type_STRING,
      .bString = (uint8_t*) sInterface
   }
};

enum USB_STATE USB_state_EP0 = IDLE;
enum USB_CONFIG_STATE USB_config_state = DEFAULT;
bool USB_enumerated = false;

uint32_t to_receive = 0;
uint32_t ptr_received = 0;
uint32_t to_send = 0;
uint32_t ptr_send = 0;
uint32_t ptr_write[1] = {0};  // buffer write pointer
uint8_t EP_buf[1][1024];   // endpoint system buffer
uint8_t *EP_get_buffer[1];


int USB_WriteTo(uint8_t *src, uint32_t size, uint8_t endpoint)
{
   USB_DBG("WR 0x%X\n",size);
   for(int i = 0; i < size; i++)
   {
      PUT8(USB0_CORE+FIFOx+(endpoint<<2),src[i]);
   }
   return size;
}
void USB_putBuffer(uint8_t* src, uint32_t len,uint8_t endp)
{
   memcpy(&EP_buf[endp][ptr_write[endp]],src,len);
   ptr_write[endp] += len;
   to_send = ptr_write[endp];
   ptr_send = 0;
}
void EP0_TX_routine()
{
   if((to_send - ptr_send) > 64)
   {
      USB_WriteTo(&(EP_buf[0][ptr_send]),64,0);
      PUT8(USB0_CORE+CSR0,(1<<1)); // set txpckrdy
      ptr_send += 64;
   }
   else
   {
      USB_WriteTo(&(EP_buf[0][ptr_send]),to_send - ptr_send,0);
      PUT8(USB0_CORE+CSR0,(1<<1)|(1<<3)); // set txpckrdy & data end (len <= 64)
      ptr_send = 0;
      to_send = 0;
      ptr_write[0] = 0;
      USB_state_EP0 = IDLE;
   }
}

int USB_ReadFrom(uint8_t *dst, uint32_t size, uint8_t endpoint)
{
   USB_DBG("RD 0x%X\n",size);
   for(int i = 0; i < size; i++)
   {
      dst[i] = GET8(USB0_CORE+FIFOx+(endpoint<<2));
   }
   return size;
}
void USB_getBuffer(uint8_t *dst, uint32_t len, uint8_t endp)
{
   EP_get_buffer[endp] = dst;
   to_receive = len;
   ptr_received = 0;
   USB_state_EP0 = RX;
}
void EP0_RX_routine()
{
   if((GET8(USB0_CORE + CSR0)&0b1) == 0)	// if !RxPktRdy,
   {
      return;
   }
   uint32_t size = GET8(USB0_CORE+COUNT0)&0x7F;
   if(size == 0)
   {
      return;
   }
   if((to_receive - ptr_received) > 64)
   {
      USB_ReadFrom(&(EP_get_buffer[0][ptr_received]),size,0);
      PUT8(USB0_CORE+CSR0,(1<<6));
      ptr_received += size;
   }
   else
   {
      USB_ReadFrom(&(EP_get_buffer[0][ptr_received]),size,0);
      PUT8(USB0_CORE+CSR0,(1<<6)|(1<<3));
      ptr_received = 0;
      to_receive = 0;
      USB_state_EP0 = IDLE;
   }
}


void USBINT0_IRQHandler()
{
   uint8_t intrusb = GET8(USB0_CORE+INTRUSB);
   uint16_t intrtx = GET16(USB0_CORE+INTRTX);
   uint16_t intrrx = GET16(USB0_CORE+INTRRX);
   NVIC_ClearPending(USBINT0_IRQn);
   
   if(intrusb & 0b10)	// resume interrupt
   {
      // resume routine
      USB_DBG("resume\n");
   }
   if(intrusb & 0b1000000)	// session req interrupt
   {
      // session req routine
      USB_DBG("session req\n");
   }
   if(intrusb & 0b10000000)	// Vbus error interrupt
   {
      // Vbus error routine
      USB_DBG("vbus\n");
   }
   if(intrusb & 0b1)	// suspend interrupt
   {
      // suspend routine
      USB_DBG("suspend\n");
   }
   if(intrusb & 0b10000)	// connect interrupt
   {
      // connect routine
      USB_DBG("connect\n");
   }
   if(intrusb & 0b100000)	// disconnect interrupt
   {
      // disconnect routine
      USB_DBG("disconnect\n");
   }
   if(intrusb & 0b100)// reset/babble interrupt
   {
      if(0)	// host mode?
      {
         // babble routine
         USB_DBG("babble\n");
      }
      else
      {
         // reset routine
         USB_DBG("reset\n");
      }
   }
   if(intrusb & 0b1000)	// SOF interrupt
   {
      // SOF routine
      USB_DBG("sof\n");
   }
   if(intrtx & 0b1)	// endpoint 0 interrupt
   {
      // endpoint 0 routine
      //USB_DBG("EP0\n");
      USB0_ENDP0Handler();
   }
   if(intrtx & 0xFFFE)	// Tx endpoint interrupt
   {
      // Tx endpoint routine
      USB_DBG("TX\n");
   }
   if(intrrx & 0xFFFE)	// Rx endpoint interrupt
   {
      // Rx endpoint routine
      USB_DBG("RX\n");
   }
}
void USB_print_setup(struct USBSetupPacket s)
{
   USB_DBG("0x%02X, ",s.bmRequestType);
   if(s.bmRequestType& 0x80)
   {
      USB_DBG("dev->host, ");
   }
   else
   {
      USB_DBG("host->dev, ");
   }
   
   switch(s.bmRequestType & 0x1F)
   {
      case 0: USB_DBG("Device, ");   break;
      case 1: USB_DBG("Interface, ");break;
      case 2: USB_DBG("Endpoint, "); break;
      case 3: USB_DBG("Other, ");    break;
      default:USB_DBG("Reserved, "); break;
   }
   switch (s.bRequest)
   {
      case GET_STATUS:        USB_DBG("GET_STATUS, ");       break;
      case CLEAR_FEATURE:     USB_DBG("CLEAR_FEATURE, ");    break;
      case SET_FEATURE:       USB_DBG("SET_FEATURE, ");      break;
      case SET_ADDRESS:       USB_DBG("SET_ADDRESS, ");      break;
      case GET_DESCRIPTOR:    USB_DBG("GET_DESCRIPTOR, ");   break;
      case SET_DESCRIPTOR:    USB_DBG("SET_DESCRIPTOR, ");   break;
      case GET_CONFIGURATION: USB_DBG("GET_CONFIGURATION, ");   break;
      case SET_CONFIGURATION: USB_DBG("SET_CONFIGURATION, ");   break;
      case GET_INTERFACE:     USB_DBG("GET_INTERFACE, ");    break;
      case SET_INTERFACE:     USB_DBG("SET_INTERFACE, ");    break;
      case SYNCH_FRAME:       USB_DBG("SYNCH_FRAME, ");      break;
      default:                USB_DBG("unrecognized!! = 0x%X, ",s.bRequest);   break;
   }
   USB_DBG("%04hX %04hX %04hX\n",s.wValue, s.wIndex, s.wLength);
}
void USB_getDescriptor(struct USBSetupPacket setup)
{
   uint8_t desc_type = setup.wValue >> 8;
   uint8_t desc_index = setup.wValue & 0xFF;
   switch(desc_type)
   {
      case Descriptor_Type_DEVICE:
         USB_putBuffer((uint8_t*) &dev[0],sizeof(struct USBDeviceDescriptor),0);
         EP0_TX_routine();
         USB_DBG("sent device descriptor");
         break;
      case Descriptor_Type_CONFIGURATION:
         USB_putBuffer((uint8_t*) &conf[0],sizeof(struct USBConfigurationDescriptor),0);
         USB_putBuffer((uint8_t*) &interface[0],sizeof(struct USBInterfaceDescriptor),0);
         EP0_TX_routine();
         USB_DBG("sent conf descriptor, [0x%X]",desc_index);
         break;
      case Descriptor_Type_STRING:
         USB_DBG("sding string descriptor, [0x%X]\n",desc_index);
         USB_putBuffer((uint8_t*) &stringDesc[desc_index],2,0);
         USB_putBuffer((uint8_t*) stringDesc[desc_index].bString,(uint32_t)stringDesc[desc_index].head.bLength-2,0);
         EP0_TX_routine();
         break;
      case Descriptor_Type_INTERFACE:
         USB_putBuffer((uint8_t*) &interface[desc_index],sizeof(struct USBInterfaceDescriptor),0);
         EP0_TX_routine();
         USB_DBG("sent interface descriptor");
         break;
      case Descriptor_Type_ENDPOINT:
         break;
      case Descriptor_Type_DEVICE_QUALIFIER:
         USB_putBuffer((uint8_t*) &devQual[desc_index],sizeof(struct USBDeviceQualifier),0);
         EP0_TX_routine();
         USB_DBG("sent device qualifier descriptor");
         break;
      case Descriptor_Type_OTHER_SPEED_CONFIG:
         break;
      case Descriptor_Type_DFU_FUNCTIONAL:
         USB_putBuffer((uint8_t*) &DFUFunc,sizeof(struct USBDFUFunctionalDescriptor),0);
         EP0_TX_routine();
         USB_DBG("sent DFU functional descriptor");
         break;
   }
}
void USB_Setup_Standard(struct USBSetupPacket s)
{
   switch(s.bmRequestType & USB_Setup_Direction_Mask)
   {
      case Direction_HOST_TO_DEVICE:
         USB_DBG("host->dev, ");
         switch(s.bmRequestType & USB_Setup_Recipient_Mask)
      {
         case Setup_Recipient_DEVICE:
            USB_DBG("Device, ");
            switch(s.bRequest)
         {
            case 0x01:  // CLEAR_FEATURE
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_DBG("CLEAR_FEATURE, ");
               break;
            case 0x03:  // SET_FEATURE
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_DBG("SET_FEATURE, ");
               break;
            case 0x05:  // SET_ADDRESS
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_DBG("SET_ADDRESS, ");
               USB_DBG("0x%X\n",s.wValue);
               break;
            case 0x07:  // SET_DESCRIPTOR
               USB_DBG("SET_DESCRIPTOR, ");
               break;
            case 0x09:  // SET_CONFIGURATION
               USB_DBG("SET_CONFIGURATION, ");
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_config_state = CONFIGURED;
               USB_enumerated = true;
               USB_DBG("set conf 0x%X\n",s.wValue);
               break;
         }
            break;
         case Setup_Recipient_INTERFACE:
            USB_DBG("Interface, ");
            switch(s.bRequest)
         {
            case 0x01:  // CLEAR_FEATURE
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_DBG("CLEAR_FEATURE, ");
               break;
            case 0x03:  // SET_FEATURE
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_DBG("SET_FEATURE, ");
               break;
            case 0x11:  // SET_INTERFACE
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_DBG("SET_INTERFACE, ");
               break;
         }
            break;
         case Setup_Recipient_ENDPOINT:
            USB_DBG("Endpoint, ");
            switch(s.bRequest)
         {
            case 0x01:  // CLEAR_FEATURE
               PUT8(USB0_CORE+CSR0,(1<<3));
               USB_DBG("CLEAR_FEATURE, ");
               break;
            case 0x03:  // SET_FEATURE
               USB_DBG("SET_FEATURE, ");
               PUT8(USB0_CORE+CSR0,(1<<3));
               break;
         }
            break;
         case Setup_Recipient_OTHER:
            USB_DBG("Other, ");
            break;
      }
         break;
      case Direction_DEVICE_TO_HOST:
         USB_DBG("dev->host, ");
         switch(s.bmRequestType & USB_Setup_Recipient_Mask)
      {
         case Setup_Recipient_DEVICE:
            USB_DBG("Device, ");
            switch(s.bRequest)
         {
            case 0x00:  // GET_STATUS
               USB_DBG("GET_STATUS, ");
               break;
            case 0x06:  // GET_DESCRIPTOR
               USB_DBG("GET_DESCRIPTOR, ");
               USB_getDescriptor(s);
               break;
            case 0x08:  // GET_CONFIGURATION
               USB_DBG("GET_CONFIGURATION, ");
               break;
         }
            break;
         case Setup_Recipient_INTERFACE:
            USB_DBG("Interface, ");
            switch(s.bRequest)
         {
            case 0x00:  // GET_STATUS
               USB_DBG("GET_STATUS, ");
               break;
            case 0x0A:  // GET_INTERFACE
               USB_DBG("GET_INTERFACE, ");
               break;
         }
            break;
         case Setup_Recipient_ENDPOINT:
            USB_DBG("Endpoint, ");
            switch(s.bRequest)
         {
            case 0x00:  // GET_STATUS
               USB_DBG("GET_STATUS, ");
               break;
            case 0x12:  // SYNCH_FRAME
               USB_DBG("SYNCH_FRAME, ");
               break;
         }
            break;
         case Setup_Recipient_OTHER:
            USB_DBG("Other, ");
            break;
      }
         break;
   }
   USB_DBG("\n");
}

void USB0_ENDP0Handler()
{
   uint8_t csr0 = GET8(USB0_CORE+CSR0);
   (void) csr0;
   uint32_t size;
   struct USBSetupPacket setup;
   static uint8_t address = 0;
   if(csr0 &0b100)// sent stall?
   {
      USB_DBG("sentstall\n");
      PUT8(USB0_CORE+CSR0,0);	// clear sentstall?
      USB_state_EP0 = IDLE;
      //clear sentstall, -> IDLE
   }
   if (csr0 & 0b10000)
   {
      //USB_DBG("setup end\n");
      PUT8(USB0_CORE+CSR0,0b10000000);
      USB_state_EP0 = IDLE;
      //setup end? serviced setupend, -> IDLE
   }
   switch(USB_state_EP0)
   {
      case IDLE:
         switch(USB_config_state)
      {
         case DEFAULT:
            size = GET8(USB0_CORE+COUNT0)&0x7F;
            if(size)
            {
               USB_ReadFrom((uint8_t*)&setup,size,0);
               PUT8(USB0_CORE+CSR0,(1<<6));
               USB_print_setup(setup);
               if(setup.bRequest == 0x05)
               {
                  PUT8(USB0_CORE+CSR0,(1<<3));
                  address = (uint8_t) setup.wValue & 0x7F;
               }
               else if (setup.bRequest == 0x06)
               {
                  uint8_t desc_type = setup.wValue >> 8;
                  if(desc_type == 0x01)
                  {
                     // send Device Descriptor
                     USB_getDescriptor(setup);
                  }
               }
            }
            else  // interrupt at end of status stage?
            {
               if(address)
               {
                  PUT8(USB0_CORE+FADDR,address);
                  USB_config_state = ADDRESSED;
                  USB_DBG("setup address, 0x%02hhX",address);
               }
            }
            USB_DBG("\n");
            break;
         case ADDRESSED:
            
            size = GET8(USB0_CORE+COUNT0)&0x7F;
            if(size)
            {
               USB_ReadFrom((uint8_t*)&setup,size,0);
               PUT8(USB0_CORE+CSR0,(1<<6));
               USB_DBG("Standard, ");
               USB_Setup_Standard(setup);
            }
            else
            {
               USB_DBG("no size\n");
            }
            break;
         case CONFIGURED:
            size = GET8(USB0_CORE+COUNT0)&0x7F;
            if(size)
            {
               USB_ReadFrom((uint8_t*)&setup,size,0);
               PUT8(USB0_CORE+CSR0,(1<<6));
               switch(setup.bmRequestType & USB_Setup_Type_Mask)
               {
                  case Setup_Type_STANDARD:
                     USB_DBG("Standard, ");
                     PUT8(USB0_CORE+CSR0,(1<<3));
                     USB_Setup_Standard(setup);
                     break;
                  case Setup_Type_CLASS:
                     USB_DBG("Class, ");
                     USB_Setup_Class(setup);
                     break;
                  case Setup_Type_VENDOR:
                     USB_DBG("Vendor, \n");
                     break;
                  case Setup_Type_RESERVED:
                     USB_DBG("Reserved, \n");
                     break;
               }
            }
            break;
         default:
            while(1);   // error
            break;
      }
         break;
      case TX:
         USB_DBG("TX routine\n");
         EP0_TX_routine();
         break;
      case RX:
      default:	// yes
         USB_DBG("RX routine\n");
         EP0_RX_routine();
         break;
         
         break;
   }
}

void USB_init()
{
   PUT32(USBSS+SYSCONFIG,1);	// start usb subsystem module reset
   while(GET32(USBSS+SYSCONFIG)&0b1);
   
   
   PUT32(USB0+USBxCTRL,1);		// start control module reset
   while(GET32(USB0+USBxCTRL)&0b1);
   
   
   PUT32(USB0+USBxMODE,(1<<8)|(1<<7));	// B type (peripheral) and from bit 8, not PHY
   
   PUT8(USB0_CORE+INTRTXE,0x0001);	// disable all interrupt at musb core level exept for EP0 int
   PUT8(USB0_CORE+INTRRXE,0x0000);	// disable all interrupt at musb core level
   PUT8(USB0_CORE+INTRUSBE,0x00);	// disable all interrupt at musb core level
   
   NVIC_ClearPending(USBINT0_IRQn);
   
   NVIC_Enable(USBINT0_IRQn);
   
   
   //PUT32(USB0+USBxIRQENABLESET0,0x1);  // enable endpoint 0 interrupt
   PUT32(USB0+USBxIRQENABLESET1,1<<9);	// enable legacy musb interrupt?
   PUT32(USB0+USBxCTRL,1<<3);	// setup USB controller as legacy
   PUT16(USB0_CORE+INTRTX,1);	// enable endp 0 interrupt
   
   PUT8(USB0_CORE+RXMAXP,64);
   PUT8(USB0_CORE+TXMAXP,64);
   
   PUT8(USB0_CORE+POWER,GET8(USB0_CORE+POWER)|(1<<6));	// softconn = 1
   while(!USB_enumerated)
   {
      asm volatile("wfi\n");
   }
}

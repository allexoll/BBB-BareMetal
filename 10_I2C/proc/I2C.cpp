/**
 * @file I2C.cpp
 * @author Alexis Marquet
 * @date 25 May 2015
 * @brief Function implementation concerning I2C peripherals for AM335x: TRM 21, Datasheet 4.2
 * Much of this comes from TI Starterware for Sitara processors. but it didnt work, so I had to rewrite the routines for read & write
 **/

#include <stdint.h>

extern "C" {
#include "../core/llma.h"
#include "clock_module.h"
#include "control_module.h"
#include "interrupt.h"
}
#include "I2C.h"

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
/******************************************************************************
 **                      MACROS
 *******************************************************************************/

#define  I2C_INSTANCE   (3)      // I2C0, I2C1, I2C2

/****************************************************************************/
/*
 ** Values that can be passed to  I2CMasterControl API as cmd to configure mode
 ** of operation of I2C
 */

#define     I2C_CFG_MST_TX              I2C_CON_TRX | I2C_CON_MST
#define     I2C_CFG_MST_RX              I2C_CON_MST
#define     I2C_CFG_STOP                I2C_CON_STP
#define     I2C_CFG_N0RMAL_MODE         (0 << I2C_CON_STB_SHIFT)
#define     I2C_CFG_SRT_BYTE_MODE       I2C_CON_STB
#define     I2C_CFG_7BIT_SLAVE_ADDR     (0 << I2C_CON_XSA_SHIFT)
#define     I2C_CFG_10BIT_SLAVE_ADDR    I2C_CON_XSA
#define     I2C_CFG_10BIT_OWN_ADDR_0    I2C_CON_XOA0
#define     I2C_CFG_10BIT_OWN_ADDR_1    I2C_CON_XOA1
#define     I2C_CFG_10BIT_OWN_ADDR_2    I2C_CON_XOA2
#define     I2C_CFG_10BIT_OWN_ADDR_3    I2C_CON_XOA3
#define     I2C_CFG_7BIT_OWN_ADDR_0     (0 << I2C_CON_XOA0_SHIFT)
#define     I2C_CFG_7BIT_OWN_ADDR_1     (0 << I2C_CON_XOA1_SHIFT)
#define     I2C_CFG_7BIT_OWN_ADDR_2     (0 << I2C_CON_XOA2_SHIFT
#define     I2C_CFG_7BIT_OWN_ADDR_3     (0 << I2C_CON_XOA3_SHIFT)

/****************************************************************************/
/*
 ** Values that can be passed to  I2CMasterIntEnableEx API as intFlag to Enable
 ** interrupts.
 */

#define     I2C_INT_ARBITRATION_LOST     I2C_IRQSTATUS_AL
#define     I2C_INT_NO_ACK               I2C_IRQSTATUS_NACK
#define     I2C_INT_ADRR_READY_ACESS     I2C_IRQSTATUS_ARDY
#define     I2C_INT_RECV_READY           I2C_IRQSTATUS_RRDY
#define     I2C_INT_TRANSMIT_READY       I2C_IRQSTATUS_XRDY
#define     I2C_INT_GENERAL_CALL         I2C_IRQSTATUS_GC
#define     I2C_INT_START                I2C_IRQSTATUS_STC
#define     I2C_INT_ACCESS_ERROR         I2C_IRQSTATUS_AERR
#define     I2C_INT_STOP_CONDITION       I2C_IRQSTATUS_BF
#define     I2C_INT_ADRR_SLAVE           I2C_IRQSTATUS_AAS
#define     I2C_INT_TRANSMIT_UNDER_FLOW  I2C_IRQSTATUS_XUDF
#define     I2C_INT_RECV_OVER_RUN        I2C_IRQSTATUS_ROVR
#define     I2C_INT_RECV_DRAIN           I2C_IRQSTATUS_RDR
#define     I2C_INT_TRANSMIT_DRAIN       I2C_IRQSTATUS_XDR

/****************************************************************************/
/*
 ** Register definition for I2C peripherals
 */

#define I2C_REVNB_LO          (0x0)
#define I2C_REVNB_HI          (0x4)
#define I2C_SYSC              (0x10)
#define I2C_EOI               (0x20)
#define I2C_IRQSTATUS_RAW     (0x24)
#define I2C_IRQSTATUS         (0x28)
#define I2C_IRQENABLE_SET     (0x2C)
#define I2C_IRQENABLE_CLR     (0x30)
#define I2C_WE                (0x34)
#define I2C_DMARXENABLE_SET   (0x38)
#define I2C_DMATXENABLE_SET   (0x3C)
#define I2C_DMARXENABLE_CLR   (0x40)
#define I2C_DMATXENABLE_CLR   (0x44)
#define I2C_DMARXWAKE_EN      (0x48)
#define I2C_DMATXWAKE_EN      (0x4C)
#define I2C_SYSS              (0x90)
#define I2C_BUF               (0x94)
#define I2C_CNT               (0x98)
#define I2C_DATA              (0x9C)
#define I2C_CON               (0xA4)
#define I2C_OA                (0xA8)
#define I2C_SA                (0xAC)
#define I2C_PSC               (0xB0)
#define I2C_SCLL              (0xB4)
#define I2C_SCLH              (0xB8)
#define I2C_SYSTEST           (0xBC)
#define I2C_BUFSTAT           (0xC0)
#define I2C_OAn(n)            (0xC4 + ((n) * 4))
#define I2C_ACTOA             (0xD0)
#define I2C_SBLOCK            (0xD4)

/**************************************************************************\
 * Field Definition Macros
\**************************************************************************/

// SYSC
#define I2C_SYSC_AUTOIDLE     (0x00000001u)
#define I2C_SYSC_CLKACTIVITY  (0x00000300u)
#define I2C_SYSC_ENAWAKEUP    (0x00000004u)
#define I2C_SYSC_IDLEMODE     (0x00000018u)
#define I2C_SYSC_SRST         (0x00000002u)

// IRQSTATUS_RAW
#define I2C_IRQSTATUS_RAW_AAS    (0x00000200u)
#define I2C_IRQSTATUS_RAW_AERR   (0x00000080u)
#define I2C_IRQSTATUS_RAW_AL     (0x00000001u)
#define I2C_IRQSTATUS_RAW_ARDY   (0x00000004u)
#define I2C_IRQSTATUS_RAW_BB     (0x00001000u)
#define I2C_IRQSTATUS_RAW_BF     (0x00000100u)
#define I2C_IRQSTATUS_RAW_GC     (0x00000020u)
#define I2C_IRQSTATUS_RAW_NACK   (0x00000002u)
#define I2C_IRQSTATUS_RAW_RDR    (0x00002000u)
#define I2C_IRQSTATUS_RAW_ROVR   (0x00000800u)
#define I2C_IRQSTATUS_RAW_RRDY   (0x00000008u)
#define I2C_IRQSTATUS_RAW_STC    (0x00000040u)
#define I2C_IRQSTATUS_RAW_XDR    (0x00004000u)
#define I2C_IRQSTATUS_RAW_XRDY   (0x00000010u)
#define I2C_IRQSTATUS_RAW_XUDF   (0x00000400u)

// IRQSTATUS
#define I2C_IRQSTATUS_AAS  (0x00000200u)
#define I2C_IRQSTATUS_AERR (0x00000080u)
#define I2C_IRQSTATUS_AL   (0x00000001u)
#define I2C_IRQSTATUS_ARDY (0x00000004u)
#define I2C_IRQSTATUS_BB   (0x00001000u)
#define I2C_IRQSTATUS_BF   (0x00000100u)
#define I2C_IRQSTATUS_GC   (0x00000020u)
#define I2C_IRQSTATUS_NACK (0x00000002u)
#define I2C_IRQSTATUS_RDR  (0x00002000u)
#define I2C_IRQSTATUS_ROVR (0x00000800u)
#define I2C_IRQSTATUS_RRDY (0x00000008u)
#define I2C_IRQSTATUS_STC  (0x00000040u)
#define I2C_IRQSTATUS_XDR  (0x00004000u)
#define I2C_IRQSTATUS_XRDY (0x00000010u)
#define I2C_IRQSTATUS_XUDF (0x00000400u)

// IRQENABLE_SET
#define I2C_IRQENABLE_SET_AERR_IE   (0x00000080u)
#define I2C_IRQENABLE_SET_AL_IE     (0x00000001u)
#define I2C_IRQENABLE_SET_ARDY_IE   (0x00000004u)
#define I2C_IRQENABLE_SET_ASS_IE    (0x00000200u)
#define I2C_IRQENABLE_SET_BF_IE     (0x00000100u)
#define I2C_IRQENABLE_SET_GC_IE     (0x00000020u)
#define I2C_IRQENABLE_SET_NACK_IE   (0x00000002u)
#define I2C_IRQENABLE_SET_RDR_IE    (0x00002000u)
#define I2C_IRQENABLE_SET_ROVR      (0x00000800u)
#define I2C_IRQENABLE_SET_RRDY_IE   (0x00000008u)
#define I2C_IRQENABLE_SET_STC_IE    (0x00000040u)
#define I2C_IRQENABLE_SET_XDR_IE    (0x00004000u)
#define I2C_IRQENABLE_SET_XRDY_IE   (0x00000010u)
#define I2C_IRQENABLE_SET_XUDF      (0x00000400u)

/* IRQENABLE_CLR */
#define I2C_IRQENABLE_CLR_AERR_IE   (0x00000080u)
#define I2C_IRQENABLE_CLR_AL_IE     (0x00000001u)
#define I2C_IRQENABLE_CLR_ARDY_IE   (0x00000004u)
#define I2C_IRQENABLE_CLR_ASS_IE    (0x00000200u)
#define I2C_IRQENABLE_CLR_BF_IE     (0x00000100u)
#define I2C_IRQENABLE_CLR_GC_IE     (0x00000020u)
#define I2C_IRQENABLE_CLR_NACK_IE   (0x00000002u)
#define I2C_IRQENABLE_CLR_RDR_IE    (0x00002000u)
#define I2C_IRQENABLE_CLR_ROVR      (0x00000800u)
#define I2C_IRQENABLE_CLR_RRDY_IE   (0x00000008u)
#define I2C_IRQENABLE_CLR_STC_IE    (0x00000040u)
#define I2C_IRQENABLE_CLR_XDR_IE    (0x00004000u)
#define I2C_IRQENABLE_CLR_XRDY_IE   (0x00000010u)
#define I2C_IRQENABLE_CLR_XUDF      (0x00000400u)

/* SYSS */
#define I2C_SYSS_RDONE  (0x00000001u)

/* CON */
#define I2C_CON_I2C_EN  (0x00008000u)
#define I2C_CON_MST     (0x00000400u)
#define I2C_CON_OPMODE  (0x00003000u)
#define I2C_CON_STB     (0x00000800u)
#define I2C_CON_STP     (0x00000002u)
#define I2C_CON_STT     (0x00000001u)
#define I2C_CON_TRX     (0x00000200u)
#define I2C_CON_XOA0    (0x00000080u)
#define I2C_CON_XOA1    (0x00000040u)
#define I2C_CON_XOA2    (0x00000020u)
#define I2C_CON_XOA3    (0x00000010u)
#define I2C_CON_XSA     (0x00000100u)

/* PSC */
#define I2C_PSC_PSC     (0x000000FFu)

/* SCLL */
#define I2C_SCLL_HSSCLL   (0x0000FF00u)
#define I2C_SCLL_SCLL   (0x000000FFu)

/* SCLH */
#define I2C_SCLH_HSSCLH   (0x0000FF00u)
#define I2C_SCLH_SCLH   (0x000000FFu)

/******************************************************************************
 **              GLOBAL VARIABLES
 ******************************************************************************/

static volatile uint8_t dataFromSlave[I2C_INSTANCE][100];
static volatile uint8_t dataToSlave[I2C_INSTANCE][100];
static volatile uint32_t tCount[I2C_INSTANCE];
static volatile uint32_t rCount[I2C_INSTANCE];
static volatile uint32_t flag[I2C_INSTANCE] = {1, 1, 1};
static volatile uint32_t numOfBytes[I2C_INSTANCE];
static volatile bool nacked[I2C_INSTANCE];
static uint32_t clkspeed[I2C_INSTANCE];

/*******************************************************************************
 *                        API FUNCTION DEFINITIONS
 *******************************************************************************/

/**
 * \brief   This API will divide the system clock fed to I2C module between
 *          12 and 100Mhz.It will also configure the I2C bus clock frequency.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used.
 * \param   sysClk      It is the System clock fed to I2C module.
 * \param   internalClk It is the internal clock used by I2C module.Which is
 *                      obtained by scaling System clock fed to I2C module.
 * \param   outputClk   It is the required I2C bus speed or frequency.
 *
 * \return  None.
 **/
static void I2CMasterInitExpClk(uint32_t baseAdd, uint32_t sysClk, uint32_t internalClk, uint32_t outputClk)
{
   uint32_t prescalar;
   uint32_t divider;
   
   /* Calculate prescalar value */
   prescalar = (sysClk / internalClk) - 1;
   
   REG32(baseAdd + I2C_PSC) = prescalar;
   
   divider = internalClk/outputClk;
   
   divider = divider / 2;
   
   REG32(baseAdd + I2C_SCLL) = divider - 7;
   
   REG32(baseAdd + I2C_SCLH) = divider - 5;
}

/**
 * \brief   Enables the I2C module.This will bring the I2C module out of reset.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  None.
 *
 **/
static void I2CMasterEnable(uint32_t baseAdd)
{
   REG32(baseAdd + I2C_CON) |= I2C_CON_I2C_EN;
}

/**
 * \brief   Disables the I2C Module.This will put the I2C module in reset.
 *          Only Tx and Rx are cleared,status bits are set their default
 *          values and all configuration registers are not reset,they keep
 *          their initial values.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  None.
 *
 **/
static void I2CMasterDisable(uint32_t baseAdd)
{
   REG32(baseAdd + I2C_CON) &= ~(I2C_CON_I2C_EN);
}

/**
 * \brief   This API configure I2C in different modes of operation.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   cmd       It is the value which configures I2C in different mode's
 *                    of operation.\n
 *
 *          cmd can take follwing macros.\n
 *
 *          I2C_CFG_MST_TX             - Configure's I2C as Master-Transmitter.\n
 *          I2C_CFG_MST_RX             - Configure's I2C as Master-Receiver.\n
 *          I2C_CFG_STOP               - Configure's I2C to generate stop
 *                                       condition when DCOUNT counts down to
 *                                       zero.\n
 *          I2C_CFG_N0RMAL_MODE        - Configure's I2C in normal mode.\n
 *          I2C_CFG_SRT_BYTE_MODE      - Configure's I2C in start byte mode.\n
 * \return None.
 *
 **/
static void I2CMasterControl(uint32_t baseAdd, uint32_t cmd)
{
   REG32(baseAdd + I2C_CON) = cmd | I2C_CON_I2C_EN;
}

/**
 * \brief   This API start's a I2C transaction on the bus. This API must
 *          be called after all the configuration for the i2c module is
 *          done and after bringing I2C out of local reset
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
static void I2CMasterStart(uint32_t baseAdd)
{
   REG32(baseAdd + I2C_CON) |= I2C_CON_STT;
}

/**
 * \brief  This API stops a I2C transaction on the bus.
 *         This API must be used in case a deliberate STOP needs to be sent
 *         on the bus.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
static void I2CMasterStop(uint32_t baseAdd)
{
   REG32(baseAdd + I2C_CON) |= I2C_CON_STP;
}

/**
 * \brief  This API enables only specified I2C interrupts in master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag   It specifies the interrupts that are rquired to be enabled.\n
 *
 *         intFlag can take following values.\n
 *
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n
 *
 * \return None.
 **/
static void I2CMasterIntEnableEx(uint32_t baseAdd, uint32_t intFlag)
{
   REG32(baseAdd + I2C_IRQENABLE_SET) |= intFlag;
}


/**
 * \brief  This API disables only specified I2C interrupts in master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag   It specifies the interrupts that are rquired to be disabled\n
 *
 *         intFlag can take following values.\n
 *
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n
 *
 * \return None.
 **/
static void I2CMasterIntDisableEx(uint32_t baseAdd, uint32_t intFlag)
{
   REG32(baseAdd + I2C_IRQENABLE_CLR) = intFlag;
}

/**
 * \brief  This API returns the status of  interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns status of interrupts.
 **/
uint32_t I2CMasterIntStatus(uint32_t baseAdd)
{
   return ((REG32(baseAdd + I2C_IRQSTATUS)));
}

/**
 * \brief  This API Clears the status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose status needs to be cleared\n
 *
 *         intFlag can take following macros.\n
 *
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n
 *
 * \returns None
 **/
static void I2CMasterIntClearEx(uint32_t baseAdd, uint32_t intFlag)
{
   REG32(baseAdd + I2C_IRQSTATUS) = intFlag;
}

/**
 * \brief   This API sets the address of the slave device with which I2C wants to
 *          communicate.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   slaveAddr  slave address.
 *
 * \return None.
 **/
static void I2CMasterSlaveAddrSet(uint32_t baseAdd, uint32_t slaveAdd)
{
   /*Set the address of the slave with which the master will communicate.*/
   REG32(baseAdd + I2C_SA) = slaveAdd;
}

/**
 * \brief   This API configure I2C data count register with a value.
 *          The value in the I2C data count register indicate how many data
 *          words to transfer when the I2C is configured as a  master-transmitter
 *          and repeat mode is off.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 * \param   count    It is value which is set to I2C data count register.
 *
 * \return None.
 **/
static void I2CSetDataCount(uint32_t baseAdd, uint32_t count)
{
   REG32(baseAdd + I2C_CNT) = count;
}

/**
 * \brief   This API configure I2C data count register with a value.
 *          The value in the I2C data count register indicate how many data
 *          words to transfer when the I2C is configured as a  master-transmitter
 *          and repeat mode is off.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return  number of bytes transfered over the I2C bus.
 **/
static uint32_t I2CDataCountGet(uint32_t baseAdd)
{
   return(REG32(baseAdd + I2C_CNT));
}

/**
 * \brief   This API reset the entire I2C module.On reset,are set to power
 *          up reset values.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *
 **/
static void I2CSoftReset(uint32_t baseAdd)
{
   REG32(baseAdd + I2C_SYSC) |= I2C_SYSC_SRST;
}

/**
 * \brief   This API disables autoidle mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *
 **/
static void I2CAutoIdleDisable(uint32_t baseAdd)
{
   REG32(baseAdd + I2C_SYSC) &= ~I2C_SYSC_AUTOIDLE;
}

/**
 * \brief   This API indicates the state of the reset in case of
 *          hardware reset,global reset or paratial reset.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns returns "1" if reset is completed.
 *          returns "0" if internal module reset is ongoing.
 *
 **/
static uint32_t I2CSystemStatusGet(uint32_t baseAdd)
{
   return(REG32(baseAdd + I2C_SYSS) & I2C_SYSS_RDONE);
}

/**
 * \brief  This function Transmits a byte from the I2C in Master mode.
 *
 * \param  baseAdd is the Memory address of the I2C instance used.
 * \param  data data to be transmitted from the I2C Master.
 *
 * \return None.\n
 *
 **/
static void I2CMasterDataPut(uint32_t baseAdd, uint8_t data)
{
   /*write data to be transmited to Data transmit register */
   REG32(baseAdd + I2C_DATA) = data;
}

/**
 *  \brief  This Receives a byte that has been sent to the I2C in Master mode.
 *
 *  \param  baseAdd is the Memory address of the I2C instance used.
 *
 *  \return Returns the byte received from by the I2C in Master mode.
 *
 **/
static uint8_t I2CMasterDataGet(uint32_t baseAdd)
{
   return (uint8_t)REG32(baseAdd + I2C_DATA);
}

static uint32_t getI2CAddr(I2C_t i2c)
{
   switch(i2c)
   {
      case I2C0:
         return 0x44E0B000;
         break;
      case I2C1:
         return 0x4802A000;
         break;
      case I2C2:
         return 0x4819C000;
         break;
      default:
         while(1);   // error
         break;
   }
   return 0;
}

/*
 ** Clear the I2C interrupts for the given instance
 */
static void cleanupInterrupts(I2C_t i2c)
{
   uint32_t instAddr;
   instAddr = getI2CAddr(i2c);
   
   I2CMasterIntClearEx(instAddr,  0x7FF);
   I2CMasterIntDisableEx(instAddr, 0x7FF);
}

/*
 ** Configure I2C0 on which the PMIC is interfaced
 */
static void _I2CInit(I2C_t i2c)
{
   uint32_t instAddr;
   
   instAddr = getI2CAddr(i2c);
   
   // Put i2c in reset/disabled state
   I2CMasterDisable(instAddr);
   
   I2CSoftReset(instAddr);
   
   // Disable auto Idle functionality
   I2CAutoIdleDisable(instAddr);
   
   // Configure i2c bus speed to 100khz
   I2CMasterInitExpClk(instAddr, 48000000, 12000000, clkspeed[i2c]);
   
   // Bring I2C module out of reset
   I2CMasterEnable(instAddr);
   
   while(!I2CSystemStatusGet(instAddr));
}

void I2C_initI2C(I2C_t i2c, uint32_t clkSpeed)
{
   clkspeed[i2c] = clkSpeed;
   switch(i2c)
   {
      case I2C0:
         // Writing to MODULEMODE field of CM_WKUP_I2C0_CLKCTRL register.
         REG32(CLKM_WKUP + CLKM_WKUP_I2C0_CLKCTRL) = 0x2;
         
         // Waiting for MODULEMODE field to reflect the written value.
         while((REG32(CLKM_WKUP + CLKM_WKUP_I2C0_CLKCTRL) & 0b11) != 0b10);
         
         // Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL register to attain
         // desired value.
         while((REG32(CLKM_WKUP + CLKM_WKUP_CONTROL_CLKCTRL)&(0b11<<16)) != (0b00<<16));
         
         // Waiting for CLKACTIVITY_I2C0_GFCLK field in CM_WKUP_CLKSTCTRL
         // register to attain desired value.
         while((REG32(CLKM_WKUP + CLKM_WKUP_CLKSTCTRL)&(0b1<<11)) != (0b1<<11));
         
         // Waiting for IDLEST field in CM_WKUP_I2C0_CLKCTRL register to attain
         // desired value.
         while((REG32(CLKM_WKUP+CLKM_WKUP_I2C0_CLKCTRL)&(0b11<<16)) != (0b00<<16));
         
         // RX enabled, slow slew rate, pullup selected, I2C0 mode
         REG32(0x44E10000+CM_conf_i2c0_sda) = (1<<5)|(1<<6)|(1<<4) | 0b000;
         REG32(0x44E10000+CM_conf_i2c0_scl) = (1<<5)|(1<<6)|(1<<4) | 0b000;
         
         NVIC_ClearPending(I2C0INT_IRQn);
         NVIC_Enable(I2C0INT_IRQn);
         break;
      case I2C1:
         // TODO: implement I2C1 & I2C2
         while(1);
         break;
      case I2C2:
         while(1);
         break;
      default:
         while(1);   // error
         break;
   }
}

/**
 * @brief I2C0 Interrupt Service Routine. This function will read and write
 * data through I2C bus. Interrupts must be declared using extern "C" keyword,
 * otherwise the symbol get mixed by g++
 **/
extern "C"
void I2C0INT_IRQHandler(void)
{
   I2C_t instNum = I2C0;
   uint32_t instAddr = getI2CAddr(instNum);
   uint32_t status = 0;
      
   status = I2CMasterIntStatus(instAddr);
   
   I2CMasterIntClearEx(instAddr, status);
   
   if(status & I2C_INT_RECV_READY)
   {
      // Receive data from data receive register
      dataFromSlave[instNum][rCount[instNum]++] = I2CMasterDataGet(instAddr);
      I2CMasterIntClearEx(instAddr,  I2C_INT_RECV_READY);
      
      if(rCount[instNum] == numOfBytes[instNum])
      {
         I2CMasterIntDisableEx(instAddr, I2C_INT_RECV_READY);
         // Generate a STOP
         I2CMasterStop(instAddr);
      }
   }
   if (status & I2C_INT_TRANSMIT_READY)
   {
      // Put data to data transmit register of i2c
      I2CMasterDataPut(instAddr, dataToSlave[instNum][tCount[instNum]++]);
      I2CMasterIntClearEx(instAddr, I2C_INT_TRANSMIT_READY);
      
      if(tCount[instNum] == numOfBytes[instNum])
      {
         I2CMasterIntDisableEx(instAddr, I2C_INT_TRANSMIT_READY);
         I2CMasterStop(instAddr);
      }
   }
   
   if (status & I2C_INT_STOP_CONDITION)
   {
      I2CMasterIntClearEx(instAddr,I2C_INT_STOP_CONDITION);
      // Disable transmit data ready and receive data read interupt
      I2CMasterIntDisableEx(instAddr,  I2C_INT_TRANSMIT_READY |
                                             I2C_INT_RECV_READY     |
                                             I2C_INT_STOP_CONDITION);
      flag[instNum] = 0;
   }
   
   if(status & I2C_INT_NO_ACK)
   {
      I2CMasterIntClearEx(instAddr,I2C_INT_NO_ACK);
      I2CMasterIntDisableEx(instAddr,  I2C_INT_TRANSMIT_READY  |
                                             I2C_INT_RECV_READY      |
                                             I2C_INT_NO_ACK          |
                                             I2C_INT_STOP_CONDITION);
      // Generate a STOP
      I2CMasterStop(instAddr);
      nacked[instNum] = 1;
      flag[instNum] = 0;
   }
}

uint32_t I2C_write(I2C_t i2c, uint8_t slave_addr, uint8_t* b, uint32_t length)
{
   uint32_t instAddr;
   tCount[i2c] = 0;
   rCount[i2c] = 0;
   nacked[i2c] = 0;
   flag[i2c] = 1;

   // does not work otherwise...
   _I2CInit(i2c);
   
   instAddr = getI2CAddr(i2c);
   
   I2CMasterSlaveAddrSet(instAddr, slave_addr>>1);
   
   // Copy buffer to send into internal buffer
   memcpy((uint8_t*)dataToSlave[i2c],b,length);
   
   I2CSetDataCount(instAddr, length);
   
   numOfBytes[i2c] = I2CDataCountGet(instAddr);
   
   cleanupInterrupts(i2c);
   
   I2CMasterControl(instAddr, I2C_CFG_MST_TX );
   
   I2CMasterIntEnableEx(instAddr, I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION | I2C_INT_NO_ACK);
   I2CMasterStart(instAddr);

   // Wait for transfer to end
   while(flag[i2c]);
   if(nacked[i2c])
   {
      return 0;
   }
   return tCount[i2c];
}

uint32_t I2C_read(I2C_t i2c, uint8_t slave_addr, uint8_t* b, uint32_t length)
{
   uint32_t instAddr;
   tCount[i2c] = 0;
   rCount[i2c] = 0;
   nacked[i2c] = 0;
   flag[i2c] = 1;

   // does not work otherwise...
   _I2CInit(i2c);
   
   instAddr = getI2CAddr(i2c);

   I2CMasterSlaveAddrSet(instAddr, slave_addr>>1);

   flag[i2c] = 1;
   
   I2CSetDataCount(instAddr, length);
   
   numOfBytes[i2c] = I2CDataCountGet(instAddr);
   
   cleanupInterrupts(i2c);
   
   I2CMasterControl(instAddr, I2C_CFG_MST_RX);
   
   I2CMasterIntEnableEx(instAddr, I2C_INT_RECV_READY | I2C_INT_STOP_CONDITION | I2C_INT_NO_ACK);
   
   I2CMasterStart(instAddr);
   
   // Wait for transfer to end
   while(flag[i2c]);
   if(nacked[i2c])
   {
      return 0;
   }
   // Copy data read from internal buffer to User buffer
   memcpy(b, (uint8_t*)dataFromSlave[i2c],length);
   return rCount[i2c];
}

vector <uint8_t> I2C_busProbe(I2C_t i2c)
{
   vector <uint8_t> l;
   uint8_t rxb[2] = {0,0};
   for(int i = 0x0; i < 0xff; i+=2)
   {
      if(I2C_read(I2C0, i, &rxb[0], 1) == 1)
      {
         l.push_back(i);
      }
   }
   return l;
}


/*
 The MIT License (MIT)
 
 Copyright (c) 2015 Alexis Marquet
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */
/**
 * @file control_module.h
 * @author Alexis Marquet
 * @date 03 Dec 2014
 * @brief Types & function prototypes concerning control module usage: TRM 9, TRM 9.3
 **/
#ifndef __control_module_H
#define __control_module_H

/**
 * @brief Control Module register & their coresponding offsets: TRM 9.3
 **/
typedef enum
{
   CM_control_revision           = 0x0000,
   CM_control_hwinfo             = 0x0004,
   CM_control_sysconfig          = 0x0010,
   CM_control_status             = 0x0040,
   CM_control_emif_sdram_config  = 0x0110,
   CM_cortex_vbbldo_ctrl         = 0x041C,
   CM_core_sldo_ctrl             = 0x0428,
   CM_mpu_sldo_ctrl              = 0x042C,
   CM_clk32kdivratio_ctrl        = 0x0444,
   CM_bandgap_ctrl               = 0x0448,
   CM_bandgap_trim               = 0x044C,
   CM_pll_clkinpulow_ctrl        = 0x0458,
   CM_mosc_ctrl                  = 0x0468,
   CM_deepsleep_ctrl             = 0x0470,
   CM_dpll_pwr_sw_status         = 0x050C,
   CM_device_id                  = 0x0600,
   CM_dev_feature                = 0x0604,
   CM_init_priority_0            = 0x0608,
   CM_init_priority_1            = 0x060C,
   CM_mmu_cfg                    = 0x0610,
   CM_tptc_cfg                   = 0x0614,
   CM_usb_ctrl0                  = 0x0620,
   CM_usb_sts0                   = 0x0624,
   CM_usb_ctrl1                  = 0x0628,
   CM_usb_sts1                   = 0x062C,
   CM_mac_id0_lo                 = 0x0630,
   CM_mac_id0_hi                 = 0x0634,
   CM_mac_id1_lo                 = 0x0638,
   CM_mac_id1_hi                 = 0x063C,
   CM_dcan_raminit               = 0x0644,
   CM_usb_wkup_ctrl              = 0x0648,
   CM_gmii_sel                   = 0x0650,
   CM_pwmss_ctrl                 = 0x0664,
   CM_mreqprio_0                 = 0x0670,
   CM_mreqprio_1                 = 0x0674,
   CM_hw_event_sel_grp1          = 0x0690,
   CM_hw_event_sel_grp2          = 0x0694,
   CM_hw_event_sel_grp3          = 0x0698,
   CM_hw_event_sel_grp4          = 0x069C,
   CM_smrt_ctrl                  = 0x06A0,
   CM_mpuss_hw_debug_sel         = 0x06A4,
   CM_mpuss_hw_dbg_info          = 0x06A8,
   CM_vdd_mpu_opp_050            = 0x0770,
   CM_vdd_mpu_opp_100            = 0x0774,
   CM_vdd_mpu_opp_120            = 0x0778,
   CM_vdd_mpu_opp_turbo          = 0x077C,
   CM_vdd_core_opp_050           = 0x07B8,
   CM_vdd_core_opp_100           = 0x07BC,
   CM_bb_scale                   = 0x07D0,
   CM_usb_vid_pid                = 0x07F4,
   CM_efuse_sma                  = 0x07FC,
   CM_conf_gpmc_ad0              = 0x0800,
   CM_conf_gpmc_ad1              = 0x0804,
   CM_conf_gpmc_ad2              = 0x0808,
   CM_conf_gpmc_ad3              = 0x080C,
   CM_conf_gpmc_ad4              = 0x0810,
   CM_conf_gpmc_ad5              = 0x0814,
   CM_conf_gpmc_ad6              = 0x0818,
   CM_conf_gpmc_ad7              = 0x081C,
   CM_conf_gpmc_ad8              = 0x0820,
   CM_conf_gpmc_ad9              = 0x0824,
   CM_conf_gpmc_ad10             = 0x0828,
   CM_conf_gpmc_ad11             = 0x082C,
   CM_conf_gpmc_ad12             = 0x0830,
   CM_conf_gpmc_ad13             = 0x0834,
   CM_conf_gpmc_ad14             = 0x0838,
   CM_conf_gpmc_ad15             = 0x083C,
   CM_conf_gpmc_a0               = 0x0840,
   CM_conf_gpmc_a1               = 0x0844,
   CM_conf_gpmc_a2               = 0x0848,
   CM_conf_gpmc_a3               = 0x084C,
   CM_conf_gpmc_a4               = 0x0850,
   CM_conf_gpmc_a5               = 0x0854,
   CM_conf_gpmc_a6               = 0x0858,
   CM_conf_gpmc_a7               = 0x085C,
   CM_conf_gpmc_a8               = 0x0860,
   CM_conf_gpmc_a9               = 0x0864,
   CM_conf_gpmc_a10              = 0x0868,
   CM_conf_gpmc_a11              = 0x086C,
   CM_conf_gpmc_wait0            = 0x0870,
   CM_conf_gpmc_wpn              = 0x0874,
   CM_conf_gpmc_ben1             = 0x0878,
   CM_conf_gpmc_csn0             = 0x087C,
   CM_conf_gpmc_csn1             = 0x0880,
   CM_conf_gpmc_csn2             = 0x0884,
   CM_conf_gpmc_csn3             = 0x0888,
   CM_conf_gpmc_clk              = 0x088C,
   CM_conf_gpmc_advn_ale         = 0x0890,
   CM_conf_gpmc_oen_ren          = 0x0894,
   CM_conf_gpmc_wen              = 0x0898,
   CM_conf_gpmc_ben0_cle         = 0x089C,
   CM_conf_lcd_data0             = 0x08A0,
   CM_conf_lcd_data1             = 0x08A4,
   CM_conf_lcd_data2             = 0x08A8,
   CM_conf_lcd_data3             = 0x08AC,
   CM_conf_lcd_data4             = 0x08B0,
   CM_conf_lcd_data5             = 0x08B4,
   CM_conf_lcd_data6             = 0x08B8,
   CM_conf_lcd_data7             = 0x08BC,
   CM_conf_lcd_data8             = 0x08C0,
   CM_conf_lcd_data9             = 0x08C4,
   CM_conf_lcd_data10            = 0x08C8,
   CM_conf_lcd_data11            = 0x08CC,
   CM_conf_lcd_data12            = 0x08D0,
   CM_conf_lcd_data13            = 0x08D4,
   CM_conf_lcd_data14            = 0x08D8,
   CM_conf_lcd_data15            = 0x08DC,
   CM_conf_lcd_vsync             = 0x08E0,
   CM_conf_lcd_hsync             = 0x08E4,
   CM_conf_lcd_pclk              = 0x08E8,
   CM_conf_lcd_ac_bias_en        = 0x08EC,
   CM_conf_mmc0_dat3             = 0x08F0,
   CM_conf_mmc0_dat2             = 0x08F4,
   CM_conf_mmc0_dat1             = 0x08F8,
   CM_conf_mmc0_dat0             = 0x08FC,
   CM_conf_mmc0_clk              = 0x0900,
   CM_conf_mmc0_cmd              = 0x0904,
   CM_conf_mii1_col              = 0x0908,
   CM_conf_mii1_crs              = 0x090C,
   CM_conf_mii1_rx_er            = 0x0910,
   CM_conf_mii1_tx_en            = 0x0914,
   CM_conf_mii1_rx_dv            = 0x0918,
   CM_conf_mii1_txd3             = 0x091C,
   CM_conf_mii1_txd2             = 0x0920,
   CM_conf_mii1_txd1             = 0x0924,
   CM_conf_mii1_txd0             = 0x0928,
   CM_conf_mii1_tx_clk           = 0x092C,
   CM_conf_mii1_rx_clk           = 0x0930,
   CM_conf_mii1_rxd3             = 0x0934,
   CM_conf_mii1_rxd2             = 0x0938,
   CM_conf_mii1_rxd1             = 0x093C,
   CM_conf_mii1_rxd0             = 0x0940,
   CM_conf_rmii1_ref_clk         = 0x0944,
   CM_conf_mdio                  = 0x0948,
   CM_conf_mdc                   = 0x094C,
   CM_conf_spi0_sclk             = 0x0950,
   CM_conf_spi0_d0               = 0x0954,
   CM_conf_spi0_d1               = 0x0958,
   CM_conf_spi0_cs0              = 0x095C,
   CM_conf_spi0_cs1              = 0x0960,
   CM_conf_ecap0_in_pwm0_out     = 0x0964,
   CM_conf_uart0_ctsn            = 0x0968,
   CM_conf_uart0_rtsn            = 0x096C,
   CM_conf_uart0_rxd             = 0x0970,
   CM_conf_uart0_txd             = 0x0974,
   CM_conf_uart1_ctsn            = 0x0978,
   CM_conf_uart1_rtsn            = 0x097C,
   CM_conf_uart1_rxd             = 0x0980,
   CM_conf_uart1_txd             = 0x0984,
   CM_conf_i2c0_sda              = 0x0988,
   CM_conf_i2c0_scl              = 0x098C,
   CM_conf_mcasp0_aclkx          = 0x0990,
   CM_conf_mcasp0_fsx            = 0x0994,
   CM_conf_mcasp0_axr0           = 0x0998,
   CM_conf_mcasp0_ahclkr         = 0x099C,
   CM_conf_mcasp0_aclkr          = 0x09A0,
   CM_conf_mcasp0_fsr            = 0x09A4,
   CM_conf_mcasp0_axr1           = 0x09A8,
   CM_conf_mcasp0_ahclkx         = 0x09AC,
   CM_conf_xdma_event_intr0      = 0x09B0,
   CM_conf_xdma_event_intr1      = 0x09B4,
   CM_conf_warmrstn              = 0x09B8,
   CM_conf_nnmi                  = 0x09C0,
   CM_conf_tms                   = 0x09D0,
   CM_conf_tdi                   = 0x09D4,
   CM_conf_tdo                   = 0x09D8,
   CM_conf_tck                   = 0x09DC,
   CM_conf_trstn                 = 0x09E0,
   CM_conf_emu0                  = 0x09E4,
   CM_conf_emu1                  = 0x09E8,
   CM_conf_rtc_pwronrstn         = 0x09F8,
   CM_conf_pmic_power_en         = 0x09FC,
   CM_conf_ext_wakeup            = 0x0A00,
   CM_conf_rtc_kaldo_enn         = 0x0A04,
   CM_conf_usb0_drvvbus          = 0x0A1C,
   CM_conf_usb1_drvvbus          = 0x0A34,
   CM_cqdetect_status            = 0x0E00,
   CM_ddr_io_ctrl                = 0x0E04,
   CM_vtp_ctrl                   = 0x0E0C,
   CM_vref_ctrl                  = 0x0E14,
   CM_tpcc_evt_mux_0_3           = 0x0F90,
   CM_tpcc_evt_mux_4_7           = 0x0F94,
   CM_tpcc_evt_mux_8_11          = 0x0F98,
   CM_tpcc_evt_mux_12_15         = 0x0F9C,
   CM_tpcc_evt_mux_16_19         = 0x0FA0,
   CM_tpcc_evt_mux_20_23         = 0x0FA4,
   CM_tpcc_evt_mux_24_27         = 0x0FA8,
   CM_tpcc_evt_mux_28_31         = 0x0FAC,
   CM_tpcc_evt_mux_32_35         = 0x0FB0,
   CM_tpcc_evt_mux_36_39         = 0x0FB4,
   CM_tpcc_evt_mux_40_43         = 0x0FB8,
   CM_tpcc_evt_mux_44_47         = 0x0FBC,
   CM_tpcc_evt_mux_48_51         = 0x0FC0,
   CM_tpcc_evt_mux_52_55         = 0x0FC4,
   CM_tpcc_evt_mux_56_59         = 0x0FC8,
   CM_tpcc_evt_mux_60_63         = 0x0FCC,
   CM_timer_evt_capt             = 0x0FD0,
   CM_ecap_evt_capt              = 0x0FD4,
   CM_adc_evt_capt               = 0x0FD8,
   CM_reset_iso                  = 0x1000,
   CM_dpll_pwr_sw_ctrl           = 0x1318,
   CM_ddr_cke_ctrl               = 0x131C,
   CM_sma2                       = 0x1320,
   CM_m3_txev_eoi                = 0x1324,
   CM_ipc_msg_reg0               = 0x1328,
   CM_ipc_msg_reg1               = 0x132C,
   CM_ipc_msg_reg2               = 0x1330,
   CM_ipc_msg_reg3               = 0x1334,
   CM_ipc_msg_reg4               = 0x1338,
   CM_ipc_msg_reg5               = 0x133C,
   CM_ipc_msg_reg6               = 0x1340,
   CM_ipc_msg_reg7               = 0x1344,
   CM_ddr_cmd0_ioctrl            = 0x1404,
   CM_ddr_cmd1_ioctrl            = 0x1408,
   CM_ddr_cmd2_ioctrl            = 0x140C,
   CM_ddr_data0_ioctrl           = 0x1440,
   CM_ddr_data1_ioctrl           = 0x1444
}CONTROL_MODULE;

/**
 * @fn void CM_setCtrlModule(CONTROL_MODULE module, unsigned int value)
 * @brief               Set the control module to a certain value.
 * @param[in]  module   Module to set value.
 * @param[in]  value    Value to set module to.
 * @return              void
 **/
void CM_setCtrlModule(CONTROL_MODULE module, unsigned int value);


/**
 * @fn unsigned int CM_getCtrlModule(CONTROL_MODULE module)
 * @brief               Get the control module value.
 * @param[in]  module   Module to get the value from.
 * @return              Value of the control module.
 **/
unsigned int CM_getCtrlModule(CONTROL_MODULE module);


#endif /* defined(__control_module_H) */



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


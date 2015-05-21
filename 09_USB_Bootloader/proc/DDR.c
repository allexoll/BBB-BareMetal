//
//  DDR.c
//  
//
//  taken from https://github.com/auselen/down-to-the-bone example runtime (DDR init)
//
//


#include <stdint.h>
#include "../core/llma.h"
#include "DDR.h"

#define DBG(X)	;//printf("DEBUG %x\n",(X))

#ifndef u32
# define u32	uint32_t
#endif


#define writel(V,A)	PUT32(A,V)

#define readl(A)	GET32(A)




void enable_emif_clocks_x(void)
{
   /* Enable the  EMIF_FW Functional clock */
   //        writel(PRCM_MOD_EN, &cmper->emiffwclkctrl);
   /* Enable EMIF0 Clock */
   //        writel(PRCM_MOD_EN, &cmper->emifclkctrl);
   /* Poll if module is functional */
   //        while ((readl(&cmper->emifclkctrl)) != PRCM_MOD_EN)
   
   
   /* Enable the  EMIF_FW Functional clock */
   writel(0x00000002, 0x44E000D0); // ref 8.1.12.1.38, EMIF firewall clocks, module fully functional, and enabled
   /* Enable EMIF0 Clock */
   writel(0x00000002, 0x44E00028); // ref 8.1.12.1.9, manage EMIF clocks, module fully functional, and enabled
   /* Poll if module is functional */
   while ((readl(0x44E00028)) != 0x02)
      ;
}


void ddr_pll_config_x(void)
{
   u32 clkmode, clksel, div_m2;
   
   //        clkmode = readl(&cmwkup->clkmoddpllddr);
   //        clksel = readl(&cmwkup->clkseldpllddr);
   //        div_m2 = readl(&cmwkup->divm2dpllddr);
   
   /* Set the PLL to bypass Mode */
   //        clkmode = (clkmode & CLK_MODE_MASK) | PLL_BYPASS_MODE;
   //        writel(clkmode, &cmwkup->clkmoddpllddr);
   
   /* Wait till bypass mode is enabled */
   //        while ((readl(&cmwkup->idlestdpllddr) & ST_MN_BYPASS)
   //                                != ST_MN_BYPASS)
   //                ;
   
   //        clksel = clksel & (~CLK_SEL_MASK);
   //        clksel = clksel | ((ddrpll_m << CLK_SEL_SHIFT) | DDRPLL_N);
   //        writel(clksel, &cmwkup->clkseldpllddr);
   
   //        div_m2 = div_m2 & CLK_DIV_SEL;
   //        div_m2 = div_m2 | DDRPLL_M2;
   //        writel(div_m2, &cmwkup->divm2dpllddr);
   
   //        clkmode = (clkmode & CLK_MODE_MASK) | CLK_MODE_SEL;
   //        writel(clkmode, &cmwkup->clkmoddpllddr);
   
   /* Wait till dpll is locked */
   //        while ((readl(&cmwkup->idlestdpllddr) & ST_DPLL_CLK) != ST_DPLL_CLK)
   //                ;
   
   DBG(100);
   clkmode = readl(0x44E00494);
   clksel = readl(0x44E00440);
   div_m2 = readl(0x44E004A0);
   
   /* Set the PLL to bypass Mode */
   clkmode = (clkmode & 0xfffffff8) | 0x00000004;
   writel(clkmode, 0x44E00494);
   DBG(101);
   
   /* Wait till bypass mode is enabled */
   while ((readl(0x44E00434) & 0x00000100)
          != 0x00000100)
      ;
   DBG(102);
   
   clksel = clksel & (~0x7ffff);
   clksel = clksel | ((400 << 0x8) | ((24000000/1000000)-1) );
   writel(clksel, 0x44E00440);
   DBG(103);
   
   div_m2 = div_m2 & 0xFFFFFFE0;
   div_m2 = div_m2 | 1;
   writel(div_m2, 0x44E004A0);
   DBG(104);
   
   clkmode = (clkmode & 0xfffffff8) | 0x00000007;
   writel(clkmode, 0x44E00494);
   DBG(105);
   
   /* Wait till dpll is locked */
   while ((readl(0x44E00434) & 0x00000001) != 0x00000001)
      ;
   DBG(106);
}


/**
 * Configure DDR CMD control registers
 */
void config_cmd_ctrl_x(void)
{
   /*
    writel(cmd->cmd0csratio, &ddr_reg[0]->cm0csratio);
    writel(cmd->cmd0dldiff, &ddr_reg[0]->cm0dldiff);
    writel(cmd->cmd0iclkout, &ddr_reg[0]->cm0iclkout);
    writel(cmd->cmd1csratio, &ddr_reg[0]->cm1csratio);
    writel(cmd->cmd1dldiff, &ddr_reg[0]->cm1dldiff);
    writel(cmd->cmd1iclkout, &ddr_reg[0]->cm1iclkout);
    writel(cmd->cmd2csratio, &ddr_reg[0]->cm2csratio);
    writel(cmd->cmd2dldiff, &ddr_reg[0]->cm2dldiff);
    writel(cmd->cmd2iclkout, &ddr_reg[0]->cm2iclkout);
    */
   writel(0x00000080, 0x44E1201C); // ref 7.3.6.1 (CMD0), CMD slave ratio (adr/cmd launch timing), set to max acc to ref
   writel(0x00000001, 0x44E12028); // ref 7.3.6.2 (CMD0), Dll lock diff (jitter def), set to 1 wher 4 is max
   writel(0x00000000, 0x44E1202C); // ref 7.3.6.3 (CMD0), DRMA polarity inverter (clk inverted rel to core clk), set to 0 == not inverted
   
   writel(0x00000080, 0x44E12050); // see above, this is CMD1
   writel(0x00000001, 0x44E1205C); // see above, this is CMD1
   writel(0x00000000, 0x44E12060); // see above, this is CMD1
   
   writel(0x00000080, 0x44E12084); // see above, this is CMD2
   writel(0x00000001, 0x44E12090); // see above, this is CMD2
   writel(0x00000000, 0x44E12094); // see above, this is CMD2
   
}

/**
 * Configure DDR DATA registers
 */
void config_ddr_data_x_0(void)
{
   /*
    writel(data->datardsratio0, &ddr_reg[macrono]->dt0rdsratio0);
    writel(data->datawdsratio0, &ddr_reg[macrono]->dt0wdsratio0);
    writel(data->datawiratio0, &ddr_reg[macrono]->dt0wiratio0);
    writel(data->datagiratio0, &ddr_reg[macrono]->dt0giratio0);
    writel(data->datafwsratio0, &ddr_reg[macrono]->dt0fwsratio0);
    writel(data->datawrsratio0, &ddr_reg[macrono]->dt0wrsratio0);
    writel(data->datauserank0delay, &ddr_reg[macrono]->dt0rdelays0);
    writel(data->datadldiff0, &ddr_reg[macrono]->dt0dldiff0);
    */
   writel(0x00000038, 0x44E120C8); // ref 7.3.6.4 (CS0), ratio for read DQS slave DLL, set to 0x38
   writel(0x00000044, 0x44E120DC); // ref 7.3.6.5 (CS0), ratio for write DQS slave ratio, st to 0x44
   writel(0x00000000, 0x44E120F0); // ref 7.3.6.6 (CS0), write leveling FSM ratio, set to 0
   writel(0x00000000, 0x44E120FC); // ref 7.3.6.8 (CS0), DQS gate training init ratio, set to 0
   writel(0x00000094, 0x44E12108); // ref 7.3.6.10 (CS0), we fifo ratio value, set to 0x94
   writel(0x0000007D, 0x44E12120); // ref 7.3.6.11 (CS0), ratio value for write data slave, set to 0x7D
   writel(0x00000000, 0x44E12134); // ref 7.3.6.12 (CS0), delay selection, set to 0 mean each rank uses own delays
   writel(0x00000000, 0x44E12138); // no ref? CS0 DATA0_REG_PHY_DLL_LOCK_DIFF_0, DATA equivalent to CMD jitter (ref 7.3.6.2)?
}

void config_ddr_data_x_1(void)
{
   /*
    writel(data->datardsratio0, &ddr_reg[macrono]->dt0rdsratio0);
    writel(data->datawdsratio0, &ddr_reg[macrono]->dt0wdsratio0);
    writel(data->datawiratio0, &ddr_reg[macrono]->dt0wiratio0);
    writel(data->datagiratio0, &ddr_reg[macrono]->dt0giratio0);
    writel(data->datafwsratio0, &ddr_reg[macrono]->dt0fwsratio0);
    writel(data->datawrsratio0, &ddr_reg[macrono]->dt0wrsratio0);
    writel(data->datauserank0delay, &ddr_reg[macrono]->dt0rdelays0);
    writel(data->datadldiff0, &ddr_reg[macrono]->dt0dldiff0);
    */
   writel(0x00000038, 0x44E1216C); // ref 7.3.6.4 (CS1), ratio for read DQS slave DLL, set to 0x38
   writel(0x00000044, 0x44E12180); // ref 7.3.6.5 (CS1), ratio for write DQS slave ratio, st to 0x44
   writel(0x00000000, 0x44E12194); // ref 7.3.6.6 (CS1), write leveling FSM ratio, set to 0
   writel(0x00000000, 0x44E121A0); // ref 7.3.6.8 (CS1), DQS gate training init ratio, set to 0
   writel(0x00000094, 0x44E121AC); // ref 7.3.6.10 (CS1), we fifo ratio value, set to 0x94
   writel(0x0000007D, 0x44E121C4); // ref 7.3.6.11 (CS1), ratio value for write data slave, set to 0x7D
   writel(0x00000000, 0x44E121D8); // ref 7.3.6.12 (CS1), delay selection, set to 0 mean each rank uses own delays
   writel(0x00000000, 0x44E121DC); // no ref? CS1 DATA1_REG_PHY_DLL_LOCK_DIFF_0, DATA equivalent to CMD jitter (ref 7.3.6.2)?
}


void config_io_ctrl_x(void)
{
   /*
    writel(val, &ioctrl_reg->cm0ioctl);
    writel(val, &ioctrl_reg->cm1ioctl);
    writel(val, &ioctrl_reg->cm2ioctl);
    writel(val, &ioctrl_reg->dt0ioctl);
    writel(val, &ioctrl_reg->dt1ioctl);
    */
   writel(0x0000018B, 0x44E11408);
   // ref 9.3.89, ddr_cmd1_ioctrl
   // 	bits 31-21 are bitpairs for PU/PD settings, all set to no pull
   // 	bits 20-10 are bitpairs for PU/PD settings, all set to no pull
   // 	bits 9-8 clk I/O pads output slew rate, set to 1
   // 	bits 7-5 clk I/O pads output impedance, set to 4
   // 	bits 4-3 adr/cmd pads output slew rate, set to 1
   // 	bits 2-0 adr/cmd pads output impedance, set to 3
   
   writel(0x0000018B, 0x44E1140C);
   // ref 9.3.90, ddr_cmd2_ioctrl
   // 	see ref 9.3.89, ddr_cmd1_ioctrl
   
   writel(0x0000018B, 0x44E11410); // ???, not in ref?
   
   writel(0x0000018B, 0x44E11444);
   // ref 9.3.91, ddr_data1_ioctrl
   //	bit 29 and bit 19, PU/PD for DQS and its inverse, no pull
   //	bit 28 and 18, PU/PD for DM, no pull
   //	bit 27-20 and 17-10, PU/PD for DQ, no pull
   // 	bits 9-8 clk I/O pads output slew rate, set to 1
   // 	bits 7-5 clk I/O pads output impedance, set to 4
   // 	bits 4-3 adr/cmd pads output slew rate, set to 1
   // 	bits 2-0 adr/cmd pads output impedance, set to 3
   
   writel(0x0000018B, 0x44E11448); // ???, not in ref?
}


void config_ddr_phy_x(void)
{
   /*
    writel(regs->emif_ddr_phy_ctlr_1, &emif_reg->emif_ddr_phy_ctrl_1);
    writel(regs->emif_ddr_phy_ctlr_1, &emif_reg->emif_ddr_phy_ctrl_1_shdw);
    */
   writel(0x00100007,0x4C0000E4);
   // ref 7.3.5.33
   //	bit 20, precharge power down, activated
   //	bit 15, PHY macros reset, writing 1 holds macreos in reset, writing 0 takes them out of reset
   //	bit 13-12, control ODT (on die termination) while precharge power down is activated, ODT==0 means ODT off while precharge power down
   //	bit 11-10, ODT related, always set to 0
   //	bit 9-8, ODT ctlr when OE not is asserted and read is in progress, set to 0 means ODT off
   //	bit 4-0 read data latency set to 7
   writel(0x00100007,0x4C0000E8);
   // ref 7.3.5.34, shadow register to above, bit fields are the same.
}

void set_sdram_timings_x(void)
{
   /*
    writel(regs->sdram_tim1, &emif_reg->emif_sdram_tim_1);
    writel(regs->sdram_tim1, &emif_reg->emif_sdram_tim_1_shdw);
    writel(regs->sdram_tim2, &emif_reg->emif_sdram_tim_2);
    writel(regs->sdram_tim2, &emif_reg->emif_sdram_tim_2_shdw);
    writel(regs->sdram_tim3, &emif_reg->emif_sdram_tim_3);
    writel(regs->sdram_tim3, &emif_reg->emif_sdram_tim_3_shdw);
    */
   writel(0x0AAAD4DB,0x4C000018);
   // ref 7.3.5.7, timing paramter reg 1
   //	bit 28-25, tRP in clock cykles - 1
   //	bit 24-21, tRCD in clock cykles - 1
   //	bit 20-17, tWR in clock cykles - 1
   //	bit 16-12, tRAS in clock cykles - 1
   //	bit 11-6, tRC in clock cykles - 1
   //	bit 5-3, tRRD in clock cykles - 1
   //	bit 2-0, tWTR in clock cykles - 1
   writel(0x0AAAD4DB,0x4C00001C);
   // ref 7.3.5.8
   //	shadow reg for above
   writel(0x266B7FDA,0x4C000020);
   // ref 7.3.5.9, timing paramter reg 2
   //	bit 30-28, tXP in clock cykles - 1
   //	bit 27-25, tODT in clock cykles
   //	bit 24-16, tXSNR in clock cykles - 1
   //	bit 15-6, tXSRD in clock cykles - 1
   //	bit 5-3, tRTP in clock cykles - 1
   //	bit 2-0, tCKE in clock cykles - 1
   writel(0x266B7FDA,0x4C000024);
   // ref 7.3.5.10
   //	shadow reg for above
   writel(0x501F867F,0x4C000028);
   // ref 7.3.5.11, timing paramter reg 3
   //	bit 31-28, tPDLL_UL in clocks
   //	bit 20-15, tZQ_tZQCS in clocks
   //	bit 12-4, tRFC in clocks - 1
   //	bit 3-0, tRASmax, only valid for mDDR (==LPDDR1), shoud be 0xF for others
   writel(0x501F867F,0x4C00002C);
   // ref 7.3.5.12
   //	shadow reg for above
}


void config_sdram_x(void)
{
#if 0
   if (regs->zq_config) {
      /*
       * A value of 0x2800 for the REF CTRL will give us
       * about 570us for a delay, which will be long enough
       * to configure things.
       */
      writel(0x2800, &emif_reg->emif_sdram_ref_ctrl);
      writel(regs->zq_config, &emif_reg->emif_zq_config);
      writel(regs->sdram_config, &cstat->secure_emif_sdram_config);
      writel(regs->sdram_config, &emif_reg->emif_sdram_config);
      writel(regs->ref_ctrl, &emif_reg->emif_sdram_ref_ctrl);
      writel(regs->ref_ctrl, &emif_reg->emif_sdram_ref_ctrl_shdw);
   }
   writel(regs->ref_ctrl, &emif_reg->emif_sdram_ref_ctrl);
   writel(regs->ref_ctrl, &emif_reg->emif_sdram_ref_ctrl_shdw);
   writel(regs->sdram_config, &emif_reg->emif_sdram_config);
#endif
   //        if (regs->zq_config) {
   /*
    * A value of 0x2800 for the REF CTRL will give us
    * about 570us for a delay, which will be long enough
    * to configure things.
    */
   writel(0x2800, 0x4C000010);
   // ref 7.3.5.5, refresh ctrl reg
   //	bit 31, init/refresh disable (when set to 1)
   //	bit 29, DDR3 self refresh temp range, 0 is noremal temp range, 1 is extended
   //	bit 28, DDR3 auto self refresh enable (1 is enable)
   //	bit 26-24, PASR, 0 is full array
   //	bit 15-0, refresh rate, set to 0x2800
   //		Any write to 29, 28. 26-24 causes EMIF to start SDRAM init seq
   writel(0x50074BE4,0x4C0000C8);
   // ref 7.3.5.29, ZQ config reg
   //	bit 31, ZQ enable for CS1
   //	bit 30, ZQ enable for CS0
   //	bit 29, ZQ dual cal enable
   //	bit 28, ZQ enalbe on exit from self refresh, precharge power down or active power down
   //	bit 19-18, ZQCL intervals of ZQINIT - 1
   //	bit 17-16, ZQCL intervals of ZQCS - 1
   //	bit 15-0, ref periods between ZQCS cmds
   writel(0x61C05332,0x44E10110);
   // ref 9.3.5, "safe" storage for below register
   //	when resuming from lower power states, this register is copied to below
   writel(0x61C05332,0x4C000008);
   // ref 7.3.5.3, SDRAM config reg 1
   //	bit 31-29, SDRAM type, 3 for DDR3
   //	bit 28-27, internal bank position, 0 is lower address from OCP
   //		see tables for OCP address to DDR2/3/mDDR mapping
   //	bit 26-24, termination resistor value, 1 is RZQ/4
   //	bit 23, enable differential DQS, 1 is enabled
   //	bit 22-21, DDR3 dynamic ODT, 2 is RZQ/2
   //	bit 20, disable DLL select, 0 is not disable
   //	bit 19-18, SDRAM drive strength, 0 is RZQ/6
   //	bit 17-16, DDR3 CAS write latency, 0 is latency 5 clocks
   //	bit 15-14, bus width, 1 is 16 bit
   //	bit 13-10, CAS (read) latency, 4 is CAS lat 6
   //	bit 9-7, row size, 6 is 15 row bits
   //	bit 6-4, SDRAM internal banks, 3 is 8 banks
   //	bit 3, use one or two external CS, 0 is only use CS0
   //	bit 2-0, SDRAM page size, 2 is 1024 words of 16 bits => 2048 bytes
   writel(0x00000C30,0x4C000010);
   // see above, refresh rate is set to 0xC30
   writel(0x00000C30,0x4C000014);
   // ref 7.3.5.6, shadow reg for refresh rate (in bits 15-0)
   //        }
   writel(0x00000C30,0x4C000010);
   // see above, refresh rate is set to 0xC30
   writel(0x00000C30,0x4C000014);
   // ref 7.3.5.6, shadow reg for refresh rate (in bits 15-0)
   writel(0x61C05332,0x4C000008);
   // see above
}


static void config_vtp_x(void)
{
   //        writel(readl(&vtpreg->vtp0ctrlreg) | VTP_CTRL_ENABLE,
   //                        &vtpreg->vtp0ctrlreg);
   //        writel(readl(&vtpreg->vtp0ctrlreg) & (~VTP_CTRL_START_EN),
   //                        &vtpreg->vtp0ctrlreg);
   //        writel(readl(&vtpreg->vtp0ctrlreg) | VTP_CTRL_START_EN,
   //                        &vtpreg->vtp0ctrlreg);
   
   /* Poll for READY */
   //        while ((readl(0x44E10E0C) & VTP_CTRL_READY) !=
   //                        VTP_CTRL_READY)
   //                ;
   
   DBG(200);
   writel(readl(0x44E10E0C) | (0x1 << 6),
          0x44E10E0C);
   DBG(201);
   writel(readl(0x44E10E0C) & (~0x1),
          0x44E10E0C);
   DBG(202);
   writel(readl(0x44E10E0C) | 0x1,
          0x44E10E0C);
   DBG(203);
   
   /* Poll for READY */
   while ((readl(0x44E10E0C) & (0x1 << 5)) !=
          (0x1 << 5))
      ;
   DBG(204);
}


/*
 hard-coded for BBB
 - Micron DDR3L, P/N: MT41K256M16HA-125:E
 - DDR3L freq 400MHz (TI ASIC limitation? RAM can run on 800)
 - BBB main crystal freq 24MHz
 */
void config_ddr_x(void)
{
   DBG(1);
   enable_emif_clocks_x();
   DBG(2);
   ddr_pll_config_x();
   DBG(3);
   config_vtp_x();
   DBG(4);
   config_cmd_ctrl_x();
   DBG(5);
   
   config_ddr_data_x_0();
   DBG(6);
   config_ddr_data_x_1();
   DBG(7);
   
   config_io_ctrl_x();
   DBG(8);
   
   /* Set CKE to be controlled by EMIF/DDR PHY */
   //        writel(DDR_CKE_CTRL_NORMAL, &ddrctrl->ddrckectrl);
   writel(0x1,0x44E1131C);
   DBG(9);
   
   /* Program EMIF instance */
   config_ddr_phy_x();
   DBG(10);
   set_sdram_timings_x();
   DBG(11);
   config_sdram_x();
   DBG(12);
}

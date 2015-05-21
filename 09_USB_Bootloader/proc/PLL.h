//
//  PLL.h
//  
//
//  Created by Alexis Marquet on 28/04/15.
//
//

#ifndef ____PLL__
#define ____PLL__

#include <stdint.h>

uint32_t GetInputClockFrequency();

void MPU_PLL_Config(uint32_t clkin, uint32_t n, uint32_t m, uint32_t m2);

void CORE_PLL_Config(uint32_t clkin, uint32_t n, uint32_t m, uint32_t m4, uint32_t m5, uint32_t m6);

void DDR_PLL_Config(uint32_t clkin, uint32_t n, uint32_t m, uint32_t m2);

void PER_PLL_Config(uint32_t clkin, uint32_t n, uint32_t m, uint32_t m2);

void DISP_PLL_Config(uint32_t clkin, uint32_t n, uint32_t m, uint32_t m2);

#endif /* defined(____PLL__) */

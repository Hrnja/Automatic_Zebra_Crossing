#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

void InitPA5(void);
void initPWM_Timer3(void);
void Run_DC_1(uint32_t ccr1);


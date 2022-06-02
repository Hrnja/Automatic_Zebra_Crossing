#pragma once

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

void initPWM_Timer2(void);
void Servo1(uint32_t ccr1);
void Servo2(uint32_t ccr2);


#include "pwm_timer2.h"

TIM_HandleTypeDef htim2;

void initPWM_Timer2(void) {

	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Initialize pin PA0 and PA1 for timer 2
	//-------------------------------------------------------------------------------
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;			//Alternative mode with push-pull
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;  		//Choose from stm32f407-technical-paper
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Configure timer 2
	//TIM2 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
	//-------------------------------------------------------------------------------
	__HAL_RCC_TIM2_CLK_ENABLE();
	TIM_Base_InitTypeDef TIM_Base_InitStruct;
	TIM_Base_InitStruct.Prescaler = 84-1;			//Prescaler value = 84
	TIM_Base_InitStruct.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct.Period = 20000-1;			//Counter Period is 20 000 so we can get 50Hz freq
	TIM_Base_InitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Base_InitStruct.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	
	htim2.Instance = TIM2;
	htim2.Init = TIM_Base_InitStruct;
	
	HAL_TIM_PWM_Init(&htim2);	
	
	TIM_OC_InitTypeDef TIM_OC_InitStruct;
	TIM_OC_InitStruct.OCMode = TIM_OCMODE_PWM1;		//pwm mode
	TIM_OC_InitStruct.Pulse = 500;		
	TIM_OC_InitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct.OCFastMode = TIM_OCFAST_DISABLE;
	
	HAL_TIM_PWM_ConfigChannel(&htim2, &TIM_OC_InitStruct, TIM_CHANNEL_1);	//configure channel 1 PWM for servo1 
	HAL_TIM_PWM_ConfigChannel(&htim2, &TIM_OC_InitStruct, TIM_CHANNEL_2);	//configure channel 2 PWM for servo2
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);				//start pwm for channel 1
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);				//start pwm for channel 2
}

void Servo1(uint32_t ccr1){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,ccr1);			//set ccr1 value
}

void Servo2(uint32_t ccr2){
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,ccr2);			//set ccr2 value
}


//*************************************************************************
/*
Za potrebe ovog projekta je potreban ugao od 0 i 90.
0.5ms odgovara uglu 0, a 1.5ms odgovara uglu od 90.
*************************************************************************
*/







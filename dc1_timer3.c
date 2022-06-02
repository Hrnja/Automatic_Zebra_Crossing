#include "dc1_timer3.h"

TIM_HandleTypeDef htim3;

void InitPA5(void){
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// initialize PA5 pin for control speed
	
	GPIO_InitTypeDef GPIO_InitStruct5;
	__HAL_RCC_GPIOA_CLK_ENABLE();  				// Clock Enable
	
	
	GPIO_InitStruct5.Pin = GPIO_PIN_5;
  	GPIO_InitStruct5.Mode = GPIO_MODE_OUTPUT_PP;		//Output Push-pull mode
  	GPIO_InitStruct5.Pull = GPIO_NOPULL;
  	GPIO_InitStruct5.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  	
  	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct5);  			//Initialize pin
  	
  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
}



void initPWM_Timer3(void) {

	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Initialize pin PA6 for timer 3
	//-------------------------------------------------------------------------------
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStruct3;
	GPIO_InitStruct3.Pin = GPIO_PIN_6;
	GPIO_InitStruct3.Mode = GPIO_MODE_AF_PP;			//Alternative mode with push-pull
	GPIO_InitStruct3.Pull = GPIO_NOPULL;
	GPIO_InitStruct3.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct3.Alternate = GPIO_AF2_TIM3;  		//Choose from stm32f407-technical-paper
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct3);
	
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Configure timer 3
	//TIM3 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
	//-------------------------------------------------------------------------------
	
	__HAL_RCC_TIM3_CLK_ENABLE();
	TIM_Base_InitTypeDef TIM_Base_InitStruct3;
	TIM_Base_InitStruct3.Prescaler = 630-1;			//Prescaler value = 630
	TIM_Base_InitStruct3.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct3.Period = 1000-1;			//Counter Period is 1000 so we can get 133.3Hz freq
	TIM_Base_InitStruct3.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Base_InitStruct3.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	
	htim3.Instance = TIM3;
	htim3.Init = TIM_Base_InitStruct3;
	
	HAL_TIM_PWM_Init(&htim3);
	
	TIM_OC_InitTypeDef TIM_OC_InitStruct3;
	TIM_OC_InitStruct3.OCMode = TIM_OCMODE_PWM1;		//pwm mode
	TIM_OC_InitStruct3.Pulse = 500;		
	TIM_OC_InitStruct3.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct3.OCFastMode = TIM_OCFAST_DISABLE;
	
	HAL_TIM_PWM_ConfigChannel(&htim3, &TIM_OC_InitStruct3, TIM_CHANNEL_1);	//configure channel 1 PWM for dc1 	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);				//start pwm for channel 1

}

void Run_DC_1(uint32_t ccr1){
	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,ccr1);			//set ccr1 value
}





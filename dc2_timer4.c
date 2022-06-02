#include "dc2_timer4.h"

TIM_HandleTypeDef htim4;

void InitPA7(void){
	///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// initialize PA7 pin for control speed
	
	
	GPIO_InitTypeDef GPIO_InitStruct7;
	__HAL_RCC_GPIOA_CLK_ENABLE();  				// Clock Enable
	
	
	GPIO_InitStruct7.Pin = GPIO_PIN_7;
  	GPIO_InitStruct7.Mode = GPIO_MODE_OUTPUT_PP;		//Output Push-pull mode
  	GPIO_InitStruct7.Pull = GPIO_NOPULL;
  	GPIO_InitStruct7.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  	
  	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct7); 		//Initialize pin
  	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);

}

void InitPWM_Timer4(void) {

	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Initialize pin PB6 for timer 4
	//-------------------------------------------------------------------------------
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStruct6;
	GPIO_InitStruct6.Pin = GPIO_PIN_6;
	GPIO_InitStruct6.Mode = GPIO_MODE_AF_PP;			//Alternative mode with push-pull
	GPIO_InitStruct6.Pull = GPIO_NOPULL;
	GPIO_InitStruct6.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct6.Alternate = GPIO_AF2_TIM4;  		//Choose from stm32f407-technical-paper
	
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct6);
	
	
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	//Configure timer 4
	//TIM4 runs on APB1 @ 42MHz with multiplier 2 which makes it 84MHz
	//-------------------------------------------------------------------------------
	
	__HAL_RCC_TIM4_CLK_ENABLE();
	TIM_Base_InitTypeDef TIM_Base_InitStruct4;
	TIM_Base_InitStruct4.Prescaler = 630-1;			//Prescaler value = 840
	TIM_Base_InitStruct4.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Base_InitStruct4.Period = 1000-1;			//Counter Period is 1000 so we can get 100Hz freq
	TIM_Base_InitStruct4.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TIM_Base_InitStruct4.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	
	htim4.Instance = TIM4;
	htim4.Init = TIM_Base_InitStruct4;
	
	HAL_TIM_PWM_Init(&htim4);
	
	
	TIM_OC_InitTypeDef TIM_OC_InitStruct4;
	TIM_OC_InitStruct4.OCMode = TIM_OCMODE_PWM1;		//pwm mode
	TIM_OC_InitStruct4.Pulse = 500;		
	TIM_OC_InitStruct4.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OC_InitStruct4.OCFastMode = TIM_OCFAST_DISABLE;
	
	HAL_TIM_PWM_ConfigChannel(&htim4, &TIM_OC_InitStruct4, TIM_CHANNEL_1);	//configure channel 1 PWM for dc1 	
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);				//start pwm for channel 1

}

void Run_DC_2(uint32_t ccr1){
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,ccr1);			//set ccr1 value
}



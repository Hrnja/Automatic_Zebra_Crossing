#include "InitPinD.h"

void InitPinD(void) {
///wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	/// initialize 3 LED for traffic light 
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOD_CLK_ENABLE();  				// Clock Enable
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;		//Output Push-pull mode
  	GPIO_InitStruct.Pull = GPIO_NOPULL;
  	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  	
  	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); 		//Initialize pins
}

//Pin_0 = Red light
//Pin_1 = Yellow light
//Pin_2 = Green light

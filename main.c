#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "InitPinD.h"
#include "pwm_timer2.h"
#include "dc1_timer3.h"
#include "dc2_timer4.h"


void delay_ms_soft(uint32_t ms);


int main(void) {

	InitPinD();
	initPWM_Timer2();
	InitPA5();
	initPWM_Timer3();
	InitPA7();
	InitPWM_Timer4();
	
	
    while(1) 
    {     
    	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_RESET);
	  Run_DC_1(133);
	  Run_DC_2(133);
	  Servo1(1500);
	  Servo2(1500);
	  delay_ms_soft(10000);

	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_SET);
	  delay_ms_soft(1000);
	  
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);	  
	  Run_DC_1(0);
	  Run_DC_2(0);
	  Servo1(500);
	  Servo2(500);
	  delay_ms_soft(10000);
	  
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
	  delay_ms_soft(1000);
		
	
	
    }
}
void delay_ms_soft(uint32_t ms)
  {
  	volatile uint32_t k = 10500 * ms;
  	while(k--);
  }



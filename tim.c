#include "config.h"

TIM_HandleTypeDef tim4Init;
GPIO_InitTypeDef tim4Pin;

void tim4(void){
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();
	
	tim4Pin.Pin = GPIO_PIN_14;
	tim4Pin.Speed = GPIO_SPEED_FREQ_HIGH;
	tim4Pin.Mode = GPIO_MODE_AF_PP;
	tim4Pin.Pull = GPIO_NOPULL;
	tim4Pin.Alternate = GPIO_AF2_TIM4;
	
	HAL_GPIO_Init(GPIOD, &tim4Pin);
	
	tim4Init.Instance = TIM4;
	tim4Init.Init.Prescaler = 100;
	tim4Init.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim4Init.Init.Period = 300;
	
	HAL_TIM_Base_Init(&tim4Init);
}

void pwmSetPulse(uint16_t pulse){
	TIM_OC_InitTypeDef Tim_PWM_Init;
	
	HAL_TIM_PWM_Stop(&tim4Init, TIM_CHANNEL_3);
	
	Tim_PWM_Init.OCMode = TIM_OCMODE_PWM1;
	Tim_PWM_Init.OCPolarity = TIM_OCPOLARITY_HIGH;
	Tim_PWM_Init.OCFastMode = TIM_OCFAST_ENABLE;
	Tim_PWM_Init.OCIdleState = TIM_OCNIDLESTATE_RESET;
	Tim_PWM_Init.Pulse = pulse;
	
	HAL_TIM_PWM_ConfigChannel(&tim4Init, &Tim_PWM_Init, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&tim4Init, TIM_CHANNEL_3);
}

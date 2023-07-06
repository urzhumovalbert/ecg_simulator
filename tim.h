#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef tim4Init;
extern GPIO_InitTypeDef tim4Pin;

void tim4(void);
void pwmSetPulse(uint16_t pulse);
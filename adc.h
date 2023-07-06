#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef adcInit;
extern GPIO_InitTypeDef adcPinInit;
extern ADC_ChannelConfTypeDef adcChannelInit1;

extern void adc(void);

extern uint8_t value;

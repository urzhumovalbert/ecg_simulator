#include "config.h"

ADC_HandleTypeDef adcInit;
GPIO_InitTypeDef adcPinInit;
ADC_ChannelConfTypeDef adcChannelInit1;

void adc(void);
void ADC_IRQHandler(void);

uint8_t value = 0;

void adc(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_ADC1_CLK_ENABLE();
	
	adcPinInit.Pin = GPIO_PIN_5;
	adcPinInit.Speed = GPIO_SPEED_FREQ_HIGH;
	adcPinInit.Mode = GPIO_MODE_ANALOG;
	adcPinInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &adcPinInit);
	
	adcInit.Instance = ADC1;
	adcInit.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	adcInit.Init.Resolution = ADC_RESOLUTION_10B;
	adcInit.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adcInit.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	adcInit.Init.ContinuousConvMode = ENABLE;
	adcInit.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	adcInit.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	HAL_ADC_Init(&adcInit);
	
	adcChannelInit1.Channel = ADC_CHANNEL_5;
	adcChannelInit1.Rank = 1;
	adcChannelInit1.SamplingTime = ADC_SAMPLETIME_144CYCLES; //check
	HAL_ADC_ConfigChannel(&adcInit, &adcChannelInit1);
	
	HAL_NVIC_EnableIRQ(ADC_IRQn);
	HAL_ADC_Start_IT(&adcInit);
}

void ADC_IRQHandler(void){
	HAL_ADC_IRQHandler(&adcInit);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	if (hadc == &adcInit){
		value = (uint8_t)(HAL_ADC_GetValue(&adcInit) / 10);
		if (value > 100){
			value = 100;
		}
	}
}

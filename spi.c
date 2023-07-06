#include "config.h"

SPI_HandleTypeDef spi2Init;
GPIO_InitTypeDef spi2PinInit;
GPIO_InitTypeDef pinsCsResetInit;
GPIO_InitTypeDef pinRsInit;

void spi2(void);
void SPI2_IRQHandler(void);
void pinsInit(void);

/* pins correct? */
void spi2(void){
	
	/* SPI pin init port A*/
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	spi2PinInit.Pin = GPIO_PIN_13|GPIO_PIN_15;
	spi2PinInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	spi2PinInit.Mode = GPIO_MODE_AF_PP;
	spi2PinInit.Pull = GPIO_NOPULL;
	spi2PinInit.Alternate = GPIO_AF5_SPI1;	
	
	HAL_GPIO_Init(GPIOB, &spi2PinInit);

	__HAL_RCC_SPI2_CLK_ENABLE();
	
	spi2Init.Instance = SPI2;
	spi2Init.Init.Mode = SPI_MODE_MASTER;
	spi2Init.Init.Direction = SPI_DIRECTION_1LINE;
	spi2Init.Init.DataSize = SPI_DATASIZE_16BIT;
	spi2Init.Init.CLKPolarity = SPI_POLARITY_LOW;
	spi2Init.Init.CLKPhase = SPI_PHASE_1EDGE;
	spi2Init.Init.NSS = SPI_NSS_HARD_OUTPUT;
	spi2Init.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; //check
	spi2Init.Init.FirstBit = SPI_FIRSTBIT_MSB; /* MSB - Most Significant Bit */
	
	HAL_SPI_Init(&spi2Init);
	HAL_NVIC_EnableIRQ(SPI2_IRQn);
}

void SPI2_IRQHandler(void){	
	HAL_SPI_IRQHandler(&spi2Init);	
}

void pinsInit(void){
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	pinsCsResetInit.Pin = GPIO_PIN_4|GPIO_PIN_11;
	pinsCsResetInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinsCsResetInit.Mode = GPIO_MODE_OUTPUT_PP;
	pinsCsResetInit.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOB, &pinsCsResetInit);
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	pinRsInit.Pin = GPIO_PIN_8;
	pinRsInit.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	pinRsInit.Mode = GPIO_MODE_OUTPUT_PP;
	pinRsInit.Pull = GPIO_NOPULL;
	
	HAL_GPIO_Init(GPIOA, &pinRsInit);
}

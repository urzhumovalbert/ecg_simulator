#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef spi2Init;
extern GPIO_InitTypeDef spi2PinInit;
extern GPIO_InitTypeDef pinsCsResetInit;
extern GPIO_InitTypeDef pinRsInit;

void pinsInit(void);
void spi2(void);
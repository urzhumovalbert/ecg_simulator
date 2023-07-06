#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include <stdio.h>

#define TFT_RESET_Reset         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET)  
#define TFT_RESET_Set           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET)
#define TFT_CS_Reset            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET)
#define TFT_CS_Set              HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET)
#define TFT_data                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET)
#define TFT_index               HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET)
#define TFT_clear() TFT_fillDisplay(TFT_COLOR_clear)
#define TFT_RGB(R, G, B) (((B >> 3)) | ((G >> 2) << 5) | ((R >> 3) << 11))

enum COLOR
{
	TFT_COLOR_Black = TFT_RGB(0, 0, 0),
	TFT_COLOR_Gray  = TFT_RGB(96, 96, 96),
	TFT_COLOR_Silver = TFT_RGB(192, 192, 192),
	TFT_COLOR_White = TFT_RGB(255, 255, 255),
	TFT_COLOR_Fuchsia = TFT_RGB(255, 0, 255),
	TFT_COLOR_Purple = TFT_RGB(128, 0, 128),
	TFT_COLOR_Red = TFT_RGB(255, 0, 0),
	TFT_COLOR_Maroon = TFT_RGB(128, 0, 0),
	TFT_COLOR_Yellow = TFT_RGB(255, 255, 0),
	TFT_COLOR_Orange = TFT_RGB(255, 128, 0),
	TFT_COLOR_Lime = TFT_RGB(0, 255, 0),
	TFT_COLOR_Green = TFT_RGB(0, 128, 0),
	TFT_COLOR_Aqua = TFT_RGB(0, 255, 255),
	TFT_COLOR_Teal = TFT_RGB(0, 128, 128),
	TFT_COLOR_Blue = TFT_RGB(0, 0, 255),
	TFT_COLOR_Navy = TFT_RGB(0, 0, 128),
	TFT_COLOR_clear = TFT_COLOR_Black,
	TFT_COLOR_none = 1
};

enum ORIENTATION {
    TFT_ORIENT_PORTRAIT, //portrait, pin1 (0;0)
    TFT_ORIENT_LANDSCAPE_180, //landscape, display cable (0;0)
    TFT_ORIENT_PORTRAIT_180, //portrait, pin40 (0;0)
    TFT_ORIENT_LANDSCAPE //landscape, pin1(?) (0;0)
};

extern SPI_HandleTypeDef *_displaySPI;
extern uint16_t TFT_Width, TFT_Height;
extern uint8_t TFT_currentOrientation;
extern uint16_t TFT_cursorX, TFT_cursorY;
extern uint16_t currentColor;

void TFT_reset(void);
void TFT_init(uint8_t orientation, SPI_HandleTypeDef *displaySPI);
void TFT_sendData(uint16_t data);
void TFT_sendCmd(uint16_t cmd, uint16_t data);
void TFT_setOrientation(uint8_t orientation);
void TFT_fillDisplay(uint16_t color);
void TFT_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void TFT_Off(void);
void TFT_On(void);
void TFT_setColor(uint16_t color);
uint16_t TFT_getColor(void);
void TFT_setCursor(uint16_t X, uint16_t Y);
uint16_t TFT_getCursorX(void);
uint16_t TFT_getCursorY(void);
void TFT_drawPixel(uint16_t x, uint16_t y, uint16_t color);
void TFT_drawLineHorizontal(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color);
void TFT_drawLineVertical(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color);
void TFT_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint16_t color);
void TFT_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void TFT_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t size, uint16_t color);



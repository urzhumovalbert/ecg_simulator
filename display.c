#include "display.h"
#include <stdlib.h>

SPI_HandleTypeDef *_displaySPI;

uint16_t TFT_Width, TFT_Height; //display width and height

uint8_t TFT_currentOrientation; //current display orientation

uint16_t currentColor; //current color

uint16_t TFT_cursorX, TFT_cursorY; // current cursor coordinates

/* display reset function */
void TFT_reset(void) 
{
    TFT_RESET_Reset;
    HAL_Delay(1);
    TFT_RESET_Set;
    HAL_Delay(1);
}

void TFT_sendData(uint16_t data)
{
	uint16_t buff[1] = {data};
	HAL_SPI_Transmit(_displaySPI, (uint8_t *)buff, 1, 0xFF);
}
void TFT_sendCmd(uint16_t cmd, uint16_t data)
{
	TFT_index;
	TFT_sendData(cmd);
	TFT_data;
	TFT_sendData(data);
}

void TFT_setOrientation(uint8_t orientation)
{
	TFT_currentOrientation = orientation;
	switch(orientation)
	{
		case 0:
				TFT_sendCmd(0x003, 0x10A0);
				TFT_Width = 240;
				TFT_Height = 320;
				break;
		case 1:
				TFT_sendCmd(0x003, 0x1098);
				TFT_Width = 320;
				TFT_Height = 240;
				break;
		case 2:
				TFT_sendCmd(0x003, 0x1080);
				TFT_Width = 240;
				TFT_Height = 320;
				break;
		case 3:
				TFT_sendCmd(0x003, 0x10A8);
				TFT_Width = 320;
				TFT_Height = 240;
				break;
	}
}

void TFT_init(uint8_t orientation, SPI_HandleTypeDef *displaySPI)
{
	_displaySPI = displaySPI;
	TFT_CS_Set;
	TFT_reset();
	TFT_CS_Reset;
	
	TFT_sendCmd(0x000,0x0001); //oscillator
	HAL_Delay(10);
	
	TFT_sendCmd(0x100, 0x0000); //display OFF         
	TFT_sendCmd(0x101, 0x0000); //clock OFF        
	TFT_sendCmd(0x102, 0x3100); //frequency converter setup      
	TFT_sendCmd(0x103, 0xe200); //voltage setup        
	TFT_sendCmd(0x110, 0x009d); //matrix voltage amplitude setup        
	TFT_sendCmd(0x111, 0x0022); //current setup        
	TFT_sendCmd(0x100, 0x0120); //op amp ON, voltage generator ON       
	HAL_Delay(20);
	TFT_sendCmd(0x100, 0x3120); //supply ON
	HAL_Delay(80);
	
	TFT_sendCmd(0x001, 0x0100); //display orientation    
	TFT_sendCmd(0x002, 0x0000); //driver signal shape
	TFT_sendCmd(0x003, 0x1230); //input mode
	TFT_sendCmd(0x006, 0x0000); //image movement control
	TFT_sendCmd(0x007, 0x0101); //display OFF
	TFT_sendCmd(0x008, 0x0808); //border setup (?)
	TFT_sendCmd(0x009, 0x0000); //scan setup (?)
	TFT_sendCmd(0x00b, 0x0000); //colors setup
	TFT_sendCmd(0x00c, 0x0000); //RGB interface setup
	TFT_sendCmd(0x00d, 0x0010); //refresh rate setup
	/* LTPS setup */
	TFT_sendCmd(0x012, 0x0000);
	TFT_sendCmd(0x013, 0x0000);    
	TFT_sendCmd(0x018, 0x0000);
	TFT_sendCmd(0x019, 0x0000);
	
	TFT_sendCmd(0x203, 0x0000); //GRAM mask (?)
	TFT_sendCmd(0x204, 0x0000); //GRAM mask (?)
	
	/* active area (data transmit)*/
	TFT_sendCmd(0x210, 0x0000); //hor start
	TFT_sendCmd(0x211, 0x00ef); //hor end
	TFT_sendCmd(0x212, 0x0000); //ver start
	TFT_sendCmd(0x213, 0x013f); //ver end
	
	/* active area (moving image)*/
	TFT_sendCmd(0x214, 0x0000); //hor start
	TFT_sendCmd(0x215, 0x0000); //hor end
	TFT_sendCmd(0x216, 0x0000); //ver start
	TFT_sendCmd(0x217, 0x0000); //ver end
	
	/* grayscale */
	TFT_sendCmd(0x300, 0x5343);
	TFT_sendCmd(0x301, 0x1021);
	TFT_sendCmd(0x302, 0x0003);
	TFT_sendCmd(0x303, 0x0011);
	TFT_sendCmd(0x304, 0x050a);
	TFT_sendCmd(0x305, 0x4342);
	TFT_sendCmd(0x306, 0x1100);
	TFT_sendCmd(0x307, 0x0003);
	TFT_sendCmd(0x308, 0x1201);
	TFT_sendCmd(0x309, 0x050a);
	
	/* RAM access setup */
	TFT_sendCmd(0x400, 0x4027);
	TFT_sendCmd(0x401, 0x0000);
	TFT_sendCmd(0x402, 0x0000); //First screen drive position (1)       
	TFT_sendCmd(0x403, 0x013f); //First screen drive position (2)       
	TFT_sendCmd(0x404, 0x0000);
	
	/* display orientation setup */
	TFT_setOrientation(orientation);
	
	/* current pixel */
	TFT_sendCmd(0x200, 0x0000); //hor
	TFT_sendCmd(0x201, 0x0000); //ver
	
	TFT_sendCmd(0x100, 0x7120); //display supply ON
	TFT_sendCmd(0x007, 0x0103); //image resolution
	HAL_Delay(10);
	TFT_sendCmd(0x007, 0x0113); //keys ON (?)
	
	TFT_CS_Set; 
}

void TFT_setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	uint16_t x0a, x1a, y0a, y1a;

	switch(TFT_currentOrientation)
	{
			case 1:
					x0a = x0;
					x1a = x1;
					y0a = y0;
					y1a = y1;

					x0 = y0a;
					x1 = y1a;
					y0 = TFT_Width - 1 - x1a;
					y1 = TFT_Width - 1 - x0a;
					break;
			case 2:
					x0a = x0;
					x1a = x1;
					y0a = y0;
					y1a = y1;

					x0 = TFT_Width - 1 - x1a;
					x1 = TFT_Width - 1 - x0a;
					y0 = TFT_Height - 1 - y1a;
					y1 = TFT_Height - 1 - y0a;
					break;
			case 3:
					x0a = x0;
					x1a = x1;
					y0a = y0;
					y1a = y1;

					x0 = TFT_Height - 1 - y1a;
					x1 = TFT_Height - 1 - y0a;
					y0 = x0a;
					y1 = x1a;
					break;
	}
	TFT_sendCmd(0x0210, x0);
	TFT_sendCmd(0x0211, x1);
	TFT_sendCmd(0x0212, y0);
	TFT_sendCmd(0x0213, y1);
	TFT_sendCmd(0x0200, x0);
	TFT_sendCmd(0x0201, y0);
	TFT_index;                   
	TFT_sendData(0x202);         
}

void TFT_fillDisplay(uint16_t color)
{
	TFT_CS_Reset;
	
	TFT_setWindow(0,0, TFT_Width-1, TFT_Height-1);
	
	TFT_data;
	
	for (uint32_t i = TFT_Width*TFT_Height; i != 0; i--) 
	{
		TFT_sendData(color);
	}
	TFT_CS_Set; 
	TFT_cursorX = 0;
	TFT_cursorY = 0;
}

void TFT_Off(void)
{
	TFT_RESET_Reset;
}

void TFT_On(void) 
{
	TFT_init(TFT_currentOrientation, _displaySPI);
}

void TFT_setColor(uint16_t color)
{
	currentColor = color;
}

uint16_t TFT_getColor(void)
{
	return currentColor;
}

void TFT_setCursor(uint16_t X, uint16_t Y)
{
	TFT_cursorX = X;
	TFT_cursorY = Y;
}

uint16_t TFT_getCursorX(void)
{
	return TFT_cursorX;
}

uint16_t TFT_getCursorY(void)
{
	return TFT_cursorY;
}

void TFT_drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	TFT_CS_Reset;                  
	TFT_setWindow(x,y,x,y);
	TFT_data;                       
	TFT_sendData(color);            
	TFT_CS_Set;                    
	TFT_cursorX = x+1;
	TFT_cursorY = y;
}

void TFT_drawLineHorizontal(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color)
{
	TFT_CS_Reset;                            
	TFT_setWindow(x,y,x+len-1,y+size-1);
	TFT_data;                               
	for(uint16_t i = 0; i < len*size; i++)
		TFT_sendData(color); 
	TFT_CS_Set;                              
	TFT_cursorX = x+size+1;
	TFT_cursorY = y;
}

void TFT_drawLineVertical(uint16_t x, uint16_t y, uint16_t len, uint8_t size, uint16_t color)
{
	TFT_CS_Reset;                            
	TFT_setWindow(x,y,x+size-1,y+len-1);
	TFT_data;                                
	for(uint16_t i = 0; i < len*size; i++)
		TFT_sendData(color); 
	TFT_CS_Set;                             
	TFT_cursorX = x+1;
	TFT_cursorY = y+len;
}

void TFT_drawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, uint16_t color)
{
	TFT_drawLineHorizontal(x, y, width, size, color);
	TFT_drawLineHorizontal(x, y+height-size, width, size, color);
	TFT_drawLineVertical(x, y, height, size, color);
	TFT_drawLineVertical(x+width-size, y, height, size, color);
}

void TFT_fillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
	TFT_CS_Reset;                                
	TFT_setWindow(x,y,x+width-1,y+height-1);
	TFT_data;                                      
	for (uint32_t i = width*height; i != 0; i--)
	{
		TFT_sendData(color);
	}                    
	TFT_CS_Set;                                   
}

void TFT_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t size, uint16_t color)
{
	int16_t dx = abs(x1-x0);
	int16_t sx = x0 < x1 ? 1 : -1;
	int16_t dy = -abs(y1-y0), sy = y0 < y1 ? 1 : -1;
	int16_t err = dx+dy, e2;
	for (;;)
	{
		TFT_fillRectangle(x0,y0,size, size, color);
		e2 = 2*err;
		if (e2 >= dy) 
		{
			if (x0 == x1) 
				break;
			err += dy; x0 += sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1) 
				break;
			err += dx; y0 += sy;
		}
	}
	TFT_cursorX = x1+1;
	TFT_cursorY = y1;
}


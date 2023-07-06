#include "config.h"

void SystemClock_Config(void);
void SysTick_Handler(void);

int main(void){
	SystemClock_Config();
	SysTick_Handler();
	tim4();
	spi2();
	pinsInit();
	adc();
	
	/*draw*/
	uint16_t xdPoints[] = {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
												120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120};
	uint16_t ydPoints[] = {0, 	 12, 	24,  36,  48,  60,  72,  84,  96,		108, 120, 132, 144,
												156, 168, 180, 192, 204, 216, 228, 240, 252, 264, 276, 288, 300, 319};
	
	uint16_t xPoints[] =  {120, 120, 100, 150, 120, 120, 220, 20,  180, 120, 160, 90,  120};
	uint16_t yPoints[] =  {0, 	 60, 	80,  120, 140, 160, 180, 200, 240, 260, 270, 300, 319};
	
	uint8_t i;
	
	/*init*/
	TFT_init(TFT_ORIENT_PORTRAIT, &spi2Init);
	TFT_clear();
	
	while (1){
		if (value <= 25){
			pwmSetPulse(100);
			for(i = 0;; i++){
				if (value > 25){
					pwmSetPulse(0);
					TFT_clear();
					break;
				}
				if (i < 26){
					TFT_drawLine(xdPoints[i], ydPoints[i], xdPoints[i + 1], ydPoints[i + 1], 3, TFT_COLOR_Green); // smooth draw
					HAL_Delay(5);
				}
			}
		}		
		if (value > 25 && value <= 50){
			for (i = 0; i < 12; i++){
				if (value <= 25 && value > 50){
					pwmSetPulse(0);
					TFT_clear();
					break;
				}
				if (i == 6){
					pwmSetPulse(100);
					HAL_Delay(50);
				}
				if (i == 9) pwmSetPulse(0);
				TFT_drawLine(xPoints[i], yPoints[i], xPoints[i+1], yPoints[i+1], 3, TFT_COLOR_Green);
			}
		}
		if (value > 50 && value <= 75){
			for (i = 0; i < 12; i++){
				if (value <= 50 && value > 75){
					pwmSetPulse(0);
					TFT_clear();
					break;
				}
				if (i == 6){
					pwmSetPulse(100);
					HAL_Delay(25);
				}
				if (i == 9) pwmSetPulse(0);
				TFT_drawLine(xPoints[i], yPoints[i], xPoints[i+1], yPoints[i+1], 3, TFT_COLOR_Green);
			}
		}
		if (value > 75 && value <= 100){
			for (i = 0; i < 12; i++){
				if (value <= 25 && value > 50){
					pwmSetPulse(0);
					TFT_clear();
					break;
				}
				if (i == 6){
					pwmSetPulse(100);
					HAL_Delay(10);
				}
				if (i == 9) pwmSetPulse(0);
				TFT_drawLine(xPoints[i], yPoints[i], xPoints[i+1], yPoints[i+1], 3, TFT_COLOR_Green);
			}
		}
		if (value > 25 && value <= 50){
			HAL_Delay(100); // low BPM
		}
		if (value > 50 && value <= 75){
			HAL_Delay(50); // normal BPM
		}
		if (value > 75 && value <= 100){
			HAL_Delay(25); // high BPM
		}
		TFT_clear();
	}
}


/*initializing functions below*/

/* setting system clock */
void SystemClock_Config(void){
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

/*HAL tick counter*/
void SysTick_Handler(void){
	HAL_IncTick();
}

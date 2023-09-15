/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "api_handle_display.h"
#include "api_keypad.h"
#include "api_rc522.h"
#include "api_flash.h"
#include <stdio.h>
#include <stdbool.h>
#include "bsp_spi.h"
#include "driver_rc522.h"
#include "driver_flash.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c3;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
//debug
//uint8_t second;
//uint8_t minute;
//uint8_t hour;
//uint8_t dow;
//uint8_t date;
//uint8_t month;
//uint16_t year;
uint8_t a=0;
uint8_t b=0;
volatile bool state = false;
volatile bool flag = true;
volatile uint8_t wrong = 0;

#define MAX_ROWS2 5
#define MAX_COLS2 4
uint8_t password[4] = { 1, 2, 3, 4 };
uint8_t password2[4] = { 5, 6, 7, 9 };
uint8_t all_pass[20][4] = { 0 };
// Khai báo các trạng thái
typedef enum {
	IDLE_STATE,
	CHECK_CARD_STATE,
	ENTER_PASSWORD_STATE,
	CHECK_PASSWORD_TIMEOUT_STATE,
	CHANGE_PASS_ADD_CARD_STATE,
	ADD_CARD_STATE,
	TAP_NEW_CARD_STATE,
	CHANGE_PASS_STATE,
	ENTER_NEW_PASSWORD_STATE,
	BLOCK_STATE
} State;

// Khai báo biến trạng thái hiện tại
State current_state = IDLE_STATE;
uint8_t my_index = 0;

keypad_name keypad;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C3_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
	//
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */
	//
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	//
	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM3_Init();
	MX_I2C1_Init();
	MX_I2C3_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */

	flash_load();
//	bspGetSPI(&hspi1);
//	mfrc522_init();
//	lcd_init(&hi2c3);
//	ds1307_init(&hi2c1);
//	ds1307_set_date_time (50, 56, 11, 6, 1, 9, 2023);
//	HAL_TIM_Base_Start_IT(&htim3);
//
//	//keypad_name keypad;
//	api_keypad_init(&keypad, GPIOB, GPIO_PIN_10, GPIOB, GPIO_PIN_4,
//			GPIOB,	GPIO_PIN_5, GPIOB, GPIO_PIN_3,
//			GPIOA, GPIO_PIN_10, GPIOA, GPIO_PIN_2,
//			GPIOA, GPIO_PIN_3);
//
//	handle_state_master_card();
//	time_delay(1000);


	my_index = read_password_from_flash(0x0800C000, all_pass, 20, 6);

	save_password_to_flash(0x0800C000, password2, 4, my_index);

	// get current pass : all_pass[debug][4]
	//save_password_to_flash(0x0800C000, password2, 4, debug);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
//		switch (current_state) {
//
//		case IDLE_STATE:
//			// Kiểm tra cờ để hiển thị thời gian trên LCD
//			if (flag)
//			{
//				h_display_time();
//				flag = false;
//			}
//
//			// Kiểm tra sự có mặt của thẻ
//			if (check_have_card())
//			{
//				current_state = CHECK_CARD_STATE;
//			}
//
//			// Kiểm tra nút bấm keypad
//			if (api_check_have_button(&keypad))
//			{
//				// Nếu nút '*' được nhấn, chuyển đến trạng thái nhập mật khẩu
//				if (api_check_button(&keypad, '*'))
//				{
//					current_state = ENTER_PASSWORD_STATE;
//				}
//				// Nếu nút '#' được nhấn, chuyển đến trạng thái chọn chế độ thay đổi mật khẩu hoặc thêm thẻ
//				else if (api_check_button(&keypad, '#'))
//				{
//					current_state = CHANGE_PASS_ADD_CARD_STATE;
//				}
//			}
//			break;
//
//		case CHECK_CARD_STATE:
//			// Kiểm tra xem thẻ có hợp lệ không
//			if (check_card_to_access())
//			{
//				open_door();
//				a++;
//
//			}
//			else
//			{
//				h_wrong_card();
//			}
//
//
//			current_state = IDLE_STATE;
//			break;
//
//		case ENTER_PASSWORD_STATE:
//			// Gọi hàm nhập mật khẩu
//			if (api_enter_pass(&keypad, password))
//			{
//				current_state = CHECK_PASSWORD_TIMEOUT_STATE;
//				state = false; //
//			}
//			else
//			{
//				h_timeout();
//				current_state = IDLE_STATE;
//			}
//			break;
//
//		case CHECK_PASSWORD_TIMEOUT_STATE:
//			// Kiểm tra nút bấm và timeout
//			if (api_check_button_timeout(&keypad, '#', 10000))
//			{
//				// Kiểm tra xem mật khẩu có chính xác không
//				//if (!check_password())
//				if (1) // test // 1:SAI
//				{
//					wrong++;
//					if (wrong > 3)
//					{
//						h_block();
//						//h_timeout();
//						b++;
//						wrong = 0;
//						current_state = BLOCK_STATE;
//					}
//					else
//					{
//						h_wrong_pass();
//						current_state = ENTER_PASSWORD_STATE;
//					}
//				}
//				else
//				{
//					if (state)
//					{
//						current_state = ENTER_NEW_PASSWORD_STATE;
//					}
//					else
//					{
//						open_door();
//						a++;
//						wrong = 0;
//						current_state = IDLE_STATE;
//					}
//				}
//			}
//			else
//			{
//				h_timeout();
//				wrong = 0;
//				current_state = IDLE_STATE;
//			}
//			break;
//
//		case CHANGE_PASS_ADD_CARD_STATE:
//			// Hiển thị các tùy chọn chế độ
//			h_display_choose_mode();
//
//			// Kiểm tra nút bấm và timeout
//			if (api_check_have_button_timeout(&keypad, 10000))
//			{
//				// Nếu nút '7' được nhấn, chuyển đến trạng thái chờ thẻ Master
//				if (api_check_button(&keypad, '7'))
//				{
//					current_state = ADD_CARD_STATE;
//				}
//				// Nếu nút '8' được nhấn, chuyển đến trạng thái nhập mật khẩu hiện tại
//				else if (api_check_button(&keypad, '8'))
//				{
//					current_state = CHANGE_PASS_STATE;
//				}
//			}
//			else
//			{
//				h_timeout();
//				current_state = IDLE_STATE;
//			}
//			break;
//
//		case ADD_CARD_STATE:
//			h_display_tap_master_card();
//
//			// Kiểm tra sự có mặt của thẻ và timeout
//			if (check_have_card_with_timeout())
//			{
//				// Kiểm tra xem thẻ có phải là thẻ Master không
//				if (check_master_card())
//				{
//					current_state = TAP_NEW_CARD_STATE;
//					time_delay(1000);
//				}
//				else
//				{
//					h_wrong_card();
//					current_state = IDLE_STATE;
//				}
//			}
//			else
//			{
//				h_timeout();
//				current_state = IDLE_STATE;
//			}
//			break;
//
//		case TAP_NEW_CARD_STATE:
//			h_display_tap_new_card();
//
//			// Kiểm tra sự có mặt của thẻ và timeout
//			if (check_have_card_with_timeout())
//			{
//				// Kiểm tra xem thẻ đã được đăng ký hay chưa
//				if (!check_card_to_access())
//				{
//					a++;
//					add_new_sub_card();
//
//					// ...
//				}
//			}
//			else
//			{
//				h_timeout();
//			}
//
//			current_state = IDLE_STATE;
//			break;
//
//		case CHANGE_PASS_STATE:
//			h_display_enter_current_pass();
//
//			// Nhập mật khẩu hiện tại
//			if (api_enter_pass(&keypad, password))
//			{
//				current_state = CHECK_PASSWORD_TIMEOUT_STATE;
//				state = true;
//				//				//if (check_password())
//				//				if(1) //test
//				//				{
//				//					current_state = ENTER_NEW_PASSWORD_STATE;
//				//				}
//			}
//			else
//			{
//				h_timeout();
//				current_state = IDLE_STATE;
//			}
//			break;
//
//		case ENTER_NEW_PASSWORD_STATE:
//			h_display_enter_new_pass();
//
//			// Kiểm tra nút bấm và timeout
//			if (api_enter_pass(&keypad, password))
//			{
//				if (api_check_button_timeout(&keypad,'#',10000))
//				{
//					//flash_save_pass();
//				}
//				else
//				{
//					h_timeout();
//				}
//			}
//			else
//			{
//				h_timeout();
//			}
//
//			current_state = IDLE_STATE;
//			break;
//
//		case BLOCK_STATE:
//			// Hiển thị thông báo hệ thống bị tạm khóa
//			h_block();
//
//			current_state = IDLE_STATE;
//			break;
//		}
	}
}





//		//debug-----------------------------
////		//second
////		second = ds1307_get_second();
////		//minute
////		minute = ds1307_get_minute();
////		//hour
////		hour = ds1307_get_hour();
////		//dow
////		dow = ds1307_get_dayofweek();
////		//date
////		date = ds1307_get_date();
////		//month
////		month = ds1307_get_month();
////		//year
////		year = ds1307_get_year();
//		//-------------------------------------
//
//		// check flag --> display time on LCD, flag = true every interrupt timer 1s
//		if (flag)
//		{
//			h_display_time();
//			flag = false;
//		}
//
//		//check card
//		if (check_have_card())
//		{
//			if (check_car())
//			{
//				open_door();
//			}
//			else
//			{
//				h_display_wrong_card();
//			}
//		}
//
//		// check button keypad
//		if (api_check_have_button(&keypad))
//		{
//			if (api_check_button(&keypad, '*'))
//			{
//				while(1)
//				{
//				if (enter_pass()) // func enter_pass return 1 if full 4 number, 0 if timeout
//				{
//					if (check_button_with_timeout())
//					{
//						if (!check_password())
//						{
//							wrong++;
//							if (wrong>3)
//							{
//								h_block();
//								h_timeout();
//								wrong = 0;
//								break;
//							}
//							else
//								h_wrong_pass();
//						}
//						else
//						{
//							open_door();
//							wrong = 0;
//							break;
//						}
//					}
//					else
//					{
//						h_timeout();
//						wrong = 0;
//						break;
//					}
//				}
//				else
//				{
//					h_timeout();
//					wrong = 0;
//					break;
//				}
//				}
//			}
//
//			else if (api_check_button(&keypad, '#'))
//			{
//				while(1)
//				{
//					h_display_choose_mode();
//					if (api_check_have_button_timeout(&keypad, 10000))
//					{
//						if (api_check_button(&keypad, '7'))
//						{
//							while(1)
//							{
//								h_display_tap_master_card();
//								if (check_have_card_with_timeout())
//								{
//									if (check_master_card())
//									{
//										while(1)
//										{
//											h_display_tap_new_card();
//											if (check_have_card_with_timeout())
//											{
//												if (!check_card())
//												{
//													save_card();
//													//...
//													break;
//												}
//											}
//											else
//											{
//												h_timeout();
//												wrong = 0;
//												break;
//											}
//										}
//									}
//									else
//										h_wrong_card();
//								}
//								else
//								{
//									h_timeout();
//									wrong = 0;
//									break;
//								}
//							}
//						}
//						else if (api_check_button(&keypad, '8'))
//						{
//							h_display_enter_current_pass();
//							if(enter_pass())
//							{
//								h_display_enter_new_pass();
//								while(1)
//								{
//								if (enter_pass()) // func enter_pass return 1 if full 4 number, 0 if timeout
//								{
//									if (check_button_with_timeout())
//									{
//										if (!check_password())
//										{
//											wrong++;
//											if (wrong>3)
//											{
//												h_block();
//												h_timeout();
//												wrong = 0;
//												break;
//											}
//											else
//												h_wrong_pass();
//										}
//										else
//										{
//											h_display_enter_new_pass();
//											if (enter_pass())
//											{
//												if (check_button_with_timeout())
//												{
//													flash_save_pass();
//												}
//												else
//												{
//													h_timeout();
//													break;
//												}
//											}
//											else
//											{
//												h_timeout();
//												break;
//											}
//
//										}
//									}
//									else
//									{
//										h_timeout();
//										wrong = 0;
//										break;
//									}
//								}
//								else
//								{
//									h_timeout();
//									wrong = 0;
//									break;
//								}
//								}
//							}
//							//.....
//						}
//					}
//					else
//					{
//						h_timeout();
//						wrong = 0;
//						break;
//					}
//
//				}
//
//			}
//		}
//	}
//
/* USER CODE END 3 */


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief I2C3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C3_Init(void)
{

	/* USER CODE BEGIN I2C3_Init 0 */

	/* USER CODE END I2C3_Init 0 */

	/* USER CODE BEGIN I2C3_Init 1 */

	/* USER CODE END I2C3_Init 1 */
	hi2c3.Instance = I2C3;
	hi2c3.Init.ClockSpeed = 100000;
	hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c3.Init.OwnAddress1 = 0;
	hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c3.Init.OwnAddress2 = 0;
	hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c3) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C3_Init 2 */

	/* USER CODE END I2C3_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void)
{

	/* USER CODE BEGIN SPI1_Init 0 */
	//
	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */
	//
	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */
	//
	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 999;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 15999;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_10, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

	/*Configure GPIO pins : PA2 PA3 PA4 PA10 */
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PB10 PB4 PB5 */
	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PB3 */
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{
		flag = true;
	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

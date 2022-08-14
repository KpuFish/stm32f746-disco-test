//--------------------------------------------
// Author   : dj park
// Data     : 2022.07.28
// B/D Info : STM32F746NGH6-DISCOVERY Board
// F/W      : based on FreeRTOS, generated by cubemx
//          : V0.1
//--------------------------------------------


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "gpio.h"
#include "sdmmc.h"
#include "dma.h"
#include "lcd.h"
#include "sdram.h"

#include "hw_init.h"
#include "app_led.h"
#include "cli_interface.h"
#include "file_system.h"

#include "config.h"


/* Private function prototypes -----------------------------------------------*/

void MX_FREERTOS_Init(void);


/**
  * @brief  The application entry point.
  * @note   This System is using the AXI BUS with enabling the internal I/D-cache
  * @retval int
  */
int main(void)
{
  //* MPU Configuration------------------------------------------------------
  MPU_Config();

  //* Enable I-Cache---------------------------------------------------------
  SCB_EnableICache();

  //* Enable D-Cache---------------------------------------------------------
  SCB_EnableDCache();

  //* MCU Configuration------------------------------------------------------
  //* Reset of all peripherals, Initializes the Flash interface and the Systick. 
  HAL_Init();

  //* Configure the system clock 
  SystemClock_Config();

  //* Initialize all configured peripherals 
  MX_GPIO_Init();
  
  MX_USART6_UART_Init();

#if _USE_FS_  ==  1
  MX_SDMMC1_SD_Init();
#endif

  MX_DMA_Init();

  //sdram_init();

#if _USE_LCD_ ==  1
  ltdc_clk_init();
  LCD_Config();
#endif

  //* Call init function for freertos objects (in freertos.c)
#if _USE_RTOS_  ==  1
  MX_FREERTOS_Init();
#endif

#if _USE_FS_  ==  1
  app_fs_init();
#endif

  //* App Init...
  app_led_init();
  
  app_cli_init();

  /* Start scheduler */
#if _USE_RTOS_  ==  1
  osKernelStart();
#endif

  while (1) {
      ;
  }
}
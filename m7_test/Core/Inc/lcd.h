#ifndef __LCD_H__
#define __LCD_H__


//----------------------------------------
// Include
//----------------------------------------
#include "rk043fn48h.h"


//----------------------------------------
// Function
//----------------------------------------
#define LCD_X_ORIGIN       0
#define LCD_Y_ORIGIN       0
#define LCD_X_MAX          480
#define LCD_Y_MAX          272

//-----------------------------------------------------
// LCD Pin Mappings for STM32f746-Disco
//-----------------------------------------------------
#define LCD_DISP_PIN                    GPIO_PIN_12
#define LCD_DISP_GPIO_PORT              GPIOI
#define LCD_DISP_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOI_CLK_ENABLE()
#define LCD_DISP_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOI_CLK_DISABLE()

/* Backlight control pin */
#define LCD_BL_CTRL_PIN                  GPIO_PIN_3
#define LCD_BL_CTRL_GPIO_PORT            GPIOK
#define LCD_BL_CTRL_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOK_CLK_ENABLE()
#define LCD_BL_CTRL_GPIO_CLK_DISABLE()   __HAL_RCC_GPIOK_CLK_DISABLE()


//----------------------------------------
// Function
//----------------------------------------
void LCD_Config(void);

void ltdc_clk_init(void);


#endif /*  __LCD_H__  */

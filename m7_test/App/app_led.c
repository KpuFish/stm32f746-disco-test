#include "app_led.h"
#include "stm32f7xx_hal.h"


void app_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   = GREEN_LED;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

void app_led_toggle(void)
{    
    HAL_GPIO_TogglePin(LED_PORT, GREEN_LED);    
}

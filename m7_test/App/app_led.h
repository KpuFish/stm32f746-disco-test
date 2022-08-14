#ifndef __APP_LED_H__
#define __APP_LED_H__


//----------------------------
// Define
//----------------------------
#define LED_PORT                GPIOI
#define GREEN_LED               GPIO_PIN_1

//----------------------------
// Function
//----------------------------
void app_led_init(void);

void app_led_toggle(void);


#endif /*  __APP_LED_H__  */

/* Copy the marked sections into a CubeMX-generated Core/Src/main.c. */
#include "gpio_led.h"
static gpio_led_t status_led;
static void app_init(void)
{
    gpio_led_init(&status_led, GPIOB, GPIO_PIN_0, false);
}
static void app_loop(void)
{
    gpio_led_toggle(&status_led);
    HAL_Delay(500U);
}
/* Call app_init() after MX_GPIO_Init(), then call app_loop() in while(1). */

/*
 * PA0: button, internal pull-up, falling-edge EXTI
 * PB0: LED, active high
 */
#include "exti_button_core.h"
#include "gpio_led.h"

static exti_button_core_t user_button_irq;
static gpio_led_t status_led;

static void app_init(void)
{
    gpio_led_init(&status_led, GPIOB, GPIO_PIN_0, false);
    exti_button_core_init(&user_button_irq, 30U);
}

static void app_loop(void)
{
    if (exti_button_core_take_event(&user_button_irq)) {
        gpio_led_toggle(&status_led);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0) {
        (void)exti_button_core_on_irq(
            &user_button_irq,
            HAL_GetTick()
        );
    }
}

/*
 * main():
 * MX_GPIO_Init();
 * app_init();
 * while (1) { app_loop(); }
 */

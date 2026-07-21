#include "gpio_led.h"
static GPIO_PinState gpio_led_level(const gpio_led_t *led, bool on)
{
    const bool high_level = led->active_low ? !on : on;
    return high_level ? GPIO_PIN_SET : GPIO_PIN_RESET;
}
void gpio_led_init(gpio_led_t *led, GPIO_TypeDef *port, uint16_t pin, bool active_low)
{
    if (led == NULL) return;
    led->port = port; led->pin = pin; led->active_low = active_low;
    gpio_led_off(led);
}
void gpio_led_on(const gpio_led_t *led) { gpio_led_set(led, true); }
void gpio_led_off(const gpio_led_t *led) { gpio_led_set(led, false); }
void gpio_led_toggle(const gpio_led_t *led)
{
    if (led == NULL || led->port == NULL) return;
    HAL_GPIO_TogglePin(led->port, led->pin);
}
void gpio_led_set(const gpio_led_t *led, bool on)
{
    if (led == NULL || led->port == NULL) return;
    HAL_GPIO_WritePin(led->port, led->pin, gpio_led_level(led, on));
}

#ifndef GPIO_LED_H
#define GPIO_LED_H
#include "stm32f1xx_hal.h"
#include <stdbool.h>
typedef struct { GPIO_TypeDef *port; uint16_t pin; bool active_low; } gpio_led_t;
void gpio_led_init(gpio_led_t *led, GPIO_TypeDef *port, uint16_t pin, bool active_low);
void gpio_led_on(const gpio_led_t *led);
void gpio_led_off(const gpio_led_t *led);
void gpio_led_toggle(const gpio_led_t *led);
void gpio_led_set(const gpio_led_t *led, bool on);
#endif

#ifndef GPIO_BUTTON_H
#define GPIO_BUTTON_H

#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
    bool active_low;
    uint32_t debounce_ms;
    GPIO_PinState last_raw_level;
    GPIO_PinState stable_level;
    uint32_t last_change_ms;
    bool pressed_event;
    bool released_event;
} gpio_button_t;

void gpio_button_init(
    gpio_button_t *button,
    GPIO_TypeDef *port,
    uint16_t pin,
    bool active_low,
    uint32_t debounce_ms,
    uint32_t now_ms
);

void gpio_button_update(gpio_button_t *button, uint32_t now_ms);
bool gpio_button_is_pressed(const gpio_button_t *button);
bool gpio_button_was_pressed(gpio_button_t *button);
bool gpio_button_was_released(gpio_button_t *button);

#endif

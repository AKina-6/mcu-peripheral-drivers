#include "gpio_button.h"
#include <stddef.h>

static bool level_is_pressed(
    const gpio_button_t *button,
    GPIO_PinState level
) {
    return button->active_low
        ? (level == GPIO_PIN_RESET)
        : (level == GPIO_PIN_SET);
}

void gpio_button_init(
    gpio_button_t *button,
    GPIO_TypeDef *port,
    uint16_t pin,
    bool active_low,
    uint32_t debounce_ms,
    uint32_t now_ms
) {
    if (button == NULL || port == NULL) {
        return;
    }

    const GPIO_PinState initial_level = HAL_GPIO_ReadPin(port, pin);

    button->port = port;
    button->pin = pin;
    button->active_low = active_low;
    button->debounce_ms = debounce_ms;
    button->last_raw_level = initial_level;
    button->stable_level = initial_level;
    button->last_change_ms = now_ms;
    button->pressed_event = false;
    button->released_event = false;
}

void gpio_button_update(
    gpio_button_t *button,
    uint32_t now_ms
) {
    if (button == NULL || button->port == NULL) {
        return;
    }

    const GPIO_PinState raw_level =
        HAL_GPIO_ReadPin(button->port, button->pin);

    button->pressed_event = false;
    button->released_event = false;

    if (raw_level != button->last_raw_level) {
        button->last_raw_level = raw_level;
        button->last_change_ms = now_ms;
        return;
    }

    if (raw_level == button->stable_level) {
        return;
    }

    if ((uint32_t)(now_ms - button->last_change_ms) < button->debounce_ms) {
        return;
    }

    const bool was_pressed =
        level_is_pressed(button, button->stable_level);
    const bool is_pressed =
        level_is_pressed(button, raw_level);

    button->stable_level = raw_level;

    if (!was_pressed && is_pressed) {
        button->pressed_event = true;
    } else if (was_pressed && !is_pressed) {
        button->released_event = true;
    }
}

bool gpio_button_is_pressed(
    const gpio_button_t *button
) {
    if (button == NULL) {
        return false;
    }

    return level_is_pressed(button, button->stable_level);
}

bool gpio_button_was_pressed(
    gpio_button_t *button
) {
    if (button == NULL) {
        return false;
    }

    const bool event = button->pressed_event;
    button->pressed_event = false;
    return event;
}

bool gpio_button_was_released(
    gpio_button_t *button
) {
    if (button == NULL) {
        return false;
    }

    const bool event = button->released_event;
    button->released_event = false;
    return event;
}

#ifndef EXTI_BUTTON_CORE_H
#define EXTI_BUTTON_CORE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t debounce_ms;
    uint32_t last_irq_ms;
    uint32_t pending_events;
    bool initialized;
} exti_button_core_t;

void exti_button_core_init(exti_button_core_t *button, uint32_t debounce_ms);
bool exti_button_core_on_irq(exti_button_core_t *button, uint32_t now_ms);
bool exti_button_core_take_event(exti_button_core_t *button);
uint32_t exti_button_core_pending_count(const exti_button_core_t *button);

#endif

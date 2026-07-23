#include "exti_button_core.h"
#include <stddef.h>

void exti_button_core_init(exti_button_core_t *button, uint32_t debounce_ms)
{
    if (button == NULL) return;
    button->debounce_ms = debounce_ms;
    button->last_irq_ms = 0U;
    button->pending_events = 0U;
    button->initialized = false;
}

bool exti_button_core_on_irq(exti_button_core_t *button, uint32_t now_ms)
{
    if (button == NULL) return false;

    if (!button->initialized) {
        button->initialized = true;
        button->last_irq_ms = now_ms;
        button->pending_events++;
        return true;
    }

    if ((uint32_t)(now_ms - button->last_irq_ms) < button->debounce_ms) {
        return false;
    }

    button->last_irq_ms = now_ms;
    button->pending_events++;
    return true;
}

bool exti_button_core_take_event(exti_button_core_t *button)
{
    if (button == NULL || button->pending_events == 0U) return false;
    button->pending_events--;
    return true;
}

uint32_t exti_button_core_pending_count(const exti_button_core_t *button)
{
    return button == NULL ? 0U : button->pending_events;
}

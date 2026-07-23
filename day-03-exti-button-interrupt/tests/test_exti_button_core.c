#include <assert.h>
#include "exti_button_core.h"

int main(void)
{
    exti_button_core_t b;
    exti_button_core_init(&b, 30U);

    assert(exti_button_core_on_irq(&b, 100U));
    assert(!exti_button_core_on_irq(&b, 105U));
    assert(!exti_button_core_on_irq(&b, 120U));
    assert(exti_button_core_on_irq(&b, 130U));
    assert(exti_button_core_pending_count(&b) == 2U);

    assert(exti_button_core_take_event(&b));
    assert(exti_button_core_take_event(&b));
    assert(!exti_button_core_take_event(&b));

    b.initialized = true;
    b.last_irq_ms = 0xFFFFFFF0U;
    assert(exti_button_core_on_irq(&b, 0x00000020U));
    return 0;
}

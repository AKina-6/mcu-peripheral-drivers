#include <stdio.h>
#include "exti_button_core.h"

int main(void)
{
    exti_button_core_t button;
    const uint32_t times[] = {100U, 104U, 109U, 133U, 165U};

    exti_button_core_init(&button, 30U);

    for (unsigned int i = 0; i < sizeof(times) / sizeof(times[0]); ++i) {
        const bool accepted = exti_button_core_on_irq(&button, times[i]);
        printf("irq=%lu accepted=%s pending=%lu\n",
               (unsigned long)times[i],
               accepted ? "yes" : "no",
               (unsigned long)exti_button_core_pending_count(&button));
    }

    unsigned int consumed = 0U;
    while (exti_button_core_take_event(&button)) consumed++;
    printf("consumed_events=%u\n", consumed);
    return 0;
}

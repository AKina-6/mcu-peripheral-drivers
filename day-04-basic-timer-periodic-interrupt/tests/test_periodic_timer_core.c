#include <assert.h>
#include "periodic_timer_core.h"

int main(void)
{
    periodic_timer_core_t timer;

    assert(!periodic_timer_core_init(&timer, 0U));
    assert(periodic_timer_core_init(&timer, 3U));

    periodic_timer_core_on_tick(&timer);
    periodic_timer_core_on_tick(&timer);
    assert(periodic_timer_core_pending_count(&timer) == 0U);

    periodic_timer_core_on_tick(&timer);
    assert(periodic_timer_core_pending_count(&timer) == 1U);

    assert(periodic_timer_core_take_event(&timer));
    assert(!periodic_timer_core_take_event(&timer));

    periodic_timer_core_set_enabled(&timer, false);
    for (int i = 0; i < 10; ++i) {
        periodic_timer_core_on_tick(&timer);
    }
    assert(periodic_timer_core_pending_count(&timer) == 0U);

    periodic_timer_core_set_enabled(&timer, true);
    for (int i = 0; i < 6; ++i) {
        periodic_timer_core_on_tick(&timer);
    }
    assert(periodic_timer_core_pending_count(&timer) == 2U);

    return 0;
}

#include <assert.h>
#include "tick_dispatcher.h"

int main(void)
{
    tick_dispatcher_t scheduler;
    assert(tick_dispatcher_init(&scheduler));

    for (uint32_t i = 0U; i < 2000U; ++i) {
        tick_dispatcher_on_1ms_tick(&scheduler);
    }

    assert(periodic_timer_core_pending_count(
               &scheduler.led_timer) == 4U);
    assert(periodic_timer_core_pending_count(
               &scheduler.sensor_timer) == 2U);
    assert(periodic_timer_core_pending_count(
               &scheduler.telemetry_timer) == 1U);

    return 0;
}

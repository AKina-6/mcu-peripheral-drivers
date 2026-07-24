#include "tick_dispatcher.h"
#include <stddef.h>

bool tick_dispatcher_init(tick_dispatcher_t *dispatcher)
{
    if (dispatcher == NULL) {
        return false;
    }

    const bool led_ok = periodic_timer_core_init(
        &dispatcher->led_timer,
        500U
    );
    const bool sensor_ok = periodic_timer_core_init(
        &dispatcher->sensor_timer,
        1000U
    );
    const bool telemetry_ok = periodic_timer_core_init(
        &dispatcher->telemetry_timer,
        2000U
    );

    return led_ok && sensor_ok && telemetry_ok;
}

void tick_dispatcher_on_1ms_tick(tick_dispatcher_t *dispatcher)
{
    if (dispatcher == NULL) {
        return;
    }

    periodic_timer_core_on_tick(&dispatcher->led_timer);
    periodic_timer_core_on_tick(&dispatcher->sensor_timer);
    periodic_timer_core_on_tick(&dispatcher->telemetry_timer);
}

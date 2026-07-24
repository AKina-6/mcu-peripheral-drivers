#ifndef TICK_DISPATCHER_H
#define TICK_DISPATCHER_H

#include <stdbool.h>
#include "periodic_timer_core.h"

typedef struct {
    periodic_timer_core_t led_timer;
    periodic_timer_core_t sensor_timer;
    periodic_timer_core_t telemetry_timer;
} tick_dispatcher_t;

bool tick_dispatcher_init(tick_dispatcher_t *dispatcher);
void tick_dispatcher_on_1ms_tick(tick_dispatcher_t *dispatcher);

#endif

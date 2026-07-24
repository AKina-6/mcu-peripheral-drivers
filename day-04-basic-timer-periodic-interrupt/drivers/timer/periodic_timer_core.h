#ifndef PERIODIC_TIMER_CORE_H
#define PERIODIC_TIMER_CORE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t period_ticks;
    uint32_t elapsed_ticks;
    uint32_t pending_events;
    bool enabled;
} periodic_timer_core_t;

bool periodic_timer_core_init(
    periodic_timer_core_t *timer,
    uint32_t period_ticks
);

void periodic_timer_core_set_enabled(
    periodic_timer_core_t *timer,
    bool enabled
);

void periodic_timer_core_on_tick(
    periodic_timer_core_t *timer
);

bool periodic_timer_core_take_event(
    periodic_timer_core_t *timer
);

uint32_t periodic_timer_core_pending_count(
    const periodic_timer_core_t *timer
);

#endif

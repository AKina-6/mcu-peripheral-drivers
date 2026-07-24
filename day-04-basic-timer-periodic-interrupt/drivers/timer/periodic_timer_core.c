#include "periodic_timer_core.h"
#include <stddef.h>

bool periodic_timer_core_init(
    periodic_timer_core_t *timer,
    uint32_t period_ticks
) {
    if (timer == NULL || period_ticks == 0U) {
        return false;
    }

    timer->period_ticks = period_ticks;
    timer->elapsed_ticks = 0U;
    timer->pending_events = 0U;
    timer->enabled = true;
    return true;
}

void periodic_timer_core_set_enabled(
    periodic_timer_core_t *timer,
    bool enabled
) {
    if (timer == NULL) {
        return;
    }
    timer->enabled = enabled;
}

void periodic_timer_core_on_tick(
    periodic_timer_core_t *timer
) {
    if (timer == NULL || !timer->enabled) {
        return;
    }

    timer->elapsed_ticks++;
    if (timer->elapsed_ticks >= timer->period_ticks) {
        timer->elapsed_ticks = 0U;
        timer->pending_events++;
    }
}

bool periodic_timer_core_take_event(
    periodic_timer_core_t *timer
) {
    if (timer == NULL || timer->pending_events == 0U) {
        return false;
    }

    timer->pending_events--;
    return true;
}

uint32_t periodic_timer_core_pending_count(
    const periodic_timer_core_t *timer
) {
    return timer == NULL ? 0U : timer->pending_events;
}

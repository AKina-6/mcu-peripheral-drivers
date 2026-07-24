#include <stdio.h>
#include "tick_dispatcher.h"

int main(void)
{
    tick_dispatcher_t scheduler;
    if (!tick_dispatcher_init(&scheduler)) {
        return 1;
    }

    unsigned int led_count = 0U;
    unsigned int sensor_count = 0U;
    unsigned int telemetry_count = 0U;

    for (uint32_t ms = 1U; ms <= 5000U; ++ms) {
        tick_dispatcher_on_1ms_tick(&scheduler);

        while (periodic_timer_core_take_event(
                   &scheduler.led_timer)) {
            led_count++;
            printf("t=%lu ms led_event=%u\n",
                   (unsigned long)ms,
                   led_count);
        }

        while (periodic_timer_core_take_event(
                   &scheduler.sensor_timer)) {
            sensor_count++;
            printf("t=%lu ms sensor_event=%u\n",
                   (unsigned long)ms,
                   sensor_count);
        }

        while (periodic_timer_core_take_event(
                   &scheduler.telemetry_timer)) {
            telemetry_count++;
            printf("t=%lu ms telemetry_event=%u\n",
                   (unsigned long)ms,
                   telemetry_count);
        }
    }

    printf("summary led=%u sensor=%u telemetry=%u\n",
           led_count,
           sensor_count,
           telemetry_count);
    return 0;
}

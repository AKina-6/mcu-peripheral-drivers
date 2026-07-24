/*
 * TIM2: 1 ms update interrupt
 * PB0: LED, active high
 */
#include "tick_dispatcher.h"
#include "gpio_led.h"

extern TIM_HandleTypeDef htim2;

static tick_dispatcher_t scheduler;
static gpio_led_t status_led;

static void app_init(void)
{
    gpio_led_init(
        &status_led,
        GPIOB,
        GPIO_PIN_0,
        false
    );

    (void)tick_dispatcher_init(&scheduler);
    HAL_TIM_Base_Start_IT(&htim2);
}

static void app_loop(void)
{
    if (periodic_timer_core_take_event(
            &scheduler.led_timer)) {
        gpio_led_toggle(&status_led);
    }

    if (periodic_timer_core_take_event(
            &scheduler.sensor_timer)) {
        /* TODO: trigger one non-blocking sensor step. */
    }

    if (periodic_timer_core_take_event(
            &scheduler.telemetry_timer)) {
        /* TODO: trigger one telemetry step. */
    }
}

void HAL_TIM_PeriodElapsedCallback(
    TIM_HandleTypeDef *htim
) {
    if (htim->Instance == TIM2) {
        tick_dispatcher_on_1ms_tick(&scheduler);
    }
}

/*
 * main():
 * MX_GPIO_Init();
 * MX_TIM2_Init();
 * app_init();
 * while (1) { app_loop(); }
 */

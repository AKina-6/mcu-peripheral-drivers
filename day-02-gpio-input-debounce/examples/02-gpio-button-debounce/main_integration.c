/*
 * 默认连接：
 * - PA0 接按键，按下接 GND，内部上拉，低电平有效
 * - PB0 接 LED，高电平点亮
 */

#include "gpio_button.h"
#include "gpio_led.h"

static gpio_button_t user_button;
static gpio_led_t status_led;

static void app_init(void)
{
    gpio_led_init(
        &status_led,
        GPIOB,
        GPIO_PIN_0,
        false
    );

    gpio_button_init(
        &user_button,
        GPIOA,
        GPIO_PIN_0,
        true,
        20U,
        HAL_GetTick()
    );
}

static void app_loop(void)
{
    gpio_button_update(
        &user_button,
        HAL_GetTick()
    );

    if (gpio_button_was_pressed(&user_button)) {
        gpio_led_toggle(&status_led);
    }

    HAL_Delay(1U);
}

/*
 * 在 CubeMX 生成的 main() 中：
 *
 * MX_GPIO_Init();
 * app_init();
 *
 * while (1)
 * {
 *     app_loop();
 * }
 */

# Day 03：EXTI 外部中断与按键事件处理

## 实验目标

- 使用 PA0 下降沿 EXTI 检测按键。
- 理解 EXTI、NVIC 和 HAL 回调链。
- 中断中只记录事件，主循环中翻转 LED。
- 使用 30 ms 时间窗口过滤按键抖动。
- 使用电脑端测试验证事件核心。

## 默认配置

| 项目 | 配置 |
|---|---|
| MCU | STM32F103C8T6 |
| 按键 | PA0，内部上拉 |
| EXTI | 下降沿 |
| LED | PB0 |
| 消抖窗口 | 30 ms |

## CubeMX

PA0：

- `GPIO_EXTI0`
- Falling Edge
- Pull-up

NVIC：

- Enable `EXTI line0 interrupt`

PB0：

- `GPIO_Output`
- Push Pull
- Initial Low

## HAL 调用链

```text
PA0 下降沿
→ EXTI pending
→ NVIC
→ EXTI0_IRQHandler()
→ HAL_GPIO_EXTI_IRQHandler()
→ HAL_GPIO_EXTI_Callback()
```

## 中断设计

中断回调只记录事件：

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0) {
        exti_button_core_on_irq(
            &user_button_irq,
            HAL_GetTick()
        );
    }
}
```

主循环处理事件：

```c
if (exti_button_core_take_event(&user_button_irq)) {
    gpio_led_toggle(&status_led);
}
```

不要在中断中执行 `HAL_Delay()`、OLED 刷屏、阻塞串口或 Flash 擦写。

## 电脑端测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/exti_button_sim
```

预期：

```text
irq=100 accepted=yes pending=1
irq=104 accepted=no pending=1
irq=109 accepted=no pending=1
irq=133 accepted=yes pending=2
irq=165 accepted=yes pending=3
consumed_events=3
```

## 实物预期结果

- 每按一次按键，LED 翻转一次。
- 抖动不会造成连续翻转。
- 长按只产生一次下降沿事件。

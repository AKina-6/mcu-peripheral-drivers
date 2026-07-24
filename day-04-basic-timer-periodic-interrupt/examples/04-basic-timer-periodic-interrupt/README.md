# Day 04：基本定时器周期中断与非阻塞任务调度

## 实验目标

- 理解定时器预分频、自动重装载和更新中断。
- 将 TIM2 配置为 1 ms 周期中断。
- 使用一个硬件 Tick 驱动多个软件周期任务。
- 使用主循环消费事件，避免在 ISR 中执行复杂逻辑。
- 用定时器替代 `HAL_Delay(500)` 完成 LED 闪烁。

## 默认配置

| 项目 | 配置 |
|---|---|
| MCU | STM32F103C8T6 |
| 定时器 | TIM2 |
| 基础 Tick | 1 ms |
| LED 周期 | 500 ms |
| 传感器周期 | 1000 ms |
| 遥测周期 | 2000 ms |
| LED | PB0 |

## 定时器公式

```text
f_update = f_timer / ((PSC + 1) × (ARR + 1))
```

若 TIM2 输入时钟为 72 MHz，可设置：

```text
PSC = 71
ARR = 999
```

此时更新频率为 1000 Hz，周期为 1 ms。

> TIM2 的真实输入时钟应根据 CubeMX 时钟树确认。APB1 分频不为 1 时，STM32F1 定时器时钟通常为对应 PCLK 的 2 倍。

## CubeMX 配置

### TIM2

- Clock Source：Internal Clock
- Prescaler：71
- Counter Period：999
- Counter Mode：Up
- NVIC：启用 `TIM2 global interrupt`

### PB0

- Mode：`GPIO_Output`
- Output type：`Push Pull`
- Initial level：`Low`

## 启动中断

```c
HAL_TIM_Base_Start_IT(&htim2);
```

## 中断回调

```c
void HAL_TIM_PeriodElapsedCallback(
    TIM_HandleTypeDef *htim
) {
    if (htim->Instance == TIM2) {
        tick_dispatcher_on_1ms_tick(&scheduler);
    }
}
```

## 主循环处理

```c
if (periodic_timer_core_take_event(
        &scheduler.led_timer)) {
    gpio_led_toggle(&status_led);
}
```

中断只累计时间和事件；LED、传感器和串口处理留在主循环。

## 自动测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/timer_sim
```

5000 ms 模拟时间内预期：

| 事件 | 次数 |
|---|---:|
| LED 500 ms | 10 |
| Sensor 1000 ms | 5 |
| Telemetry 2000 ms | 2 |

## 实物预期

- LED 每 500 ms 翻转一次。
- 完整亮灭周期约 1 s。
- 主循环不再使用 `HAL_Delay(500)`。
- 可同时处理按键、传感器和串口事件。

## 常见问题

### 中断不触发

检查 `HAL_TIM_Base_Start_IT()`、TIM2 NVIC、`TIM2_IRQHandler()` 和回调中的实例判断。

### 周期不准确

检查时钟树、APB1 分频、TIM2 输入时钟、PSC 和 ARR。

### 事件积压

主循环若长期阻塞，`pending_events` 会累积。综合项目中应避免长时间阻塞，并设计事件丢弃或追赶策略。

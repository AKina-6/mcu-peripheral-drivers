# STM32 GPIO 输出与 LED 闪烁

## 实验目标

- 理解 GPIO 推挽输出。
- 使用 STM32CubeMX 配置 PB0。
- 使用 HAL 控制高低电平。
- 封装可复用的 LED 驱动。
- 实现 LED 每 500 ms 翻转一次。

## 实验环境

| 项目 | 内容 |
|---|---|
| MCU | STM32F103C8T6 |
| 开发方式 | STM32CubeMX + HAL |
| IDE | STM32CubeIDE 或 Keil MDK |
| LED 引脚 | PB0 |

## 硬件连接

| 器件 | 连接 |
|---|---|
| PB0 | 限流电阻一端 |
| 电阻另一端 | LED 正极 |
| LED 负极 | GND |

上述接法为高电平点亮。若开发板 LED 为低电平点亮，请将 `active_low` 设为 `true`。

## CubeMX 配置

1. 选择 STM32F103C8T6。
2. 将 PB0 配置为 `GPIO_Output`。
3. GPIO Mode 选择 `Output Push Pull`。
4. Pull-up/Pull-down 选择 `No pull-up and no pull-down`。
5. 初始输出电平设为 Low。
6. 生成 HAL 工程。

## 关键代码

```c
gpio_led_t status_led;
gpio_led_init(&status_led, GPIOB, GPIO_PIN_0, false);
while (1)
{
    gpio_led_toggle(&status_led);
    HAL_Delay(500U);
}
```

完整亮灭周期为 1000 ms，因此闪烁频率约为 1 Hz。

## 预期结果

- 工程编译成功。
- 程序下载成功。
- LED 每 500 ms 改变一次状态。

## 常见问题

### LED 不亮

检查 GPIO 时钟、引脚模式、LED 极性、限流电阻和 `active_low` 设置。

### LED 常亮

检查主循环是否执行、`HAL_Delay()` 是否工作，以及程序是否卡在初始化阶段。

## 后续扩展

- 按键控制 LED。
- 定时器中断替代阻塞延时。
- PWM 呼吸灯。

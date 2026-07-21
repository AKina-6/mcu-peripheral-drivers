# GPIO 输出学习笔记

## GPIO 的作用

GPIO 是通用输入输出接口，可读取外部数字电平或输出高低电平。常用于 LED、蜂鸣器、继电器、片选信号和芯片使能控制。

## STM32F1 常见输出模式

| 模式 | 特点 | 用途 |
|---|---|---|
| 推挽输出 | 主动输出高、低电平 | LED、普通控制信号 |
| 开漏输出 | 只能主动拉低，高电平依赖上拉 | I²C、线与逻辑 |
| 复用推挽 | 由片上外设控制 | UART TX、SPI |
| 复用开漏 | 外设控制的开漏输出 | I²C |

## LED 限流电阻

估算公式：`R = (VGPIO - VF) / I`。

例如 3.3 V GPIO、LED 压降 2.0 V、目标电流 5 mA：

```text
R = (3.3 - 2.0) / 0.005 = 260 Ω
```

可选择常用的 330 Ω 电阻。

## HAL 常用函数

```c
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
```

## 为什么封装 LED 驱动

封装后，应用层只表达“点亮、熄灭、翻转”，具体端口、引脚和有效电平由驱动层管理，便于复用和迁移。

## HAL_Delay 的局限

`HAL_Delay()` 会阻塞当前执行流程。综合项目中应逐步替换为非阻塞调度、定时器中断或 FreeRTOS 任务延时。

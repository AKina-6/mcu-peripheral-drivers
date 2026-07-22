# GPIO 输入与按键软件消抖

## 实验目标

- 理解 GPIO 输入、内部上拉和有效电平。
- 理解机械按键抖动。
- 实现非阻塞软件消抖。
- 实现每按下一次按键，LED 只翻转一次。

## 默认配置

| 项目 | 内容 |
|---|---|
| MCU | STM32F103C8T6 |
| 按键引脚 | PA0 |
| 按键模式 | 上拉输入 |
| 按键有效电平 | 低电平 |
| LED 引脚 | PB0 |
| 消抖时间 | 20 ms |
| 扫描周期 | 1 ms |

## 接线

### 按键

| 按键端 | 连接 |
|---|---|
| 一端 | PA0 |
| 另一端 | GND |

PA0 在 CubeMX 中启用内部上拉。

### LED

| LED 端 | 连接 |
|---|---|
| 正极 | PB0，经限流电阻 |
| 负极 | GND |

## CubeMX 配置

### PA0

- Mode：`GPIO_Input`
- Pull：`Pull-up`

### PB0

- Mode：`GPIO_Output`
- Output type：`Push Pull`
- Initial level：`Low`

## 按键抖动

机械触点在按下和松开时会短暂反复接触，输入可能表现为：

```text
1 → 0 → 1 → 0 → 0 → 1 → 0
```

直接读取电平时，一次按压可能被程序识别为多次。

## 非阻塞消抖流程

```text
检测原始电平变化
→ 记录变化时刻
→ 新电平持续稳定 20 ms
→ 更新稳定状态
→ 生成一次按下或松开事件
```

## 核心调用

```c
gpio_button_update(
    &user_button,
    HAL_GetTick()
);

if (gpio_button_was_pressed(&user_button)) {
    gpio_led_toggle(&status_led);
}
```

## 预期现象

- 每按下一次按键，LED 翻转一次。
- 长按按键时，LED 不会连续翻转。
- 松开后再次按下，LED 再翻转一次。

## 常见问题

### 一直被识别为按下

检查 PA0 上拉、按键接线和 `active_low` 配置。

### 一次按压触发多次

增大消抖时间到 30 ms 或 50 ms，并检查主循环是否存在长时间阻塞。

### 响应过慢

减小消抖时间，检查主循环中的 `HAL_Delay()` 和阻塞式驱动。

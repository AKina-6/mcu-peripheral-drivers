# MCU Peripheral Drivers

面向 STM32F103C8T6 的单片机外设驱动学习仓库，用于系统整理 GPIO、EXTI、定时器、PWM、UART、ADC、DMA、I²C、SPI、RTC、Flash 和看门狗等基础能力。

## 仓库目标

- 理解外设工作原理和寄存器配置逻辑
- 使用 STM32 HAL 完成可复用驱动封装
- 为后续裸机、FreeRTOS 和综合项目提供基础模块
- 记录接线、调试过程和常见错误

## 目录

```text
drivers/
├── gpio/
├── exti/
├── timer/
├── pwm/
├── uart/
├── adc/
├── dma/
├── i2c/
├── spi/
├── rtc/
├── flash/
└── watchdog/
examples/
docs/
learning-log/
```

## 学习顺序

GPIO → EXTI → Timer → PWM → UART → ADC → DMA → I²C → SPI → RTC/Flash/Watchdog

详细计划见 [docs/learning-roadmap.md](docs/learning-roadmap.md)。

## GitHub Description

`Reusable STM32 peripheral drivers and learning examples for GPIO, EXTI, timers, PWM, UART, ADC, DMA, I2C, SPI, RTC, Flash and watchdogs.`

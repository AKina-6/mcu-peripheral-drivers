# Day 04：基本定时器周期中断与非阻塞任务调度

## 今日目标

使用 TIM2 产生 1 ms 周期中断，通过软件定时器生成 LED、传感器和遥测事件。

## 已完成的软件结果

- [x] 周期定时器核心
- [x] 多周期 Tick Dispatcher
- [x] STM32 HAL 集成示例
- [x] 电脑端模拟程序
- [x] 两组单元测试
- [x] 禁用与重新启用测试
- [x] 多周期次数验证

## 自动验证结果

生成包时已经完成：

```text
CMake configure：通过
CMake build：通过
CTest：通过
```

5000 ms 模拟结果：

```text
LED events = 10
Sensor events = 5
Telemetry events = 2
```

具体输出见 `VERIFICATION_RESULT.txt`。

## STM32 实物结果

完成后填写：

- 开发板：
- IDE：
- TIM2 输入时钟：
- PSC：
- ARR：
- 编译结果：
- 烧录结果：
- LED 实际翻转间隔：
- 波形或照片路径：

## 今日总结

完成了硬件定时器 1 ms Tick、软件周期事件和延迟处理框架，可在不使用长时间阻塞延时的情况下调度多个周期任务。

## 下一步

Day 05：PWM 输出与 LED 呼吸灯。

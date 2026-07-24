# Day 04 上传说明

目标仓库：`mcu-peripheral-drivers`

## 复制文件

将压缩包中的全部内容复制到仓库根目录。STM32 示例依赖 Day 01 的 `gpio_led.c/.h`。

## 自动测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 实物验证

- TIM2 配置为 1 ms 更新中断；
- 启用 TIM2 NVIC；
- 调用 `HAL_TIM_Base_Start_IT(&htim2)`；
- PB0 配置为推挽输出；
- 测量 LED 翻转间隔；
- 填写真实实验结果。

## Git 提交

```bash
git pull
git add .
git commit -m "feat: add periodic timer interrupt and deferred task scheduler"
git push
```

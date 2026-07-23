# Day 03 上传说明

目标仓库：`mcu-peripheral-drivers`

复制压缩包全部内容到仓库根目录。STM32 示例依赖 Day 01 的 `gpio_led.c/.h`。

## 先运行自动测试

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 再完成实物验证

- PA0 配置为 EXTI0 下降沿、内部上拉；
- NVIC 启用 EXTI line0；
- PB0 配置为推挽输出；
- 烧录并测试按键；
- 填写学习日志中的真实结果。

## 上传

```bash
git pull
git add .
git commit -m "feat: add EXTI button interrupt and deferred event handling"
git push
```

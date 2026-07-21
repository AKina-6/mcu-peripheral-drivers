# Day 01 上传说明

## 目标仓库

`mcu-peripheral-drivers`

## 复制内容

将压缩包内以下内容复制到仓库根目录：

```text
drivers/gpio/gpio_led.c
drivers/gpio/gpio_led.h
examples/01-gpio-led-blink/
docs/gpio-output-notes.md
learning-log/day-01-gpio-output.md
PROGRESS.md
```

根据 `README_UPDATE_SNIPPET.md` 更新根目录 README。

## 提交命令

```bash
git pull
git add .
git commit -m "feat: add STM32 GPIO output and LED blink experiment"
git push
```

上传前请在学习日志中补充实际 IDE、编译结果、烧录结果、LED 现象、问题和照片路径。

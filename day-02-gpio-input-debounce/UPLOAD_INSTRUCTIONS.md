# Day 02 上传说明

## 目标仓库

`mcu-peripheral-drivers`

## 复制文件

```text
drivers/gpio/gpio_button.c
drivers/gpio/gpio_button.h
examples/02-gpio-button-debounce/
docs/gpio-input-debounce-notes.md
learning-log/day-02-gpio-input-debounce.md
PROGRESS_UPDATE.md
README_UPDATE_SNIPPET.md
```

本实验依赖 Day 01 的：

```text
drivers/gpio/gpio_led.c
drivers/gpio/gpio_led.h
```

## 上传前完成

- 编译工程
- 烧录开发板
- 测试短按
- 测试长按
- 补充真实实验结果
- 添加照片或调试截图

## Git 提交

```bash
git pull
git add .
git commit -m "feat: add GPIO button input and software debounce"
git push
```

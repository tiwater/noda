# 说明
Ticos-SDK 项目模板 for arduino

## 编译环境搭建

  1. Arduino IDE 安装
     - 在 Arduino IDE 中, 选择菜单 `项目`, `加载库`, `管理库...`。
     - 搜索并安装 `Ticos Framework`。 (当前库还未过审，请参考下面步骤手动安装)
  2. 手动安装
     - 将本 [Ticos Framework](https://github.com/tiwater/ticos) 克隆至 Arduino 库目录，通常该目录在 ～/Documents/Arduino/libraries，请根据你的开发平台中 Arduino IDE 的配置确定。
     - 将本 [Ticos SDK](https://github.com/tiwater/ticos-sdk-for-c) 克隆至 Arduino 库目录，通常该目录在 ～/Documents/Arduino/libraries，请根据你的开发平台中 Arduino IDE 的配置确定。

## 编译 & 运行

```bash
$ cd ${您的工程的父目录}
$ arduino-cli compile --fqbn esp32:esp32:esp32s3 ${本工程名}    # 编译工程，请根据实际版型填写--fqbn参数
$ arduino-cli upload --fqbn esp32:esp32:esp32s3 ${本工程名}     # 向/dev/ttyACM0端口烧录固件
$ arduino-cli monitor -p /dev/ttyACM0                           # 打开/dev/ttyACM0端口查看固件的打印信息
```


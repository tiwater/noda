# 说明
Ticos-SDK 项目模板 for esp-idf

## 编译环境搭建

  1. ESP-IDF
如果已经安装esp-idf工具，请跳过此步骤；否则，请先安装esp-idf工具：
注：本例程需要esp-idf更新到最新主线(>=5.0dev)

```bash
$ git clone https://github.com/espressif/esp-idf
$ cd esp-idf
$ . ./install.sh                            # 安装工具链，本步骤仅需要执行一次
$ . ./export.sh                             # 在本终端建立工具链运行环境，每个新建终端都需要执行一次
```
  2. 运行工程目录下 install.sh 脚本自动安装 Ticos 相关工具库；或者手动进行以下两步
  3. 将 [Ticos Framework](https://github.com/tiwater/ticos) 克隆至你的本地，并添加环境变量TICOS_FRAMEWORK_PATH，将变量值配置为此目录
  4. 将 [Ticos SDK](https://github.com/tiwater/ticos-sdk-for-c) 克隆至你的本地，并添加环境变量TICOS_SDK_PATH，将变量值配置为此目录

## 编译 & 运行

```bash
$ export TICOS_FRAMEWORK_PATH=${ Ticos Framework 项目根目录 }
$ export TICOS_SDK_PATH=${ ticos-sdk-for-c 项目根目录 }
$ cd ${您的项目根目录}                      # 然后打开main/main.c，修改文件内指定的宏，填写实际的 WiFi ssid/password 等信息
$ idf.py --list-targets                     # 查看可选编译目标平台
$ idf.py set-target esp32s3                 # 设置编译目标平台，此处选择了 esp32s3
$ idf.py build                              # 编译项目
$ idf.py flash -p /dev/ttyACM0 -b 921600    # 以921600的波特率向/dev/ttyACM0端口烧录固件，波特率与端口请根据实际情况填写
$ idf.py monitor -p /dev/ttyACM0 -b 115200  # 以115200的波特率打开/dev/ttyACM0端口查看固件的打印信息，波特率与端口请根据实际情况填写
```

# Ticos Framework

本框架提供快速接入 Ticos Cloud 的脚手架工程。

## 工具链安装

### Arduino

  1. Arduino IDE 安装
     - 在 Arduino IDE 中, 选择菜单 `项目`, `加载库`, `管理库...`。
     - 搜索并安装 `Ticos Framework`。 (当前库还未过审，请参考下面步骤手动安装)
  2. 手动安装
     - 将 [Ticos Framework](https://github.com/tiwater/ticos-framework) 克隆至 Arduino 库目录，通常该目录在 ~/Documents/Arduino/libraries，请根据你的开发平台中 Arduino IDE 的配置确定。
     - 将 [Ticos SDK](https://github.com/tiwater/ticos-sdk-for-c) 克隆至 Arduino 库目录，通常该目录在 ~/Documents/Arduino/libraries，请根据你的开发平台中 Arduino IDE 的配置确定。

### ESP-IDF

  1. ESP-IDF 安装

```bash
$ git clone https://github.com/espressif/esp-idf
$ cd esp-idf
$ . ./install.sh                            # 安装工具链，本步骤仅需要执行一次
$ . ./export.sh                             # 在本终端建立工具链运行环境，每个新建终端都需要执行一次
```
  2. 运行工程目录下 install.sh 脚本自动安装 Ticos 相关工具库；或者手动进行以下两步
  3. 将 [Ticos Framework](https://github.com/tiwater/ticos-framework) 克隆至你的本地，并添加环境变量TICOS_FRAMEWORK_PATH，将变量值配置为此目录
  4. 将 [Ticos SDK](https://github.com/tiwater/ticos-sdk-for-c) 克隆至你的本地，并添加环境变量TICOS_SDK_PATH，将变量值配置为此目录

## 脚手架工程创建

以下为使用arduino-cli的编译及运行示例，使用Arduino IDE的开发者请直接打开项目
注意：项目生成后请打开ino文件填写产品ID等必要的设备信息

```bash
$ cd ${Ticos Framework 项目根目录}/scripts/codegen                          # 此步骤非必要，仅为后继命令长度短一点
$ python3 -B create_ticos_proj.py --help                        # 查看完整配置项
$ python3 -B create_ticos_proj.py --name='hello_ticos' --thingmodel='templates/thing_model.json'
$ arduino-cli compile --fqbn esp32:esp32:esp32s3 hello_ticos    # 编译工程，请根据实际版型填写--fqbn参数
$ arduino-cli upload --fqbn esp32:esp32:esp32s3 hello_ticos     # 向/dev/ttyACM0端口烧录固件
$ arduino-cli monitor -p /dev/ttyACM0                           # 打开/dev/ttyACM0端口查看固件的打印信息
```

## 利用 ticos_hal_gen.py 创建 IOT 物模型代码模板文件(.h, .c)

通过内含的 ticos_hal_gen.py 脚本，用户可以创建新的物模型接口代码文件，以下为例子：

```bash
$ cd ${Ticos Framework 项目根目录}/scripts/codegen
$ python3 ticos_hal_gen.py --help #查看脚本命令描述
$ python3 ticos_hal_gen.py --name="ticos_iot" --private="uint32_t pid;uint32_t did; uint32_t skey;" --json='templates/thing_model.json'
```

创建成功后，请将新生成的 .h 与 .c 文件直接复制到您的项目代码目录下，即可正常使用
示例中 thing_model.json 文件仅为示例模型，后期需要根据具体模型协议更改脚本

## 利用 ticos_hal_gen.py 创建设备接口代码模板文件(.h, .c)

通过内含的 ticos_hal_gen.py 脚本，用户可以创建新的设备接口代码文件，以下为例子：

```bash
$ cd ${Ticos Framework 项目根目录}/scripts/codegen
$ python3 ticos_hal_gen.py --help #查看脚本命令描述
$ python3 ticos_hal_gen.py --name="fake_accel" --private="uint8_t scl; uint8_t sda; uint8_t addr; uint8_t freq;" --public="float x; float y; float z;"
```

创建成功后，请将新生成的 .h 与 .c 文件直接复制到您的项目代码目录下，即可正常使用

## 利用 ticos_proj_gen.py 新建项目工程

通过内含的 ticos_proj_gen.py 脚本，用户可以新建开箱即用的项目工程，以下为例子：

```bash
$ cd ${Ticos Framework 项目根目录}/scripts/codegen
$ python3 ticos_proj_gen.py --help #查看脚本命令描述
$ python3 -B ticos_proj_gen.py --name="my_ticos_project" --platform="unix"
$ cd my_ticos_project
$ cmake -B build
$ cd build
$ make
```

## 项目编译与运行

### unix

以 Ticos framework 项目目录下 examples/unix/00_hello 例程为例：

```bash
$ export TICOS_FRAMEWORK_PATH=您的 Ticos Framework 项目根目录
$ cd ${TICOS_FRAMEWORK_PATH}/examples/examples/00_hello
$ cmake -B build
$ cd build
$ make
$ ./00_hello
```

### esp32

以 Ticos framework 项目目录下 examples/esp32/00_hello 例程为例：

```bash
$ export TICOS_FRAMEWORK_PATH=您的 Ticos Framework 项目根目录
$ cd ${TICOS_FRAMEWORK_PATH}/examples/esp32/00_hello
$ idf.py --list-targets                     # 查看可选编译目标平台
$ idf.py set-target esp32s3                 # 设置编译目标平台，此处选择了 esp32s3
$ idf.py build                              # 编译项目
$ idf.py flash -p /dev/ttyACM0 -b 921600    # 以 921600 的波特率向 /dev/ttyACM0 端口烧录固件，波特率与端口请根据实际情况填写
$ idf.py monitor -p /dev/ttyACM0 -b 115200  # 以 115200 的波特率打开 /dev/ttyACM0 端口查看固件的打印信息，波特率与端口请根据实际情况填写
```

### arduino

以ticos项目目录下examples/arduino/00_hello例程为例：
注：以下为使用arduino-cli的编译及运行示例，使用arduino-ide的开发者请直接打开项目examples/arduino内例程即可

```bash
$ export TICOS_FRAMEWORK_PATH=您的 Ticos Framework 项目根目录
$ cd ${TICOS_FRAMEWORK_PATH}/examples/arduino                          # 进入例程列表目录
$ arduino-cli compile --fqbn esp32:esp32:esp32s3 00_hello   # 编译00_hello工程，请根据实际版型填写--fqbn参数
$ arduino-cli upload --fqbn esp32:esp32:esp32s3 00_hello    # 向/dev/ttyACM0端口烧录固件
$ arduino-cli monitor -p /dev/ttyACM0                       # 打开/dev/ttyACM0端口查看固件的打印信息
```

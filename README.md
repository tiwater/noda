# noda
Ticos IoT OS for c

## 利用noda_hal_gen.py创建IOT物模型代码模板文件(.h, .c)

通过内含的noda_hal_gen.py脚本，用户可以创建新的物模型接口代码文件，以下为例子：

```bash
$ cd ${noda项目根目录}/scripts/codegen
$ python noda_hal_gen.py --help #查看脚本命令描述
$ python noda_hal_gen.py --name="noda_iot" --private="uint32_t pid;uint32_t did; uint32_t skey;" --json='templates/thing_model.json'
```

创建成功后，请将新生成的.h与.c文件直接复制到您的项目代码目录下，即可正常使用
实例中thing_model.json文件仅为示例模型，后期需要根据具体模型协议更改脚本

## 利用noda_hal_gen.py创建设备接口代码模板文件(.h, .c)

通过内含的noda_hal_gen.py脚本，用户可以创建新的设备接口代码文件，以下为例子：

```bash
$ cd ${noda项目根目录}/scripts/codegen
$ python noda_hal_gen.py --help #查看脚本命令描述
$ python noda_hal_gen.py --name="fake_accel" --private="uint8_t scl; uint8_t sda; uint8_t addr; uint8_t freq;" --public="float x; float y; float z;"
```

创建成功后，请将新生成的.h与.c文件直接复制到您的项目代码目录下，即可正常使用

## 项目编译与运行

### unix

以noda项目目录下examples/unix/00_hello例程为例：

```bash
$ export NODA_PATH=您的noda项目根目录
$ cd ${NODA_PATH}/examples/examples/00_hello
$ cmake -B build
$ cd build
$ make
$ ./00_hello
```

### esp32

如果已经安装esp-idf工具，请跳过此步骤；否则，请先安装esp-idf工具：

```bash
$ git clone https://github.com/espressif/esp-idf
$ cd esp-idf
$ . ./install.sh                            # 安装工具链，本步骤仅需要执行一次
$ . ./export.sh                             # 在本终端建立工具链运行环境，每个新建终端都需要执行一次
```

以noda项目目录下examples/esp32/00_hello例程为例：

```bash
$ export NODA_PATH=您的noda项目根目录
$ cd ${NODA_PATH}/examples/esp32/00_hello
$ idf.py --list-targets                     # 查看可选编译目标平台
$ idf.py set-target esp32s3                 # 设置编译目标平台，此处选择了 esp32s3
$ idf.py build                              # 编译项目
$ idf.py flash -p /dev/ttyACM0 -b 921600    # 以921600的波特率向/dev/ttyACM0端口烧录固件，波特率与端口请根据实际情况填写
$ idf.py monitor -p /dev/ttyACM0 -b 115200  # 以115200的波特率打开/dev/ttyACM0端口查看固件的打印信息，波特率与端口请根据实际情况填写
```

### arduino

如果已经安装arduino-cli或arduino-ide，请跳过此步骤；否则，请先安装两者其中之一：

```bash
$                                           # 施工中 ... ...
```

以noda项目目录下examples/arduino/00_hello例程为例：
注：以下为使用arduino-cli的编译及运行示例，使用arduino-ide的开发者请直接打开项目examples/arduino内例程即可

```bash
$ export NODA_PATH=您的noda项目根目录
$ cd ${NODA_PATH}/examples/arduino                          # 进入例程列表目录
$ arduino-cli compile --fqbn esp32:esp32:esp32s3 00_hello   # 编译00_hello工程，请根据实际版型填写--fqbn参数
$ arduino-cli upload --fqbn esp32:esp32:esp32s3 00_hello    # 向/dev/ttyACM0端口烧录固件
$ arduino-cli monitor -p /dev/ttyACM0                       # 打开/dev/ttyACM0端口查看固件的打印信息
```

施工中 ... ...

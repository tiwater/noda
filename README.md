# noda
Ticos IoT OS for c

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

以noda项目目录下platforms/unix/examples/00_hello例程为例：

```bash
$ export NODA_PATH=您的noda项目根目录
$ cd ${NODA_PATH}/platforms/unix/examples/00_hello
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

以noda项目目录下platforms/esp32/examples/00_hello例程为例：

```bash
$ export NODA_PATH=您的noda项目根目录
$ cd ${NODA_PATH}/platforms/esp32/examples/00_hello
$ idf.py --list-targets                     # 查看可选编译目标平台
$ idf.py set-target esp32c3                 # 设置编译目标平台，此处选择了 esp32ce
$ idf.py build                              # 编译项目
$ idf.py flash -p /dev/ttyACM0 -b 921600    # 以921600的波特率向/dev/ttyACM0端口烧录固件，波特率与端口请根据实际情况填写
$ idf.py monitor -p /dev/ttyACM0 -b 115200  # 以115200的波特率打开/dev/ttyACM0端口查看固件的打印信息，波特率与端口请根据实际情况填写
```

施工中 ... ...

# noda
Ticos IoT OS for c

## 利用noda_hal_gen.py创建设备接口代码模板文件(.h, .c)

通过内含的noda_hal_gen.py脚本，用户可以创建新的设备接口代码文件，以下为例子：

```bash
$ cd ${noda项目script目录}
$ python noda_hal_gen.py --name="fake_accel" --private="uint8_t scl; uint8_t sda; uint8_t addr; uint8_t freq;" --public="float x; float y; float z;"
```

创建成功后，请将新生成的.h与.c文件直接复制到您的项目代码目录下，即可正常使用

## 项目编译与运行

请参考noda项目目录下examples/00_noda_hi

```bash
$ cd examples/00_noda_hi
$ mkdir build
$ cd build
$ cmake ../../..
$ make
$ ./00_noda_hi
```

正在施工...

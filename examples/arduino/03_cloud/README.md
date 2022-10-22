# 03_cloud
arduino对接Ticos-SDK例程

## 编译 & 运行

以下为使用arduino-cli的编译及运行示例，使用Arduino IDE的开发者请直接打开项目examples/arduino内例程即可

```bash
$ export NODA_PATH=您的noda项目根目录
$ cd ${NODA_PATH}/examples/arduino                          # 然后打开03_cloud/03_cloud.ino，修改文件内指定的宏，填写实际的 WiFi ssid/password
$ arduino-cli compile --fqbn esp32:esp32:esp32s3 03_cloud   # 根据实际版型填写--fqbn参数
$ arduino-cli upload --fqbn esp32:esp32:esp32s3 03_cloud    # 向/dev/ttyACM0端口烧录固件
$ arduino-cli monitor -p /dev/ttyACM0                       # 打开/dev/ttyACM0端口查看固件的打印信息
```

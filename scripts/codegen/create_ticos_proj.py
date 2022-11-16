# coding=utf-8
import os, sys, shutil, argparse

from datetime import datetime
from string import Template
from create_ticos_hal import generate as hal_generator

INSTLER = 'install.' 'sh' # TODO the file ext name should be detected by os
MAIN_C  = 'main_c'
CONF_H  = 'conf_h'
PROJ_H  = 'proj_h'
CLSNAME = 'ticos_iot'
DEVNAME = 'DEV_IOT'
PRIVATE = 'const char* ssid;' \
          'const char* pswd;' \
          'const char* fqdn;' \
          'const char* product_id;'  \
          'const char* device_id;'  \
          'const char* secret_key;'
MQTTHAL = 'mqtt_wrapper.c'
IOT_DEF = '#include "ticos_iot.h"\n'
BUS_ADD = ''
DEV_ADD = '    TICOS_DEV(' + DEVNAME + ', ' + CLSNAME + ',\n' \
          '             /* 请填充测试所需的 WiFi ssid */\n' \
          '             .ssid="SSID",\n' \
          '             /* 请填充测试所需的 WiFi password */\n' \
          '             .pswd="PSWD",\n' \
          '             /* 请填充测试所需的 mqtt fqdn */\n' \
          '             .fqdn="mqtt://hub.ticos.cn",\n' \
          '             /* 请填充测试所需的 product id */\n' \
          '             .product_id="PRODUCT ID",\n ' \
          '             /* 请填充测试所需的 device id */\n' \
          '             .device_id="DEVICE ID",\n' \
          '             /* 请填充测试所需的 security key */\n' \
          '             .secret_key="SECRET KEY")\n'

def copy_file(src, dst):
    s = ''
    with open(src, 'r') as f:
        s = f.read()
    if not s:
        raise Exception('文件读取失败： %s' % src)
    with open(dst, 'w') as f:
        f.write(s)

def gen_cmake_file(name, thingmodel, tmpl_dir, to_path):
    file_name = 'CMakeLists.txt'
    lines = []
    sdk = '' if not thingmodel else 'set (TICOS_CLOUD_SDK ticos-sdk-for-c)\n'
    with open(tmpl_dir + '/' + file_name, 'r') as f:
        tmpl = Template(f.read())
        lines.append(tmpl.safe_substitute(
                    TICOS_PROJ_NAME     = name,
                    TICOS_USE_CLOUD_SDK = sdk))
    with open(to_path + '/' + file_name, 'w') as f:
        f.writelines(lines)

def gen_conf_h(date_time, tmpl, thingmodel, to):
    file_name = 'ticos_config.h'
    iot_def = IOT_DEF if thingmodel else ''
    bus_add = BUS_ADD if thingmodel else ''
    dev_add = DEV_ADD if thingmodel else ''
    lines = []
    with open(tmpl + '/' + CONF_H, 'r') as f:
        tmpl = Template(f.read())
        lines.append(tmpl.substitute(
                    FILE_NAME = file_name,
                    DATE_TIME = date_time,
                    IOT_DEF = iot_def,
                    BUS_ADD = bus_add,
                    DEV_ADD = dev_add))
    with open(to + '/' + file_name, 'w') as f:
        f.writelines(lines)

def gen_main_c(name, ext, date_time, tmpl, to):
    file_name = name + '.' + ext
    lines = []
    with open(tmpl + '/' + MAIN_C, 'r') as f:
        tmpl = Template(f.read())
        lines.append(tmpl.substitute(
                    FILE_NAME = file_name,
                    DATE_TIME = date_time))
    with open(to + '/' + file_name, 'w') as f:
        f.writelines(lines)

def gen_codes(name, ext, tmpl, thingmodel, to):
    date_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    if thingmodel:
        copy_file(tmpl + '/' + MQTTHAL, to + '/' + MQTTHAL)
        hal_generator(CLSNAME, DEVNAME, private=PRIVATE, thingmodel=thingmodel, to=to)
    gen_conf_h(date_time, tmpl, thingmodel, to)
    gen_main_c(name, ext, date_time, tmpl, to)
    copy_file(tmpl + '/' + PROJ_H, to + '/ticos_project.h')

def gen_for_esp32(name, tmpl, thingmodel, to):
    code_path = to + '/main'
    copy_file(tmpl + '/tools/' + INSTLER, to + '/' + INSTLER)
    gen_cmake_file(name, thingmodel, to, to)
    gen_cmake_file(name, thingmodel, code_path, code_path)
    gen_codes(name, 'c', tmpl, thingmodel, code_path)

def gen_for_arduino(name, tmpl, thingmodel, to):
    gen_codes(name, 'ino', tmpl, thingmodel, to)

def generate(name, platform, thingmodel='', to='.'):
    if not name:
        raise Exception('项目名(--name)参数必须填写')
    if not platform:
        platform = 'arduino'
    py_dir = os.path.dirname(os.path.abspath(__file__))
    tmpl = py_dir + '/templates'
    root = to + '/' + name
    tmpl_platform = tmpl + '/tmpl_' + platform

    if os.path.exists(tmpl_platform):
        shutil.copytree(tmpl_platform, root)
    else:
        os.mkdir(root)

    globals()['gen_for_' + platform](name, tmpl, thingmodel, root)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='ticos project generator')
    parser.add_argument('--name', type=str, help='project name')
    parser.add_argument('--platform', type=str, help='supported platform: arduino (default) | esp32')
    parser.add_argument('--thingmodel', type=str, help='json file|data of thing model')
    parser.add_argument('--to', type=str, default='.', help='target directory')
    args = parser.parse_args()
    generate(args.name, args.platform, args.thingmodel, args.to)

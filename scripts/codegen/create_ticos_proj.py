# coding=utf-8
import os, sys, shutil, argparse

from datetime import datetime
from string import Template
from create_ticos_hal import generate as hal_generator

INSTLER = 'install.' 'sh' # TODO the file ext name should be detected by os
MAIN_C  = 'main_c'
DEVNAME = 'ticos_iot'
PRIVATE = 'const char* ssid;' \
          'const char* pswd;' \
          'const char* fqdn;' \
          'const char* product_id;'  \
          'const char* device_id;'  \
          'const char* secret_key;'
MQTTHAL = 'mqtt_wrapper.c'
IOT_DEF = '#include "ticos_iot.h"\n' \
          '\n' \
          '/* 请填充测试所需的 WiFi ssid */\n' \
          '#define _SSID ""\n' \
          '/* 请填充测试所需的 WiFi password */\n' \
          '#define _PSWD ""\n' \
          '/* 请填充测试所需的 mqtt fqdn */\n' \
          '#define _FQDN "mqtt://hub.ticos.cn"\n' \
          '/* 请填充测试所需的 product id */\n' \
          '#define _PRD_ID "PRD_ID"\n' \
          '/* 请填充测试所需的 device id */\n' \
          '#define _DEV_ID "DEV_ID"\n' \
          '/* 请填充测试所需的 security key */\n' \
          '#define _SKEY   "SKEY"\n'
BUS_IDS = ''
DEV_IDS = '    DEV_IOT,\n'
BUS_ADD = ''
DEV_ADD = '    TICOS_DEV(DEV_IOT, ticos_iot, .ssid=_SSID, .pswd=_PSWD, .fqdn=_FQDN,\n' \
          '            .product_id=_PRD_ID, .device_id=_DEV_ID, .secret_key=_SKEY);\n'

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

def gen_entry_file(name, ext, tmpl, thingmodel, to):
    file_name = name + '.' + ext
    date_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    iot_def = IOT_DEF if thingmodel else ''
    bus_ids = BUS_IDS if thingmodel else ''
    dev_ids = DEV_IDS if thingmodel else ''
    bus_add = BUS_ADD if thingmodel else ''
    dev_add = DEV_ADD if thingmodel else ''
    lines = []
    with open(tmpl + '/' + MAIN_C, 'r') as f:
        tmpl = Template(f.read())
        lines.append(tmpl.substitute(
                    FILE_NAME = file_name,
                    DATE_TIME = date_time,
                    IOT_DEF = iot_def,
                    BUS_IDS = bus_ids,
                    DEV_IDS = dev_ids,
                    BUS_ADD = bus_add,
                    DEV_ADD = dev_add))
    with open(to + '/' + file_name, 'w') as f:
        f.writelines(lines)

def gen_codes(name, ext, tmpl, thingmodel, to):
    if thingmodel:
        copy_file(tmpl + '/' + MQTTHAL, to + '/' + MQTTHAL)
        hal_generator(DEVNAME, private=PRIVATE, thingmodel=thingmodel, to=to)
    gen_entry_file(name, ext, tmpl, thingmodel, to)

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

# coding=utf-8
import os, sys, shutil, argparse

from noda_hal_gen import generate as hal_generator

MAIN_C  = 'tmpl_main'
DEVNAME = 'noda_iot'
PRIVATE = 'const char* ssid;' \
          'const char* pswd;' \
          'const char* fqdn;' \
          'const char* pid;'  \
          'const char* did;'  \
          'const char* skey;'
MQTTHAL = 'ticos_hal.c'

def copy_file(src, dst):
    s = ''
    with open(src, 'r') as f:
        s = f.read()
    if not s:
        raise Exception('文件读取失败： %s' % src)
    with open(dst, 'w') as f:
        f.write(s)

def gen_codes(name, ext, tmpl, thingmodel, to):
    copy_file(tmpl + '/' + MAIN_C,  to + '/' + name + '.' + ext)
    copy_file(tmpl + '/' + MQTTHAL, to + '/' + MQTTHAL)
    hal_generator(DEVNAME, private=PRIVATE, thingmodel=thingmodel, to=to)

def gen_for_esp32(name, tmpl, thingmodel, to):
    gen_codes(name, 'c', tmpl, thingmodel, to + '/main')

def gen_for_arduino(name, tmpl, thingmodel, to):
    gen_codes(name, 'ino', tmpl, thingmodel, to)

def generate(name, platform, thingmodel='', to='.'):
    if not name:
        raise Exception('项目名(--name)参数必须填写')
    if not platform:
        platform = 'arduino'
    py_dir = os.path.dirname(os.path.abspath(__file__))
    tmpl = py_dir + '/templates/ticos_proj_tmpl'
    root = to + '/' + name

    shutil.copytree(tmpl + '/' + platform, root)

    globals()['gen_for_' + platform](name, tmpl, thingmodel, root)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='noda ticos project generator')
    parser.add_argument('--name', type=str, help='project name')
    parser.add_argument('--platform', type=str, help='supported platform: arduino (default) | esp32')
    parser.add_argument('--thingmodel', type=str, help='json file|data of thing model')
    parser.add_argument('--to', type=str, default='.', help='target directory')
    args = parser.parse_args()
    generate(args.name, args.platform, args.thingmodel, args.to)

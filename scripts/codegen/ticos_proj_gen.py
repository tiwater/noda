# coding=utf-8
import os, sys, re, argparse

from datetime import datetime
from string import Template

from ticos_hal_gen import generate as hal_generator

TMPL_MAIN_C = 'main_c'
IOT_DEVNAME = 'ticos_iot'

def gen_proj_cmake_file(name, tmpl_file, to_path):
    file_name = 'CMakeLists.txt'
    lines = []
    with open(tmpl_file, 'r') as f:
        tmpl = Template(f.read())
        lines.append(tmpl.safe_substitute(
                    TICOS_PROJ_NAME = name))
    with open(to_path + '/' + file_name, 'w') as f:
        f.writelines(lines)

def gen_proj_entry_file(name, ext, tmpl_file, date_time, to_path):
    file_name = name + '.' + ext
    lines = []
    with open(tmpl_file, 'r') as f:
        tmpl = Template(f.read())
        lines.append(tmpl.substitute(
                    FILE_NAME = file_name,
                    DATE_TIME = date_time))
    with open(to_path + '/' + file_name, 'w') as f:
        f.writelines(lines)

def gen_unix_proj(name, tmpl_dir, date_time, thingmodel):
    code_path = name
    tmpl_main = tmpl_dir + TMPL_MAIN_C
    tmpl_cmake = tmpl_dir + 'proj_tmpl_unix/cmake_lists_txt'
    gen_proj_entry_file(name, 'c', tmpl_main, date_time, code_path)
    gen_proj_cmake_file(name, tmpl_cmake, code_path)
    if thingmodel:
        hal_generator(IOT_DEVNAME, thingmodel=thingmodel, to=code_path)

def gen_esp32_proj(name, tmpl_dir, date_time, thingmodel):
    code_path = name + '/main'
    tmpl_main = tmpl_dir + TMPL_MAIN_C
    tmpl_cmake_list_root = tmpl_dir + 'proj_tmpl_esp32/cmake_lists_root'
    tmpl_cmake_list_main = tmpl_dir + 'proj_tmpl_esp32/cmake_lists_main'
    if not os.path.exists(code_path):
        os.mkdir(code_path)
    gen_proj_entry_file(name, 'c', tmpl_main, date_time, code_path)
    gen_proj_cmake_file(name, tmpl_cmake_list_root, name)
    gen_proj_cmake_file(name, tmpl_cmake_list_main, code_path)
    if thingmodel:
        hal_generator(IOT_DEVNAME, thingmodel=thingmodel, to=code_path)

def gen_arduino_proj(name, tmpl_dir, date_time, thingmodel):
    code_path = name
    tmpl_main = tmpl_dir + TMPL_MAIN_C
    gen_proj_entry_file(name, 'ino', tmpl_main, date_time, code_path)
    if thingmodel:
        hal_generator(IOT_DEVNAME, thingmodel=thingmodel, to=code_path)

def generate(name, platform, thingmodel=''):
    if not name:
        raise Exception('项目名(--name)参数必须填写')
    if not platform:
        platform = 'arduino'
    date_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    py_dir = os.path.dirname(os.path.abspath(__file__))
    tmpl_dir = py_dir + '/templates/'

    if not os.path.exists(name):
        os.mkdir(name)

    globals()['gen_%s_proj' % platform](name, tmpl_dir, date_time, thingmodel)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='ticos_proj_gen')
    parser.add_argument('--name', type=str, help='project name')
    parser.add_argument('--platform', type=str, help='supported platform: arduino (default) | esp32 | unix')
    parser.add_argument('--thingmodel', type=str, help='the json file path of thing model')
    args = parser.parse_args()
    generate(args.name, args.platform, args.thingmodel)

# -*- coding: utf-8 -*-
import os, sys, re, argparse

from datetime import datetime
from string import Template

reload(sys)
sys.setdefaultencoding('utf-8')

def type_to_iot_val_enum(t):
    ''' 根据实际数据类型返回对应的TICOS_IOT_VAL_TYPE '''
    if t == 'float':
        return 'TICOS_IOT_VAL_TYPE_FLOAT'
    elif t == 'int':
        return 'TICOS_IOT_VAL_TYPE_INTEGER'
    elif t == 'str':
        return 'TICOS_IOT_VAL_TYPE_STRING'
    else:
        raise Exception('类型名不存在：%s', t);

def gen_func_head_getter(cls_name, _key, _id, _type):
    return '\n' + _type + ' ti_iot_' + _key + '_' + _id + '(void)'

def gen_func_head_setter(cls_name, _key, _id, _type):
    return '\nint ti_iot_' + _key + '_' + _id + '(' + _type + ' ' + _id + ')'

def gen_func_body_getter(cls_name, _key, _id, _type):
    ''' 根据物模型json内容返回对应的getter函数内容 '''
    return ' {' \
        + '\n    ' + cls_name + '_t* iot = noda_dev(0, ' + cls_name + ');' \
        + '\n    return noda_cache_get(iot, ' + _key + '_' +  _id + ');' \
        + '\n}\n'

def gen_func_body_setter(cls_name, _key, _id, _type):
    ''' 根据物模型json内容返回对应的setter函数内容 '''
    return ' {' \
        + '\n    ' + cls_name + '_t* iot = noda_dev(0, ' + cls_name + ');' \
        + '\n    noda_cache_set(iot, ' + _key + '_' + _id + ', ' + _id + ');' \
        + '\n    return 0;\n}\n'

def gen_func_decs(s, _key, cls_name, need_getter, need_setter):
    ''' 根据物模型json内容返回对应的函数声明 '''
    decs = ''
    for item in s[_key]:
        _i = item['id']
        _t = item['type']
        if need_getter:
            decs += gen_func_head_getter(cls_name, _key, _i, _t) + ';'
        if need_setter:
            decs += gen_func_head_setter(cls_name, _key, _i, _t) + ';'
    return decs

def gen_func_defs(s, _key, cls_name, need_getter, need_setter):
    ''' 根据物模型json内容返回对应的函数定义 '''
    defs = ''
    for item in s[_key]:
        _i = item['id']
        _t = item['type']
        if need_getter:
            head = gen_func_head_getter(cls_name, _key, _i, _t)
            defs += head + gen_func_body_getter(cls_name, _key, _i, _t)
        if need_setter:
            head = gen_func_head_setter(cls_name, _key, _i, _t)
            defs += head + gen_func_body_setter(cls_name, _key, _i, _t)
    return defs

def gen_table(s, _key):
    ''' 根据物模型json内容返回对应的方法表成员注册 '''
    tab = ''
    for item in s[_key]:
        _i = item['id']
        _t = item['type']
        _e = type_to_iot_val_enum(_t)
        tab += '\n    { \"%s\", %s, ti_iot_%s_%s },' %(_i, _e, _t, _i)
    if tab:
        tab += '\n'
    else:
        tab = ' NULL '
    return tab

def gen_enum(s, _key):
    ''' 根据物模型json文件返回对应的物模型枚举列表 '''
    _enum = ''
    for item in s[_key]:
        _i = item['id']
        _enum += '\n    TICOS_IOT_' + _key.upper() + '_' + _i + ','
    return _enum + '\n    TICOS_IOT_' + _key.upper() + '_MAX,\n'

def gen_public_vars(s, _key):
    _vars = ''
    for item in s[_key]:
        _i = item['id']
        _t = item['type']
        _vars += _t + ' ' + _key + '_' + _i + ';'
    return _vars

def gen_iot(cls_name, date, tmpl_dir, json_file):
    ''' 根据物模型json文件返回对应的物模型接口文件 '''
    import json

    raw = None
    with open(json_file, 'r') as f:
        raw = json.load(f)

    if not raw:
        raise Exception('物模型文件异常')

    tele_key = 'telemetry'
    prop_key = 'property'
    cmmd_key = 'command'

    func_decs = ''
    tele_enum = ''
    prop_enum = ''
    cmmd_enum = ''

    func_defs = ''
    tele_tabs = ''
    prop_tabs = ''
    cmmd_tabs = ''

    public_vars = ''

    func_decs += gen_func_decs(raw, tele_key, cls_name, True, False)
    func_defs += gen_func_defs(raw, tele_key, cls_name, True, False)
    tele_tabs += gen_table(raw, tele_key)
    tele_enum += gen_enum(raw, tele_key)
    public_vars += gen_public_vars(raw, tele_key)
    func_decs += gen_func_decs(raw, prop_key, cls_name, True, True)
    func_defs += gen_func_defs(raw, prop_key, cls_name, True, True)
    prop_tabs += gen_table(raw, prop_key)
    prop_enum += gen_enum(raw, prop_key)
    public_vars += gen_public_vars(raw, prop_key)
    func_decs += gen_func_decs(raw, cmmd_key, cls_name, False, True)
    func_defs += gen_func_defs(raw, cmmd_key, cls_name, False, True)
    cmmd_tabs += gen_table(raw, cmmd_key)
    cmmd_enum += gen_enum(raw, cmmd_key)
    public_vars += gen_public_vars(raw, cmmd_key)

    dot_c_lines = []
    with open(tmpl_dir + 'iot_c', 'r') as f:
        tmpl = Template(f.read())
        dot_c_lines.append(tmpl.substitute(
                    GEN_DATE = date,
                    CLS_NAME = cls_name,
                    FUNC_DEFS = func_defs,
                    TELEMETRY_TABS = tele_tabs,
                    PROPERTY_TABS = prop_tabs,
                    COMMAND_TABS = cmmd_tabs))
    with open('ti_thingmodel.c', 'w') as f:
        f.writelines(dot_c_lines)

    dot_h_lines = []
    with open(tmpl_dir + 'iot_h', 'r') as f:
        tmpl = Template(f.read())
        dot_h_lines.append(tmpl.substitute(
                    GEN_DATE = date,
                    FUNC_DECS = func_decs,
                    TELEMETRY_ENUM = tele_enum,
                    PROPERTY_ENUM = prop_enum,
                    COMMAND_ENUM = cmmd_enum))
    with open('ti_thingmodel.h', 'w') as f:
        f.writelines(dot_h_lines)

    return public_vars

def gen_hal(cls_name, date, tmpl_dir, private_vars='', public_vars=''):
    cls_name_upper_case = cls_name.upper()

    prvs = private_vars.replace('; ', ';').strip()
    prvs = '' if not prvs else '    ' + prvs.replace(';', ';\n    ')[:-4]
    puvs = public_vars.replace('; ', ';').strip()
    puvs = puvs.replace(' ', ', ')
    puvs = '' if not puvs else '    NODA_VAR(' + puvs.replace(';', ');\n    NODA_VAR(')[:-14]

    dot_h_lines = []
    with open(tmpl_dir + 'dev_h', 'r') as f:
        tmpl = Template(f.read())
        dot_h_lines.append(tmpl.substitute(
                GEN_DATE = date,
                CLS_NAME = cls_name,
                CLS_NAME_UPPER_CASE = cls_name_upper_case,
                CLS_MEMBER_VAR_LIST = prvs + puvs))
    with open(r'%s.h' % cls_name, 'w') as f:
        f.writelines(dot_h_lines)

    regex = r'NODA_VAR.*,'
    sync_from_cache = re.sub(regex, 'noda_sync_from_cache(self,', puvs)
    post_to_cache = re.sub(regex, 'noda_post_to_cache(self,', puvs)

    dot_c_lines = []
    with open(tmpl_dir + 'dev_c', 'r') as f:
        tmpl = Template(f.read())
        dot_c_lines.append(tmpl.substitute(
                GEN_DATE = date,
                CLS_NAME = cls_name,
                SYNC_FROM_CACHE = sync_from_cache,
                POST_TO_CACHE = post_to_cache))

    with open(r'%s.c' % cls_name, 'w') as f:
        f.writelines(dot_c_lines)

def generate(name, private_vars='', public_vars='', json_file=''):
    if not name:
        raise Exception('类型名(--name)参数必须填写')
    datetime_mark = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    py_dir = os.path.dirname(os.path.abspath(__file__))
    tmpl_dir = py_dir + '/templates/'

    if json_file:
        public_vars += gen_iot(name, datetime_mark, tmpl_dir, json_file)

    if private_vars or public_vars:
        gen_hal(name, datetime_mark, tmpl_dir, private_vars, public_vars)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='noda_hal_gen')
    parser.add_argument('--name', type=str, help='class name')
    parser.add_argument('--private', type=str, default='', help='private vars')
    parser.add_argument('--public', type=str, default='', help='public vars')
    parser.add_argument('--json', type=str, default='', help='iot json file')
    args = parser.parse_args()
    generate(args.name, args.private, args.public, args.json)

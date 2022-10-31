# coding=utf-8
import os, sys, re, argparse

from datetime import datetime
from string import Template

TELE = 'telemetry'
PROP = 'property'
CMMD = 'command'

NAME = 'name'
TYPE = '@type'
SCHEMA = 'schema'

''' IOT数据类型 到 c语言类型 的字典 '''
iot_type_map = {
    "boolean":  "bool",
    "integer":  "int",
    "float"  :  "float",
    "double" :  "float", # TODO 需要后期支持
    "string" :  "const char*",
    "enum"   :  "int",   # TODO 是否可以映射short类型?
    "timestamp":"time_t",
    "duration" :"time_t" }

def type_to_c_type(t):
    ''' 根据iot_type_map字典返回 c语言类型 '''
    return iot_type_map[t]

def gen_iot_val_type(t):
    return 'TICOS_VAL_TYPE_' + t.upper()

def gen_func_name_getter(_key, _id):
    return ' ticos_' + _key + '_' + _id + '_send'

def gen_func_name_setter(_key, _id):
    return 'ticos_' + _key + '_' + _id + '_recv'

def gen_func_head_getter(_key, _id, _type):
    return '\n' + _type + gen_func_name_getter(_key, _id) + '(void)'

def gen_func_head_setter(_key, _id, _type):
    return '\nint %s(%s %s_)' %(gen_func_name_setter(_key, _id), _type, _id)

def gen_func_body_getter(cls_name, _key, _id, _type):
    ''' 根据物模型json内容返回对应的getter函数内容 '''
    body = '\n    ' + cls_name + '_t* iot = ticos_dev(0, ' + cls_name + ');' \
         + '\n    return ticos_cache_get(iot, ' + _key[:4] + '_' +  _id + ');'
    return ' {' + body + '\n}\n'

def gen_func_body_setter(cls_name, _key, _id, _type):
    ''' 根据物模型json内容返回对应的setter函数内容 '''
    body = '\n    ' + cls_name + '_t* iot = ticos_dev(0, ' + cls_name + ');' \
         + '\n    ticos_cache_set(iot, ' + _key[:4] + '_' + _id + ', ' + _id + '_);'
    return ' {' + body + '\n    return 0;\n}\n'

def gen_func_decs(item, cls_name, need_getter, need_setter):
    ''' 根据物模型json内容返回对应的函数声明 '''
    decs = ''
    _k = item[TYPE]
    _i = item[NAME]
    _t = type_to_c_type(item[SCHEMA])
    if need_getter:
        decs += gen_func_head_getter(_k, _i, _t) + ';'
    if need_setter:
        decs += gen_func_head_setter(_k, _i, _t) + ';'
    return decs

def gen_func_defs(item, cls_name, need_getter, need_setter):
    ''' 根据物模型json内容返回对应的函数定义 '''
    defs = ''
    _k = item[TYPE]
    _i = item[NAME]
    _t = type_to_c_type(item[SCHEMA])
    if need_getter:
        head = gen_func_head_getter(_k, _i, _t)
        defs += head + gen_func_body_getter(cls_name, _k, _i, _t)
    if need_setter:
        head = gen_func_head_setter(_k, _i, _t)
        defs += head + gen_func_body_setter(cls_name, _k, _i, _t)
    return defs

def gen_table(item, need_getter, need_setter):
    ''' 根据物模型json内容返回对应的方法表成员注册 '''
    _k = item[TYPE]
    _i = item[NAME]
    _t = item[SCHEMA]
    _e = gen_iot_val_type(_t)
    getter = gen_func_name_getter(_k, _i)
    setter = gen_func_name_setter(_k, _i)
    if need_getter:
        if need_setter:
            return '\n    { \"%s\", %s, %s, %s },' %(_i, _e, getter, setter)
        else:
            return '\n    { \"%s\", %s, %s },' %(_i, _e, getter)
    else:
        return '\n    { \"%s\", %s, %s },' %(_i, _e, setter)

def gen_enum(item):
    ''' 根据物模型json文件返回对应的物模型枚举列表 '''
    _k = item[TYPE].upper()
    _i = item[NAME]
    return '\n    TICOS_' + _k + '_' + _i + ','

def gen_puvs(item):
    ''' 根据物模型json文件返回对应的成员变量 '''
    _k = item[TYPE]
    _i = item[NAME]
    _t = type_to_c_type(item[SCHEMA])
    return  _t + ' ' + _k[:4] + '_' + _i + ';'

def gen_iot(cls_name, date_time, tmpl_dir, thingmodel, to='.'):
    ''' 根据物模型json文件返回对应的物模型接口文件 '''
    import json

    raw = None
    if thingmodel.endswith('.json'):
        with open(thingmodel, 'r') as f:
            raw = json.load(f)
    else:
        raw = json.loads(thingmodel)

    if not raw:
        raise Exception('物模型解析异常')

    func_decs = ''
    tele_enum = ''
    prop_enum = ''
    cmmd_enum = ''

    func_defs = ''
    tele_tabs = ''
    prop_tabs = ''
    cmmd_tabs = ''

    puvs = ''

    for item in raw[0]['contents']:
        item[TYPE] = item[TYPE].lower()
        _type = item[TYPE]
        if _type == TELE:
            func_decs += gen_func_decs(item, cls_name, True, False)
            func_defs += gen_func_defs(item, cls_name, True, False)
            tele_tabs += gen_table(item, True, False)
            tele_enum += gen_enum(item)
        elif _type == PROP:
            func_decs += gen_func_decs(item, cls_name, True, True)
            func_defs += gen_func_defs(item, cls_name, True, True)
            prop_tabs += gen_table(item, True, True)
            prop_enum += gen_enum(item)
        elif _type == CMMD:
            func_decs += gen_func_decs(item, cls_name, False, True)
            func_defs += gen_func_defs(item, cls_name, False, True)
            cmmd_tabs += gen_table(item, False, True)
            cmmd_enum += gen_enum(item)
        puvs += gen_puvs(item)
    tele_enum += gen_enum({ TYPE:TELE, NAME:'MAX'}) + '\n'
    prop_enum += gen_enum({ TYPE:PROP, NAME:'MAX'}) + '\n'
    cmmd_enum += gen_enum({ TYPE:CMMD, NAME:'MAX'}) + '\n'

    dot_c_lines = []
    with open(tmpl_dir + 'iot_c', 'r') as f:
        tmpl = Template(f.read())
        dot_c_lines.append(tmpl.substitute(
                    DATE_TIME = date_time,
                    CLS_NAME = cls_name,
                    FUNC_DEFS = func_defs,
                    TELEMETRY_TABS = tele_tabs,
                    PROPERTY_TABS = prop_tabs,
                    COMMAND_TABS = cmmd_tabs))
    with open(to + '/ticos_thingmodel.c', 'w') as f:
        f.writelines(dot_c_lines)

    dot_h_lines = []
    with open(tmpl_dir + 'iot_h', 'r') as f:
        tmpl = Template(f.read())
        dot_h_lines.append(tmpl.substitute(
                    DATE_TIME = date_time,
                    FUNC_DECS = func_decs,
                    TELEMETRY_ENUM = tele_enum,
                    PROPERTY_ENUM = prop_enum,
                    COMMAND_ENUM = cmmd_enum))
    with open(to + '/ticos_thingmodel.h', 'w') as f:
        f.writelines(dot_h_lines)

    return puvs

def gen_hal(cls_name, date_time, tmpl_dir, prvs='', puvs='',
            inc_list='', on_open='', on_close='', from_dev='', to_dev='',
            to='.'):
    cls_name_upper_case = cls_name.upper()

    prvs = re.sub(r'(.*?);', r'    \1;\n', prvs)
    puvs = re.sub(r'(.*?) (\w+);', r'    NODA_VAR(\1, \2);\n', puvs)

    dot_h_lines = []
    with open(tmpl_dir + 'dev_h', 'r') as f:
        tmpl = Template(f.read())
        dot_h_lines.append(tmpl.substitute(
                DATE_TIME = date_time,
                CLS_NAME = cls_name,
                CLS_NAME_UPPER_CASE = cls_name_upper_case,
                CLS_MEMBER_VAR_LIST = prvs + puvs))
    with open(r'%s/%s.h' % (to, cls_name), 'w') as f:
        f.writelines(dot_h_lines)

    regex = r'NODA_VAR.*,'
    from_cache = re.sub(regex, 'ticos_sync_from_cache(self,', puvs)
    to_cache = re.sub(regex, 'ticos_post_to_cache(self,', puvs)

    dot_c_lines = []
    with open(tmpl_dir + 'dev_c', 'r') as f:
        tmpl = Template(f.read())
        dot_c_lines.append(tmpl.substitute(
                DATE_TIME   = date_time,
                CLS_NAME    = cls_name,
                INC_LIST    = inc_list,
                ON_OPEN     = on_open,
                ON_CLOSE    = on_close,
                FROM_CACHE  = from_cache,
                TO_CACHE    = to_cache,
                FROM_DEV    = from_dev,
                TO_DEV      = to_dev))

    with open(r'%s/%s.c' % (to, cls_name), 'w') as f:
        f.writelines(dot_c_lines)

def generate(name, private='', public='', thingmodel='', to='.'):
    if not name:
        raise Exception('类型名(--name)参数必须填写')
    date_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    py_dir = os.path.dirname(os.path.abspath(__file__))
    tmpl_dir = py_dir + '/templates/'

    prvs        = private
    puvs        = public

    inc_list    = ''
    on_open     = '    NODA_UNUSED(self);\n'
    on_close    = '    NODA_UNUSED(self);\n'
    from_dev    = '    NODA_UNUSED(self);\n'
    to_dev      = '    NODA_UNUSED(self);\n'
    dirty_cond  = ''

    if thingmodel:
        iot_puvs = gen_iot(name, date_time, tmpl_dir, thingmodel, to)
        if iot_puvs:
            dirty_cond = re.sub('.*? (\w+);', r'ticos_cache_isdirty(self, \1)\n     || ', iot_puvs)[:-9]
            puvs += iot_puvs
    prvs = prvs.replace('; ', ';').strip()
    puvs = puvs.replace('; ', ';').strip()
    if thingmodel:
        # FIXME 临时填充，后继应该以更优雅方式自动填充
        inc_list  = '#include <noda/nil/wifi.h>\n' \
                    '#include <ticos_api.h>\n'
        on_open   = '    ticos_wifi_start_as_sta(self->ssid, self->pswd);\n' \
                    '    ticos_cloud_start(self->pid, self->did, self->skey);\n'
        on_close += '    ticos_cloud_stop();\n' \
                    '    ticos_wifi_stop();\n'
        from_dev  = '' if not puvs else \
                    '    if (%s) {\n' \
                    '        ticos_property_report();\n' \
                    '    }\n' \
                    % (dirty_cond)

    if prvs or puvs:
        gen_hal(name, date_time, tmpl_dir, prvs, puvs,
                inc_list, on_open, on_close, to_dev, from_dev,
                to)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='ticos_hal_gen')
    parser.add_argument('--name', type=str, help='class name')
    parser.add_argument('--private', type=str, default='', help='private vars')
    parser.add_argument('--public', type=str, default='', help='public vars')
    parser.add_argument('--thingmodel', type=str, default='', help='json file|data of thing model')
    parser.add_argument('--to', type=str, default='.', help='target directory')
    args = parser.parse_args()
    generate(args.name, args.private, args.public, args.thingmodel, args.to)

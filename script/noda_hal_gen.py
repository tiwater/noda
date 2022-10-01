import os, sys, re, argparse

from datetime import datetime
from string import Template

def generate(name, private_vars='', public_vars=''):
    if not name:
        raise Exception('类型名(--name)参数必须填写')
    datetime_mark = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    py_dir = os.path.dirname(os.path.abspath(__file__))
    tmpl_dir = py_dir + '/templates/'

    cls_name = name
    cls_name_upper_case = cls_name.upper()

    prvs = private_vars.replace('; ', ';').strip()
    prvs = '    ' + prvs.replace(';', ';\n    ')[:-4]
    puvs = public_vars.replace('; ', ';').strip()
    puvs = puvs.replace(' ', ', ')
    puvs = '    NODA_VAR(' + puvs.replace(';', ');\n    NODA_VAR(')[:-14]

    dot_h_lines = []
    with open(tmpl_dir + 'dev_h', 'r') as f:
        tmpl = Template(f.read())
        dot_h_lines.append(tmpl.substitute(
                GEN_DATE = datetime_mark,
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
                GEN_DATE = datetime_mark,
                CLS_NAME = cls_name,
                SYNC_FROM_CACHE = sync_from_cache,
                POST_TO_CACHE = post_to_cache))

    with open(r'%s.c' % cls_name, 'w') as f:
        f.writelines(dot_c_lines)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='noda_code_gen')
    parser.add_argument('--name', type=str, help='class name')
    parser.add_argument('--private', type=str, default='', help='private vars')
    parser.add_argument('--public', type=str, default='', help='public vars')
    args = parser.parse_args()
    generate(args.name, args.private, args.public)

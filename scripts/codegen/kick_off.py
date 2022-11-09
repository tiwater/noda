# coding=utf-8
import os, sys, argparse

from create_ticos_proj import generate as prj_generator

PROJ_NAME = 'ticos_project'

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='kick off')
    parser.add_argument('--platform', type=str, help='supported platform: arduino (default) | esp32')
    parser.add_argument('--thingmodel', type=str, help='json file|data of thing model')
    parser.add_argument('--to', type=str, default='.', help='target directory')
    args = parser.parse_args()
    prj_generator(PROJ_NAME, args.platform, args.thingmodel, args.to)

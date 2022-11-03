#!/usr/bin/env bash

set -e
set -u

ticos_packages_dir=~/.ticos/packages
ticos_framework=ticos-framework
ticos_cloud_sdk=ticos-sdk-for-c

[ ! -d ${ticos_packages_dir} ] && mkdir -p ${ticos_packages_dir}

cd ${ticos_packages_dir}
if [ ! -d ${ticos_framework} ]; then
    git clone https://github.com/tiwater/${ticos_framework}.git
else
    echo "${ticos_framework} has already existed"
fi
if [ ! -d ${ticos_cloud_sdk} ]; then
    git clone https://github.com/tiwater/${ticos_cloud_sdk}.git
else
    echo "${ticos_cloud_sdk} has already existed"
fi

echo ""
echo "All done!"
echo ""

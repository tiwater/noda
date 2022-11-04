#!/usr/bin/env bash

set -e
set -u

ticos_packages_dir=~/.ticos/packages
ticos_framework=ticos-framework
ticos_cloud_sdk=ticos-sdk-for-c

echo "Ticos SDK installation script."
echo ""

[ ! -d ${ticos_packages_dir} ] && mkdir -p ${ticos_packages_dir}

cd ${ticos_packages_dir}

if [ ! -d ${ticos_framework} ]; then
    echo "Clone ${ticos_framework}"
    git clone https://github.com/tiwater/${ticos_framework}.git
else
    echo "Looking for update to ${ticos_framework}"
    git -C ${ticos_framework} pull
fi
echo ""

if [ ! -d ${ticos_cloud_sdk} ]; then
    echo "Clone ${ticos_cloud_sdk}"
    git clone https://github.com/tiwater/${ticos_cloud_sdk}.git
else
    echo "Looking for update to ${ticos_cloud_sdk}"
    git -C ${ticos_cloud_sdk} pull
fi
echo ""

echo ""
echo "All done!"
echo ""

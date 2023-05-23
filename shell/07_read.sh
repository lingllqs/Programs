#!/bin/bash

# read  -rep "please input y or n:" a
read -n1 -rep "please input y or n:" a # 读取一个字符

# ==用来比较字符串
# -eq用来比较数值
if [[ $a == 'y' || $a == 'Y' ]]; then
    echo "yes"
fi


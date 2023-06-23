#! /bin/sh
#

read -p "please input a number: " number

if [ $number -ge 0 ]; then
    echo "$number is not less than 0"
fi

if test $number -lt 0; then
    echo "$number is less than 0"
fi

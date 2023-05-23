#!/bin/sh

read -p "please input a number: " number 

num=number
if [ $number -lt 0 ]; then
    number=$[-1 * $number]
fi
echo "$number"

#!/bin/sh

i=1
while [ $i -lt 10 ]
do
    j=1 
    while [ $j -le $i ]
    do

        if [ $[$i * $j] -lt 10 ];then
            echo -n "$j * $i = $[$j * $i]  "
        else
            echo -n "$j * $i = $[$j * $i] "
        fi
        j=$[$j + 1]
    done
    echo
    #i=$[$i + 1]
    let i++
done

#! /bin/sh
#

echo "This is a string \"\$*\""

for var in "$*"
do
    echo "$var"
done

echo 'This is a string \"\$@\"'

for var in "$@"
do
    echo "$var"
done

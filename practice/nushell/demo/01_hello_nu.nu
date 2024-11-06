#!/usr/bin/env nu

# 自定义命令
def say_hello [mesg] {
    $"Hello ($mesg)"
}

say_hello rust | describe
say_hello "rust"

def touch_file [] {
    [file1 file2 file3] | each {|filename|
        touch $filename} | ignore # 没有ignore将会返回一个empty list
}

# touch_file

def exponents_of_three [] {
    [0 1 2 3 4 5] | each {|x| {
            3 ** $x
        }
    }
}

exponents_of_three

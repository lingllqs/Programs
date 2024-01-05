#!/usr/bin/env lua

print(type("Hello Rust"))
print(type(20))
print(type(print))
print(type(type))
print(type(false))
print(type(nil))
A = "rust"
print(type(type(A))) -- type 的结果总是一个 string
A = false -- 变量没有预定义类型
print(type(A))

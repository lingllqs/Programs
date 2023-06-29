fn main() {
    // 通常情况下，'{}' 会被任意变量内容替换
    // 变量内容会转化成字符串
    println!("{}", 5); // 输出：5

    // 使用位置参数
    println!("{0} {1} {1} {0}", 0, 1); // 输出：0 1 1 0

    // 使用命名参数
    println!("{first} {second} {first}", second = 2, first = 1); // 输出：1 2 1

    // 在:后面指定特殊的格式
    // b 为二进制格式
    println!("{} {:b}", 9, 12); // 输出 9 1100

    // 指定宽度右对齐
    println!("{number:>width$}", number = 1, width = 6); // 输出：     1

    // 在数字左边补0
    println!("{number:>0width$}", number = 1, width = 6); // 输出：000001
}

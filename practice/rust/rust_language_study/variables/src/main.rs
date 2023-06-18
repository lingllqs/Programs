fn main() {
    let x = 5;
    println!("The value of x is {}", x);

    // x = 6; // 错误，不能对一个不可变变量重新复制
    // println!("The value of x is {}", x);

    // 加上mut关键字定义变量使得变量可变
    let mut y = 7;
    println!("The value of y is {}", y);

    y = 8;
    println!("The value of y is {}", y);

    // 常量使用const关键字声明而不是let,且必须指定类型
    // 约定俗成使用大写字母来起变量名
    // 常量只能设置为常量表达式，不能是函数调用的结果或者只能在运行时计算得到的值
    const ONE_HOURS_IN_SECONDS: u32 = 60 * 60;
    println!("const: {}", ONE_HOURS_IN_SECONDS);

    let z = 5;
    let z = z + 1;
    {
        let z = z * 2;
        println!("The value of z in the inner scope is: {}", z); // 结果为12
    }
    println!("The value of z is: {}", z); // 结果为6
}

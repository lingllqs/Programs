fn main() {
    let mut s = String::from("Rust");
    s.push_str("Python");
    s.push('C');
    println!("{}", s);

    let s1 = String::from("hello");
    let s2 = String::from("world");
    // &s2是&String类型，被强转成&str类型
    // +号相当于调用了fn add(self, s: &str) -> Strung {}
    // add没有获取s2的所有权，所以之后还可以使用
    let s3 = s1 + &s2;
    println!("{} {}", s2, s3);

    let s4 = String::from("Python");
    let s5 = String::from("CPP");
    let s6 = String::from("Qt");

    // 使用+连接
    let s7 = s4 + &s5 + &s6;
    println!("{}", s7);

    // 使用format!宏连接
    // format!和println!工作原理相同，format!返回结果，println!输出到屏幕上
    let s8 = format!("{} {} {}", s7, s5, s6);
    println!("{}", s8);

    let len = String::from("Здравствуйте").len();
    println!("len = {}", len); // 结果是len = 24

    // chars方法操作单独的Unicode标量值
    for c in "नमस्ते".chars() {
        println!("{}", c); // 结果返回6个char类型的值
    }
    println!("len: {}","नमस्ते".len());// 结果是len: 18

    // bytes方法返回每一个原始字节
    for b in "नमस्ते".bytes() {
        println!("{}", b);
    }
}

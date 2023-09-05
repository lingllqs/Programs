fn main() {
    // let triple = (0, -2, 4);
    let triple = (1, -2, 4);

    println!("triple: {:?}", triple);

    // 解构元组
    match triple {
        (0, y, z) => println!("First is '0', 'y' is {:?}, and 'z' is {:?}", y, z),
        // .. 用来忽略元组的其余部分
        (1, ..) => println!("First is '1', and the rest doesn't matter"),
        // _ 表示不将值绑定到变量
        _ => println!("It doesn't matter what they are"),
    }
}

fn main() {
    let names = vec!["Rust", "Python", "c"];

    // iter -在每次迭代中借用集合中的一个元素
    // 这样集合本身不会被改变，循环之后仍可以使用
    for name in names.iter() {
        match name {
            &"Rust" => println!("Rust"),
            _ => println!("Hello {}", name),
        }
    }

    println!("{:?}", names);

    // into_iter 会消耗集合
    let names = vec!["Python", "Rust", "C"];

    for name in names.into_iter() {
        match name {
            "C" => println!("C"),
            _ => println!("hello {}", name),
        }
    }
    // println!("{:?}", names);

    // iter_mut 可变地借用集合中的每个元素，从而允许集合被就地修改

    let mut vs = vec!["cpp", "rust", "python", "c"];

    for v in vs.iter_mut() {
        *v = match v {
            &mut "rust" => "rust to Rust",
            _ => "world",
        }
    }
    println!("vs: {:?}", vs);
}

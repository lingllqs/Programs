fn main() {
    // 新建一个空的vector需要添加类型标注
    // 因为Rust不能推断出vector类型
    let v1: Vec<i32> = Vec::new();

    // 使用初始值来创建一个vector则不需要添加类型标注
    let v2 = vec![1, 2, 3];

    // 不添加类型标注新建一个空集合可以通过push方法增加元素
    // Rust可以推断出vector的类型
    let mut v3 = Vec::new();
    v3.push(5);
    v3.push(6);
    v3.push(7);
    v3.push(8);

    // 访问vector中的元素
    // 使用索引语法
    // 访问越界会panic
    let second = &v3[1];
    println!("The second element is {}", second);

    // 使用get方法，get方法返回的是一个Option<&T>
    // 访问越界返回None
    match v3.get(1) {
        Some(second) => println!("The second element is {}", second),
        None => println!("There is no second element."),
    }

    #[derive(Debug)]
    enum SpreadsheetCell{
        Int(i32),
        Float(f64),
        Text(String),
    }

    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Float(3.14),
        SpreadsheetCell::Text(String::from("Rust")),
    ];

    println!("{:?}", row);
}

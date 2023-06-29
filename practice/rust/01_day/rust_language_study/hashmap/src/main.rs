use std::collections::HashMap;

fn main() {
    let mut map = HashMap::new();

    map.insert("Rust".to_string(), "世界上最好的编程语言");
    map.insert("Python".to_string(), "hello world");
    println!("{:?}", map);

    let key = String::from("Rust");
    let m = map.get(&key);
    println!("{:?}", m);

    for (key, value) in map {
        println!("{}: {}", key, value);
    }

    let text = "hello world wonderful world world";
    let mut map1 = HashMap::new();

    // entry方法返回值为Entry,Entry中or_insert方法返回对应值的可变引用
    for word in text.split_whitespace() {
        // or_insert方法在键对应的值存在时就返回这个值的可变引用
        // 如果不存在则将参数作为新值插入并返回新值的可变引用
        let count = map1.entry(word).or_insert(0);
        // 对对应的值+1操作
        *count += 1;
        // print!("{}", *count);
    }

    println!("{:?}", map1);
}

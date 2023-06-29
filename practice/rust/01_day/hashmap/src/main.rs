use std::collections::HashMap;

fn main() {
    test_02();
}

fn test_02() {
    let text = "hello world ni hao";
    let mut h = HashMap::new();

    for word in text.split_whitespace() {
        let count = h.entry(word).or_insert(0);
        *count += 1;
    }

    println!("{:#?}", h);
}

fn test_01() {
    let mut h1 = HashMap::new();
    h1.insert("Rust".to_string(), 100);
    h1.insert("C".to_string(), 99);
    h1.entry(String::from("Python")).or_insert(90);

    for (k, v) in &h1 {
        println!("{}, {}", k, v);
    }
}

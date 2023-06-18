fn main() {
    let s1 = String::from("Hello");

    let len = calculate_length(&s1);

    println!("The length of '{}' is {}", s1, len);
}

fn calculate_length(s: &String) -> usize {
    s.len()
}

fn first_word(s: &String) -> &str {
    // 使用as_bytes方法将String 转化为字节数组
    let bytes = s.as_bytes();

    // enumerate将iter结果包装为一个集合，返回的元组中两个元素分别是索引和集合中的元素引用
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' { 
            return &s[0..i];
        }
    }

    &s[..]
}

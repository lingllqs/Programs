fn main() {
    let some_u8_value = Some(0u8);
    match some_u8_value {
        Some(3) => println!("three"),
        _ => (),
    }
    
    // 等价于
    if let Some(3) = some_u8_value {
        println!("three");
    }
}

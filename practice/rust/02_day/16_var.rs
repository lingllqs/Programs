fn main() {
    let _immutable_binding = 1;  // 不可变绑定
    let mut mutable_binding = 1; // 可变绑定

    println!("Before mutation: {}", mutable_binding);

    mutable_binding += 1;

    println!("After mutation: {}", mutable_binding);
}

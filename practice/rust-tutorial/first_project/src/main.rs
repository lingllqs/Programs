// prelude
use std::io;

fn main() {
    println!("Please input msg");
    let mut buf = String::new();
    let ret = io::stdin()
        .read_line(&mut buf)
        .expect("Failed to recv input");
    println!("Message is {}", buf);
    println!("ret = {}", ret);

    let c = 'r';
    let s = "rust";
    println!("Size of c is {}", c.len_utf16());
    println!("Size of s is {}", s.len());
}
// library crate 只能有一个
// binary crate 可以有多个

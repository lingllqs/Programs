#![allow(dead_code)]

fn age() -> u32 {
    10
}

fn test_01() {
    println!("Tell me what type of person you are");

    match age() {
        0 => println!("I haven't celebrated my first birthday yet"),
        n @ 1..=12 => println!("I'm child of age {:?}", n),
        n @ 13..=18 => println!("I'm a teen of age {:?}", n),
        n => println!("I'm an old person of age {:?}", n),
    }
}

fn some_number() -> Option<u32> {
    Some(55)
}

fn test_02() {
    match some_number() {
        Some(n @ 44) => println!("The Answer: {}", n),
        // Some(55) => println!("55"),
        Some(n) => println!("Not interesting... {}", n),
        _ => (),
    }
}

fn main() {
    test_02();
}

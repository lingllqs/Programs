fn main() {
    let mut optional = Some(3);

    while let Some(i) = optional {
        if i > 9 {
            println!("Greater than 9, quit");
            optional = None;
        } else {
            println!("`i` is `{:?}`. Try again.", i);
            optional = Some(i + 1);
        }
    }
    // if let 有可选的 else/else if 分句
    // while let 没有
}

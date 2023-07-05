// 隐藏为使用代码的警告
#![allow(dead_code)]

#[derive(Debug)]
enum WebEvent {
    PageLoad,
    PageUnload,
    KeyPress(char),
    Paste(String),
    Click { x: i64, y: i64 },
}

fn inspect(event: WebEvent) {
    match event {
        WebEvent::PageLoad => println!("Page loaded"),
        WebEvent::PageUnload => println!("Page unloaded"),
        WebEvent::KeyPress(c) => println!("pressed '{}'", c),
        WebEvent::Paste(s) => println!("pasted \"{}\".", s),
        WebEvent::Click { x, y } => {
            println!("clicked at x={}, y={}.", x, y);
        },
    }
}

fn main() {
    let pressed = WebEvent::KeyPress('x');
    // `to_owned()` 从一个字符串切片中创建一个具有所有权的 `String`。
    // let pasted  = WebEvent::Paste("my text".to_owned());
    let pasted = WebEvent::Paste(String::from("my text"));
    let click   = WebEvent::Click { x: 20, y: 80 };
    let load    = WebEvent::PageLoad;
    let unload  = WebEvent::PageUnload;

    inspect(pressed);
    inspect(pasted);
    inspect(click);
    inspect(load);
    inspect(unload);

    test_01();
}

// 使用 use 关键字
#[derive(Debug)]
enum Color {
    Pink,
    Blue,
    Green,
    Red,
    Orange,
}

fn test_01() {
    use Color::*;

    let color = Pink;
    let color2 = Color::Green;

    match color {
        Pink => println!("粉色"),
        _ => println!("其它颜色"),
    }

    // irrefutable 不可辩驳
    // if let green = color2 {
    //     println!("绿色 {:?}", green);
    // }

    match color2 {
        Color::Red => println!("红色"),
        _ => println!("不是红色"),
    }
}

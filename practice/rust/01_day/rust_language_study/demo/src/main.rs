fn main() {
    test_01();
    test_02();
    test_03();
    test_04();
    test_05();
    test_06();
}

fn test_01() {
    let mut statck = Vec::new();

    statck.push(1);
    statck.push(2);
    statck.push(3);

    // pop方法返回Option<T>
    // while循环只要pop返回Some就会一直运行其块中的代码
    // 一旦其返回None,while循环停止
    while let Some(top) = statck.pop() {
        println!("{}", top);
    }
}

fn test_02() {
    let v = vec!['a', 'b', 'c'];

    // enumerate方法适配一个迭代器来产生一个值和其在迭代器中的索引
    for (index, value) in v.iter().enumerate() {
        println!("{} is at index {}", value, index);
    }

    // if let x = 1 {
    //     println!("{}", x);
    // }
}

fn test_03() {
    let x = Some(5);
    let y = 10;

    match x {
        Some(50) => println!("Got 50"),
        // y的值是x,而不是外部变量y的值10,因为y覆盖了外部y
        Some(y) => println!("Matched, y = {:?}", y),
        _ => println!("Default case, x = {:?}", x),
    }

    println!("at the end: x = {:?}, y = {:?}\n", x, y);

    let x = 8;
    match x {
        1 | 2 => println!("one or two"),
        3 => println!("three"),
        4..=10 => println!("4 through 10"),
        _ => println!("anthing"),
    }

    let x = 'c';

    match x {
        'a'..='j' => println!("early ASCII letter"),
        'k'..='z' => println!("late ASCII letter"),
        _ => println!("something else"),
    }
}

struct Point {
    x: i32,
    y: i32,
}

fn test_04() {
    let p = Point { x: 0, y: 7 };

    let Point { x: a, y: b } = p;
    assert_eq!(0, a);
    assert_eq!(b, 7);

    let p = Point { x: 0, y: 7 };

    // 第一个分支通过指定字段 y 匹配字面量 0 来匹配任何位于 x 轴上的点。
    // 此模式仍然创建了变量 x 以便在分支的代码中使用。
    // 类似的，第二个分支通过指定字段 x 匹配字面量 0 来匹配任何位于 y 轴上的点，
    // 并为字段 y 创建了变量 y。第三个分支没有指定任何字面量，
    // 所以其会匹配任何其他的 Point 并为 x 和 y 两个字段创建变量。
    // 在这个例子中，值 p 因为其 x 包含 0 而匹配第二个分支，
    // 因此会打印出 On the y axis at 7。
    match p {
        Point { x, y: 0 } => println!("On the x axis at {}", x),
        Point { x: 0, y } => println!("On the y axis at {}", y),
        Point { x, y } => println!("On neither axis: ({}, {})", x, y),
    }
}

enum Color {
    Rgb(i32, i32, i32),
    Hsv(i32, i32, i32),
}

enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(Color),
}

fn test_05() {
    let msg = Message::ChangeColor(Color::Hsv(0, 160, 255));

    match msg {
        Message::ChangeColor(Color::Rgb(r, g, b)) => {
            println!("Change the color to red {}, green {}, and blue {}", r, g, b)
        }
        Message::ChangeColor(Color::Hsv(h, s, v)) => {
            println!(
                "Change the color to hue {}, saturation {}, and value {}",
                h, s, v
            )
        }
        _ => (),
    }
}

fn test_06() {
    let nums = (2, 4, 6, 8, 10, 12);
    match nums {
        (first, .., last) => {
            println!("Some numbers: {}, {}", first, last);
        }
    }
}

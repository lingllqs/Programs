// 所有类型都能推导 fmt::Debug 的实现，但是 fmt::Display 需要手动实现

#[derive(Debug)]
struct Structure(i32);

#[derive(Debug)]
struct Deep(Structure);

#[derive(Debug)]
struct Person<'a> {
    name: &'a str,
    age: u8,
}

fn main() {
    // 使用{:?}打印和使用{}类似
    println!("{:?} months in a year", 12);
    println!(
        "{1:?} {0:?} is the {actor:?} name.",
        "Rust",
        "python",
        actor = "cpp's"
    );

    println!("Now {:?} will print!", Structure(5));

    // 使用 derive 的一个问题是不能控制输出的形式
    println!("Now {:?} will print!", Deep(Structure(2)));

    // 使用{:#?}来增加一些美感(个人感觉)
    // 可以通过手动实现 fmt::Display 来控制显示效果
    let name = "Peter";
    let age = 20;
    let peter = Person { name, age };

    println!("{:#?}", peter);
}

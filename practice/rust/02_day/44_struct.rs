mod my {
    // 公有结构体
    pub struct OpenBox<T> {
        // 公有字段
        pub contents: T,
    }

    #[allow(dead_code)]
    pub struct CloseBox<T> {
        // 私有字段
        contents: T,
    }

    impl<T> CloseBox<T> {
        // 公有构造器
        pub fn new(contents: T) -> CloseBox<T> {
            CloseBox { contents: contents }
        }
    }
}

fn main() -> () {
    let open_box = my::OpenBox {
        contents: "Public information",
    };
    println!("The open box contains: {}", open_box.contents);

    // 带有私有字段的公有结构体不能使用字段名来构造
    // let closed_box = my::CloseBox {
    //     contents: "classified information",
    // };

    let _closed_box = my::CloseBox::new("classified information");
    // 私有字段不能访问
    // println!("The closed box contains: {}", _closed_box.contents);
}

use std::ops::Deref;

fn main() {
    let x = 5;
    let y = &x;

    assert_eq!(5, x);
    assert_eq!(5, *y);
    // assert_eq!(5, y);

    let x = 5;
    // new方法返回Self
    let y = MyBox::new(x);

    assert_eq!(5, x);
    // 底层运行了*(y.deref())
    assert_eq!(5, *y);

    let m = MyBox::new(String::from("Rust"));
    hello(&m);
    hello(&(*m)[..]);

    let c = CustomSmartPointer { data: String::from("my stuff") };
    let d = CustomSmartPointer { data: String::from("other stuff") };
    drop(c);
    println!("CustomSmartPointers created.");
}

// 定义一个元组结构体
struct MyBox<T>(T);

impl<T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

impl<T> Deref for MyBox<T> {
    type Target = T;
     
    fn deref(&self) -> &T {
        &self.0
    }
}

fn hello(name: &str) {
    println!("Hello {}", name);
}

struct CustomSmartPointer {
    data: String,
}

impl Drop for CustomSmartPointer {
    fn drop(&mut self) {
        println!("Dropping CustomSmartPointer with data `{}`!", self.data);
    }
}


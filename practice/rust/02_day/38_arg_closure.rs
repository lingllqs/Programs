// 闭包作为返回值参数必须使用 move 关键字 因为函数。退出时任何通过引用的捕获都会被丢弃
fn create_fn() -> impl Fn() {
    let text = "Fn".to_owned();
    move || println!("This is a: {}", text)
}

fn create_fn_mut() -> impl FnMut() {
    let text = "FnMut".to_owned();
    move || println!("This is a: {}", text)
}

fn create_fn_once() -> impl FnOnce() {
    let text = "FnOnce".to_owned();
    move || println!("This is a: {}", text)
}

fn main() -> () {
    let fn_plain = create_fn();
    let mut fn_mut = create_fn_mut();
    let fn_once = create_fn_once();

    fn_plain();
    fn_mut();
    fn_once();
}

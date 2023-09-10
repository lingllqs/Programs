fn apply<F>(f: F)
where
    F: FnOnce(), // 移动，所有权改变
{
    f();
}

fn apply_to_3<F>(f: F) -> i32
where
    F: Fn(i32) -> i32,
{
    return f(3);
}

fn main() -> () {
    use std::mem;

    let greeting = "hello";
    // to owned 从借用的数据创建有所有权的数据
    let mut farewell = "goodbye".to_owned();

    let diary = || {
        println!("I said {}.", greeting);

        farewell.push_str("!!!");
        println!("Then I screamed {}.", farewell);
        println!("Now Ican sleep. zzzzz");

        mem::drop(farewell);
    };

    // 闭包作为参数
    apply(diary);

    // double 符合 apply_to_3 的trait.
    let double = |x| 2 * x;
    println!("3 doubled: {}", apply_to_3(double));
}

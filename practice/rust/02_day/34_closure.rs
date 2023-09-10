fn main() {
    // 不能对闭包类型解引用
    let closure_annotated = |i: i32| -> i32 { i + 1 };
    let closure_inferred = |i| i + 1;

    println!("{}", closure_inferred(3));
    println!("{}", closure_annotated(2));

    let no_arg = || 1;
    println!("no_arg: {}", no_arg());
}

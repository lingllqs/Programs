fn call_me<F: Fn()>(f: F) {
    f();
}

// 满足 Fn 约束的函数
fn function() {
    println!("I'm a function");
}

fn main() {
    // 满足 Fn 约束的闭包
    let closure = || println!("I'm a closure");

    call_me(function);
    call_me(closure);
}

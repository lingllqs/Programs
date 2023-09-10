fn test_01() {
    // Vec 在语义上是不可复制的
    let haystack = vec![1, 2, 3];

    let contains = move |needle| haystack.contains(needle);
    println!("{}", contains(&1));
    println!("{}", contains(&4));
}

fn main() {
    // use std::mem;
    //
    // let color = String::from("green");
    //
    // let print = || println!("`color`: {}", color);
    //
    // // 使用借用来调用闭包 `color`
    // print();
    //
    // let _reborrow = &color;
    // print();
    //
    // let _color_moved = color;
    //
    // // color 已经 move 不可使用
    // // println!("color: {}", color);
    //
    // let mut count = 0;
    // let mut inc = || {
    //     count += 1;
    //     println!("count: {}", count);
    // };
    // // let _reborrow = &count;
    // inc();
    //
    // let _count_reborrowed = &mut count;
    //
    // let movable = Box::new(3);
    // let consume = || {
    //     println!("movable: {:?}", movable);
    //     mem::drop(movable);
    // };
    //
    // consume();
    // // consume();

    test_01();
}

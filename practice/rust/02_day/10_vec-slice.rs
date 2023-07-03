// 切片 (slice) 大小在编译时是不确定的
// 切片是一个双字对象，第一个字是一个指向数据的指针
// 第二个字是切片的长度

use std::mem;

// 参数: 借用一个切片 (slice)
fn analyze_slice(slice: &[i32]) {
    println!("切片中第一个元素: {}", slice[0]);
    println!("该切片有 {} 个元素", slice.len());
}

fn main() {
    // 数组 xs 元素类型是 i32, 长度是5
    let xs: [i32; 5] = [1, 2, 3, 4, 5];

    // 数组 ys 元素类型是 i32, 长度是500, 全部元素初始化为 0
    let ys: [i32; 500] = [0; 500];

    println!("first elemtn of the array xs is {}", xs[0]);
    println!("second elemtn of the array xs is {}", xs[1]);
    println!("array's size: {}", xs.len());

    // 数组是在栈中分配的
    println!("array occupies {} bytes", mem::size_of_val(&xs));

    // 借用为 slice
    println!("borrow the whole array xs as a slice");
    analyze_slice(&xs);

    println!("borrow a section of the array as a slice");
    analyze_slice(&ys[1..4]);

    // 数组越界会引发 panic
    // println!("{}", xs[5]);
}

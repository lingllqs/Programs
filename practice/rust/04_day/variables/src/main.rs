#![allow(unused)]
fn main() {
    // declare a tuple
    let tup = ('z', 3, 3.14);

    println!("tup.0 = {} tup.1 = {} tup.2 = {}", tup.0, tup.1, tup.2);

    // destructure tuple
    let (x, y, z) = tup;
    println!("x = {x}, y = {y}, z = {z}");

    // length = 3, value = 9
    let a = [9; 3];
    println!("a = {:#?}", a);

    let a2: [u32; 3] = [3, 0, 3];
    println!("a2 = {:#?}", a2);

    let v = 6; // let statement don't return a value
    // let var = var2 = 6; // error

    let ret = {
        v + 1 // an expression do not endwith a ';'
    };

    let r = func(); // a function return an expression
}

fn func() -> i32 {
    5
}

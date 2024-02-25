fn main() {
    let v_1 = 3.14; // 不可变变量
    let v_2 = v_1 as i32;
    println!("{v_2}");
    println!("{v_1}");
    
    let x = 5;
    {
        let x = 10;
        println!("Inner x: {x}");
    }
    println!("Outer x: {x}");

    let mut x = "Rust"; // 可变变量
    println!("Mut x: {x}");

    x = "Python";
    println!("New x: {x}");
}

fn main(){
    // reference 是 & 类型
    let reference = &4;
    println!("{}", reference);
    println!("{}", *reference);

    match reference {
        &val => println!("Got a value via destructuring: {:?}", val),
    }

    match reference {
        val => println!("Got a value via destructuring: {:?}", *val),
    }

    match *reference {
        val => println!("Got a value via destructuring: {:?}", val),
    }

    let value = 5;
    match value {
        // r 是 &i32 类型，和 i32 类型一样可以直接打印
        ref r => println!("r = {:?}", *r),
    }

    let mut mut_value = 6;
    match mut_value {
        ref mut r => {
            // r 是 mut_value 的可变引用
            *r += 10;
            println!("r = {:?}", r);
        }
    }
}

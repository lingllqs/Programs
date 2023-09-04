#![allow(unreachable_code)]

fn test() {
    'outer: loop {
        println!("Entered the outer loop");
        'inner: loop {
            println!("Entered the inner loop");

            // break;
            break 'outer;
        }
        println!("This point will never be reached");
    }

    println!("Exited the outer loop");
}

fn main() {
    let mut count = 0u32;

    let result = loop {
        count += 1;
        if count == 3 {
            println!("three");
            continue;
        }

        println!("{}", count);

        if count == 5 {
            println!("OK, that's enough");
            break count * 2; // 退出并返回 count * 2
        }
    };
    println!("resut = {}", result);
    test();
}

fn is_odd(n: u32) -> bool {
    n % 2 == 1
}

fn main() -> () {
    println!("Find the sum of all the squared odd numbers under 1000");
    let upper = 1000;

    let mut acc = 0;

    // 0 到正无穷
    for n in 0.. {
        // n 平方
        let n_squared = n * n;

        if n_squared >= upper {
            break;
        } else if is_odd(n_squared) {
            // 平方是奇数
            acc += n_squared;
        }
    }
    println!("imperative style: {}", acc);

    // 函数式写法
    let sum_of_squared_odd_numbers: u32 = (0..)
        .map(|n| n * n) // 所有自然数平方和
        .take_while(|&n| n < upper) // 取值小于upper
        .filter(|&n| is_odd(n)) // 取奇数
        .fold(0, |sum, i| sum + i); // 求和
    println!("Function style: {}", sum_of_squared_odd_numbers);
}

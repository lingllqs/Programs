// 发散函数不会返回，使用感叹号(!)标记，这是一个空类型

#![feature(never_type)]
fn main() {
    fn sum_odd_numbers(up_to: u32) -> u32 {
        let mut acc = 0;
        for i in 0..up_to {
            // 求奇数和
            let addition: u32 = match i % 2 == 1 {
                true => i,
                false => continue,
            };
            acc += addition;
        }
        // 返回 acc
        acc
    }
    println!(
        "Sum of odd numbers up to 9 (excluding): {}",
        sum_odd_numbers(9)
    );

    test_01();
}

fn test_01() {
    let x: ! = panic!("This call never returns.");
    println!("You will never see this line!");
}

use rand::Rng;          // Rng是一个trait
use std::cmp::Ordering; // Ordering是一个枚举(成员是Less, Greater, Equal)
use std::io;            // io模块不在预导入模块(prelude)中

fn main() {
    // 游戏标题
    println!("Guess the number!");

    // 定义变量保存要猜的数字
    let secret_number = rand::thread_rng().gen_range(1..101);

    // 循环
    loop {
        // 提示输入用户的猜测
        println!("Please input your guess.");

        // 定义一个可变(mutable)变量来接收用户输入
        // String是标准库提供的字符串类型，是一个UTF-8编码的可增长文本
        // new是String类型的一个关联函数
        let mut guess = String::new();

        // 如果没有使用use std::io引入io库，可以通过std::io::stdin来调用函数
        // stdin函数返回一个std::io::Stdin的实例类型(代表终端标准输入的文件描述符)
        // 以下三行可以写在一行上 io::stdin().read_line(&mut guess).expect("Failed to read line");
        // read_line函数返回一个值--io::Result，这是一个枚举类型
        // Result的成员是Ok和Err，分别表示成功和失败
        // Ok->expect会将Ok的值原样返回，Err->expect会导致程序崩溃
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");

        // trim去除前后的空格，parse将字符串解析成数字
        // _是一个通配符，忽略错误输入继续猜测
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        // {}为占位符，后面用guess填充
        println!("You guessed: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small"),
            Ordering::Greater => println!("Too big"),
            Ordering::Equal => {
                println!("The secret number is: {}", secret_number);
                println!("You win!");
                break;
            }
        }
    }
}

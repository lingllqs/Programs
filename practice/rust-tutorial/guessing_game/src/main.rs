use std::{cmp::Ordering, io};

use rand::Rng;

fn main() {
    println!("Guessing Game!!!");

    let secret_number = rand::thread_rng().gen_range(1..101);

    loop {
        println!("Please input your guess:");

        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Please Type a number");
                continue;
            }
        };

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too Small"),
            Ordering::Greater => println!("Too Big"),
            Ordering::Equal => {
                println!("You Win!!!");
                break;
            }
        }
    }

    println!("Thanks");
}

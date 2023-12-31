#![allow(unused)]

use rand::Rng;
use rand::{distributions::Uniform, thread_rng};
use rand_distr::{Distribution, Normal, NormalError};

fn main() {}

fn test_03() -> Result<(), NormalError> {
    let mut rng = thread_rng();
    let normal = Normal::new(2.0, 3.0)?;
    let v = normal.sample(&mut rng);
    println!("{} is from a N(2,9) distribution", v);
    Ok(())
}

fn test_02() {
    let mut rng = rand::thread_rng();
    let die = Uniform::from(1..7);
    loop {
        let throw = die.sample(&mut rng);
        println!("Roll the die: {}", throw);
        if throw == 6 {
            break;
        }
    }
}

fn test_01() {
    let mut rng = rand::thread_rng();

    let n1: u8 = rng.gen();
    let n2: u16 = rng.gen();

    println!("random u8: {}", n1);
    println!("random u16: {}", n2);
    println!("random u32: {}", rng.gen::<u32>());
    println!("random i32: {}", rng.gen::<i32>());
    println!("random float: {}", rng.gen::<f64>());
    println!("random integer: {}", rng.gen_range(0..10));
    println!("random float: {}", rng.gen_range(0.0..10.0));
}

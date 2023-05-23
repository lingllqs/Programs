use std::collections::HashMap;

fn main() {
    // let s1 = String::from("hello, ");
    // let s2 = String::from("world");
    // let s3 = s1 + &s2;

    // println!("{}", s1); // s1 拥有权转移
    // println!("{}", s2);
    // println!("{}", s3);
    
    // let s4 = format!("{}{}", s1, s2);
    // println!("{}", s4);

    // for s in s1.chars() {
    //     println!("{}", s);
    // }

    // for s in s2.bytes() {
    //     println!("{}", s);
    // }

    let teams = vec![String::from("red"), String::from("green")];
    let intial_scores = vec![10, 50];

    let scores: HashMap<_, _> = 
        teams.iter().zip(intial_scores.iter()).collect();

    for (k, v) in &scores {
        println!("{}: {}", k, v);
    }

    let mut kv = HashMap::new();
    kv.insert(String::from("cpp"), 10);
    kv.insert(String::from("java"), 20);

    let kn = String::from("c");
    let v = kv.get(&kn);

    match v {
        Some(s) => println!("{}", s),
        None => println!("not fount"),
    };
}

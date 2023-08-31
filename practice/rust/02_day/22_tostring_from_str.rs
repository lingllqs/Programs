use std::fmt;

struct Circle {
    radius: i32,
}

// 实现了 fmt::Display trait 后会自动提供 ToString trait
impl fmt::Display for Circle {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Circle of radius {}", self.radius)
    }
}

// 手动实现 ToString trait
// impl ToString for Circle {
//     fn to_string(&self) -> String {
//         format!("Circle of radius(to_string) {:?}", self.radius)
//     }
// }

fn main() {
    let circle = Circle { radius: 5 };
    println!("{}", circle.to_string());

    let parsed: i32 = "5".parse().unwrap();
    let turbo_parsed = "10".parse::<i32>().unwrap();

    let sum = parsed + turbo_parsed;
    println!("Sum = {:?}", sum);
}

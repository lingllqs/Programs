#[derive(Debug)]
struct User {
    email: String,
    name: String,
}

fn main() {
    let user1 = User {
        email: String::from("example@gmail.com"),
        name: String::from("Rust"),
    };

    println!("{:?}", user1);

    let user2 = User {
        email: String::from("example@qq.com"),
        ..user1
    };

    println!("{:?}", user2);
}

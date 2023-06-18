// Rust不允许结构体某个字段标记为可变
struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

// 元组结构体
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

fn main() {
    let user1 = User {
        active: true,
        username: String::from("Rust"),
        email: String::from("Python"),
        sign_in_count: 1,
    };

    // user1.username已经move
    // active和sign_in_count的类型实现了Copy Trait
    let user2 = User {
        active: user1.active,
        username: user1.username,
        email: String::from("C"),
        sign_in_count: user1.sign_in_count,
    };

    // 使用结构体更新语法，..语法指定剩余未显式设置值的字段应有与给定实例对应字段相同的值
    let user3 = User {
        email: String::from("Cpp"),
        ..user2
    };

    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);
}

fn build_user(username: String, email: String) -> User {
    User {
        // username: username,
        // email: email,
        // 参数名和字段名相同可以简写
        username,
        email,
        active: true,
        sign_in_count: 1,
    }
}

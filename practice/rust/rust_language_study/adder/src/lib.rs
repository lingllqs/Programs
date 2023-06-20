#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

pub fn add(left: usize, right: usize) -> usize {
    left + right
}

// #[cfg(test)]告诉Rust只在cargo test时才编译和运行测试代码
#[cfg(test)]
mod tests {
    // tests是一个普通模块，要在内部模块中测试外部模块的代码需要引入
    // 使用glob全局导入
    use super::*;

    // #[test] 表明这是一个测试函数
    #[test]
    fn it_works() {
        let result = add(2, 2);
        // 断言result结果为4
        assert_eq!(result, 4);
    }

    #[test]
    fn it_works2() -> Result<(), String> {
        if 2 * 2 == 5 {
            Ok(())
        }
        else {
            Err(String::from("this is a test string"))
        }
    }

    #[test]
    fn another_test() {
        let result = add(2, 3);
        assert_eq!(result, 4);
    }

    #[test]
    fn larger_can_hold_smaller() {
        let larger = Rectangle {
            width: 8,
            height: 7,
        };
        let smaller = Rectangle {
            width: 5,
            height: 2,
        };

        assert!(larger.can_hold(&smaller));
    }

    #[test]
    #[ignore]
    fn smaller_cannot_hold_larger() {
        let larger = Rectangle {
            width: 8,
            height: 7,
        };
        let smaller = Rectangle {
            width: 5,
            height: 2,
        };

        assert!(smaller.can_hold(&larger), "nihao");
    }
}

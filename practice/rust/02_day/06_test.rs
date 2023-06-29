use std::fmt;

struct List(Vec<i32>);

impl fmt::Display for List {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // 获取 List 的第一个元素的引用
        let vec = &self.0;

        // 先输出一个 [
        write!(f, "[")?;

        // 遍历所有元素
        for (count, v) in vec.iter().enumerate() {
            // 下标不为 0 则先输出一个逗号
            if count != 0 {
                write!(f, ", ")?;
            }
            // 输出元素的下标和值
            write!(f, "{}: {}", count, v)?;
        }

        // 输出一个 ]
        write!(f, "]")
    }
}

fn main() {
    let v = List(vec![1, 2, 3]);
    println!("{}", v);
}

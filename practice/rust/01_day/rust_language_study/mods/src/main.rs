mod module_a {
    pub fn some_function() {
        println!("hello mod!");
    }
}

mod module_b {
    // 重新导出模块a的函数
    pub use crate::module_a::some_function;
}

fn main() {
    // 直接使用模块b中重新导出的函数
    module_b::some_function();
    // 等价于使用模块a中的函数
    module_a::some_function();
}

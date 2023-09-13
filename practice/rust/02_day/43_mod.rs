// 定义一个名为 my_mod 的模块
mod my_mod {
    // 模块中的项默认为私有的，可见性只限于模块内
    fn private_function() {
        println!("called my_mod::private_function()");
    }

    // 使用 pub 修饰语法可以改变默认的可见性
    pub fn function() {
        println!("called my_mod::function()");
    }

    // 在同一模块中，项可以访问其他项，即使它是私有的
    pub fn indirect_access() {
        print!("called my_mod::indirect_access(), that\n");
        private_function();
    }

    // 模块也可以嵌套
    pub mod nested {
        pub fn function() {
            println!("called my_mod::nested::function()");
        }

        #[allow(dead_code)]
        fn private_function() {
            println!("called my_mod::nested::private_function()");
        }
    }
}

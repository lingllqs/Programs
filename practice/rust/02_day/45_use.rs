mod deeply {
    pub mod nested {
        pub fn function() {
            println!("call deeply::nested::function()");
        }
    }
}

fn function() {
    println!("called function()");
}

// use 关键字引入项到当前作用域
// as 将 deeply::nested::function 绑定到 other_function
use deeply::nested::function as other_function;

fn main() -> () {
    other_function();

    println!("Entering block");
    {
        // 遮蔽外部同名函数
        use deeply::nested::function;
        function();
    }

    println!("Leaving block");

    function();
}

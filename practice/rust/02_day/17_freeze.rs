fn main() {
    let mut _mutable_integer = 7i32;

    {
        let _mutable_integer = _mutable_integer; // 屏蔽了外部 _mutable_integer
    }

    _mutable_integer = 3; // 在此作用域 _mutable_integer 没有被冻结
}

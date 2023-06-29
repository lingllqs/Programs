use adder;

// tests目录的子目录不会被作为单独的crate编译或作为一个测试结果部分出现在测试输出中
#[test]
fn it_adds_two() {
    assert_eq!(4, adder::add(2, 2));
}

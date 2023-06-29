use std::vec;

fn main() {
    let v1 = vec![1, 2, 3];

    // v1_iter需要是可变的
    // let mut v1_iter = v1.iter();
    let v1_iter = v1.iter();

    // for循环中无需使v1_iter可变因为for循环会获取v1_iter的所有权并在后台使v1_iter可变
    for item in v1_iter {
        println!("{}", item);
    }

    // assert_eq!(v1_iter.next(), Some(&1));
    // assert_eq!(v1_iter.next(), Some(&2));
    // assert_eq!(v1_iter.next(), Some(&3));
    //
    // assert_eq!(v1_iter.next(), None);

    test();
}

fn test() {
    let v1: Vec<i32> = vec![1, 2, 3];

    // collect方法消费迭代器并创建一个vector
    let v2: Vec<_> = v1.iter().map(|x| x + 1).collect();

    assert_eq!(v2, vec![2, 3, 4]);
}

use std::rc::Rc;
use std::sync::Arc;
use std::sync::Mutex;
use std::thread;

fn main() {
    test02();
}

fn test02() {
    // Rc<T>并没有使用任何并发原语来确保改变计数操作不会被其他线程打断
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 1..=10 {
        // Mutex<T>提供了内部可变性
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();

            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());
}

fn test01() {
    let m = Mutex::new(5);

    {
        // 使用lock方法获取锁
        // 这个方法会阻塞当前线程
        let mut num = m.lock().unwrap();
        *num = 6;
        // 锁的释放是自动发生的
    }

    println!("m = {:?}", m);
}

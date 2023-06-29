use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    test();

    test_01();
}

fn test_01() {
    let (tx, rx) = mpsc::channel();

    let tx1 = tx.clone();
    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];

        for val in vals {
            tx1.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    thread::spawn(move || {
        let vals = vec![
            String::from("more"),
            String::from("messages"),
            String::from("for"),
            String::from("you"),
        ];

        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    for received in rx {
        println!("Got: {}", received);
    }
}

fn test() {
    // 子线程
    // thread::spawn返回值是JoinHandle
    let handle = thread::spawn(|| {
        for i in 1..10 {
            println!("hi number {} from the spawned thread!", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    // 主线程
    for i in 1..5 {
        println!("hi number {} from the main thread!", i);
        thread::sleep(Duration::from_millis(1));
    }

    // join函数阻塞等待关联线程结束
    // 返回值为Result<T>
    handle.join().unwrap();

    let v = vec![1, 2, 3];

    // move关键字使v的值的所有权移动到线程中
    let hl = thread::spawn(move || {
        println!("Here's a vector: {:?}", v);
    });

    hl.join().unwrap();
}

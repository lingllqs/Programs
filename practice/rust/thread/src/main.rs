use std::thread;
use std::sync::mpsc;
use std::time::Duration;


fn main() {
    test03();
}

fn test01() {
    let handle = thread::spawn( || {
        for i in 1..10 {
            println!("number {} from the spawned thread!", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..5 {
        println!("number {} from the main thread!", i);
        thread::sleep(Duration::from_millis(1));
    }

    handle.join().unwrap();
}

fn test02() {
    let v = vec![1, 2, 3];
    let handle = thread::spawn(move || {
        println!("Here is a vector {:?}", v);
    });

    handle.join().unwrap();
}

fn test03() {
    let (tx, rx) = mpsc::channel();
    thread::spawn(move || {
        let msg = String::from("hello");
        tx.send(msg).unwrap();
    });

    let received = rx.recv().unwrap();
    println!("Got msg: {}", received);
}

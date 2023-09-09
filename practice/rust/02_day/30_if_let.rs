fn test() {
    let number = Some(7);
    let letter: Option<i32> = None;
    let emoticon: Option<i32> = None;

    // 如果 number 是 Some(i)
    if let Some(i) = number {
        println!("Matched {:?}!", i);
    }

    if let Some(i) = letter {
        println!("Matched {:?}", i);
    } else {
        println!("Didn't match a number, let's go with a letter");
    }
}

enum Foo {
    Bar,
    Baz,
    Qux(u32),
}

fn test_01() {
    let a = Foo::Bar;
    let b = Foo::Baz;
    let c = Foo::Qux(100);

    if let Foo::Bar = a {
        println!("a is foobar");
    }

    if let Foo::Bar = b {
        println!("b is foobar");
    }

    if let Foo::Qux(100) = c {
        println!("c is {}", 100);
    }

    if let Foo::Qux(value) = c {
        println!("c is {}", value);
    }
}

fn main() {
    #[derive(PartialEq)]
    enum Bar {
        Foo,
    }

    let a = Bar::Foo;

    if Bar::Foo == a {
        println!("a is barfoo");
    }
    // test_01();
}

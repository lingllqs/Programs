fn main() {
    let mut x = vec!["hello", "world"];
    {
        let y = &x[0];     // y等于x第一个元素的引用
        println!("{}", y); // 打印y到标准输出中
    }

    let z = x[0].clone();

    x.push("foo");
    println!("{}", z);

    println!("x has {} elements", x.len());

    struct Point {
        x: i32,
        y: i32,
    }

    let mut point = Point { x: 0, y: 0 };
    point.x = 5;
    println!("The point is at ({}, {})", point.x, point.y);
    
    // test();
    let mut num = 2;
    test_02(&mut num);
    println!("num = {}", num);
}

fn test() {
    struct Circle {
        x: f64,
        y: f64,
        radius: f64,
    }

    impl Circle {
        fn area(&self) -> f64 {
            std::f64::consts::PI * (self.radius * self.radius)
        }

        fn grow(&self, increment: f64) -> Circle {
            Circle { x: self.x, y: self.y, radius: self.radius + increment }
        }
    }


    let c = Circle { x: 0.0, y: 0.0, radius: 2.0 };
    println!("{}", c.area());

    let d = c.grow(2.0).area();
    println!("{}", d);
}

fn test_02(num: &mut i32) {
    *num = *num * 2;
    println!("num = {}", num);
}

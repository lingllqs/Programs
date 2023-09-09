struct Point {
    x: f64,
    y: f64,
}

impl Point {
    // 静态方法
    // 静态方法不需要被实例调用
    // 一般用作构造器 (constructor)
    fn origin() -> Point {
        Point { x: 0.0, y: 0.0 }
    }

    fn new(x: f64, y: f64) -> Point {
        Point { x: x, y: y }
    }
}

struct Rectangle {
    p1: Point,
    p2: Point,
}

impl Rectangle {
    // &self 是 self: &Self 的语法糖， 这个例子中 Self = Rectangle
    // 面积
    fn area(&self) -> f64 {
        let Point { x: x1, y: y1 } = self.p1;
        let Point { x: x2, y: y2 } = self.p2;

        // abs 是一个 f64 类型的方法，返回调用者的绝对值
        ((x1 - x2) * (y1 - y2)).abs()
    }

    // 周长
    fn perimeter(self: &Self) -> f64 {
        let Point { x: x1, y: y1 } = self.p1;
        let Point { x: x2, y: y2 } = self.p2;

        2.0 * ((x1 - x2).abs() + (y1 - y2).abs())
    }

    fn translate(&mut self, x: f64, y: f64) {
        self.p1.x += x;
        self.p2.x += x;

        self.p1.y += y;
        self.p2.y += y;
    }
}

struct Pair(Box<i32>, Box<i32>);

impl Pair {
    // 这个方法会‘消耗’调用者的资源
    fn destroy(self: Self) {
        // 解构 self
        let Pair(first, second) = self;

        println!("Destroying Pari({}, {})", first, second);
    }
}

fn main() -> () {
    let rectangle = Rectangle {
        p1: Point::origin(),      // 默认值
        p2: Point::new(3.0, 4.0), // 自定义值
    };

    println!("Rectangle perimeter: {}", rectangle.perimeter());
    println!("Rectangle area: {}", rectangle.area());

    let mut square = Rectangle {
        p1: Point::origin(),
        p2: Point::new(1.0, 1.0),
    };

    square.translate(2.0, 2.0);

    let pair = Pair(Box::new(1), Box::new(2));
    pair.destroy();
}

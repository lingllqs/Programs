#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    //fn area(&self) -> u32 {
    //    self.width * self.height
    //}
    fn area(self: &Self) -> u32 {
        self.width * self.height
    }

    fn area2(&self, rect: &Rectangle) -> u32 {
        rect.width * rect.height
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

fn main() {
    let rect1 = Rectangle {
        width: 20,
        height: 30,
    };

    println!("{:?}", area(&rect1));
    dbg!(&rect1);
    println!("rect1 is {:#?}", rect1);

    let rect2 = Rectangle {
        width: 90,
        height: dbg!(20 * 3),
    };

    dbg!(&rect2);

    println!("The area of rect1 is {} square pixels.", rect1.area());
    println!("The area of rect1 is {} square pixels.", rect1.area2(&rect1));
    println!("The area of rect1 is {} square pixels.", Rectangle::area2(&rect1, &rect2));

    println!("The rect2 can hold rect1? {}", rect2.can_hold(&rect1));
    println!("The rect1 can hold rect2? {}", rect1.can_hold(&rect2));
}

fn area(rectangle: &Rectangle) -> u32 {
    return rectangle.width * rectangle.height;
}

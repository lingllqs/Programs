pub trait Summary {
    // 默认实现
    fn summarize(&self) -> String {
        String::from("default impl")
    }
}

pub struct NewsArticle {
    pub headline: String,
    pub location: String,
    pub author: String,
    pub content: String,
}

// 为NewsArticle实现Summary这个trait
// impl后面是需要实现trait的名称
impl Summary for NewsArticle {
    fn summarize(&self) -> String {
        format!("{}, by {} ({})", self.headline, self.author, self.location)
    }
}

pub struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}

pub struct Def {}
impl Summary for Def {}

fn main() {
    let tweet = Tweet {
        username: String::from("Rust"),
        content: String::from("Python"),
        reply: false,
        retweet: false,
    };

    println!("1 new tweet: {}", tweet.summarize());

    let def = Def {};
    println!("default trait: {}", def.summarize());

    let number_list = vec![34, 50, 25, 100, 65];

    let result = largest(&number_list);
    println!("The largest number is {}", result);

    let char_list = vec!['y', 'm', 'a', 'q'];

    let result = largest(&char_list);
    println!("The largest char is {}", result);
}

// trait 作为参数
// item 可以是任何实现了 Summary 这个 trait 的类型
pub fn notify(item: impl Summary) {
    println!("Breaking news {}", item.summarize());
}

// trait bound 写法
pub fn notify1<T: Summary + std::fmt::Display>(item: T) {
    println!("{}", item.summarize());
}

// where 语法
fn some_function<T, U>(t: T, u: U) -> impl Summary
where
    T: std::fmt::Display + Clone,
    U: Clone + std::fmt::Debug,
{
    Tweet {
        username: "Rust".to_string(),
        content: "Python".to_string(),
        reply: true,
        retweet: false,
    }
}

fn largest<T>(list: &[T]) -> T
where
    T: PartialOrd + Copy,
{
    let mut largest = list[0];

    for &item in list.iter() {
        if item > largest {
            largest = item;
        }
    }

    largest
}

struct Pair<T> {
    x: T,
    y: T,
}

impl<T> Pair<T> {
    fn new(x: T, y: T) -> Self {
        Self { x, y }
    }
}

impl<T> Pair<T>
where
    T: std::fmt::Display + PartialOrd,
{
    fn cmp_display(&self) {
        if self.x >= self.y {
            println!("The largest member is x = {}", self.x);
        } else {
            println!("The largest member is y = {}", self.y);
        }
    }
}

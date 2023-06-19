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

    let def = Def{};
    println!("default trait: {}", def.summarize());
}

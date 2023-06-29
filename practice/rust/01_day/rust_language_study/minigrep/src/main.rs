use std::env;
use std::process;

use minigrep::Config;

fn main() {
    // collect 可以被用来创建很多类型的集合，所以需要显式注明args的类型
    let args: Vec<String> = env::args().collect();

    // 解析命令行参数
    let config = Config::new(env::args()).unwrap_or_else(|err| {
        eprintln!("Problem parsing arguments: {}", err);
        process::exit(3);
    });

    // println!("Searching for {}", config.query);
    // println!("In file {}", config.filename);

    if let Err(e) = minigrep::run(config) {
        eprintln!("Application error: {}", e);
        process::exit(1);
    }
}

// fn parse_config(args: &[String]) -> Config {
//     // 匹配项
//     let query = args[1].clone();
//     // 文件名
//     let filename = args[2].clone();
//
//     Config { query, filename }
// }

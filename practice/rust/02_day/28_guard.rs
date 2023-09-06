fn main() {
    let pair = (2, -2);

    println!("pair: {:?}", pair);
    match pair {
        (x, y) if x == y => println!("twins"),
        (x, y) if x + y == 0 => println!("Antimatter, kaboom"),
        (x, _) if x % 2 == 1 => println!("The first one is odd"),
        _ => println!("No correlation..."),
    }
}

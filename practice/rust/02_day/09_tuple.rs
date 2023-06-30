fn reverse(pair: (i32, bool)) -> (bool, i32) {
    let (integer, boolean) = pair;
    (boolean, integer)
}

fn main() {
    let t = (1, 2, 3);
    println!("{:?}", t);

    let pair = (1, true);
    println!("{:?}", pair);
    println!("{:?}", reverse(pair));
}

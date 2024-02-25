static STATIC_VAL: i32 = 55; // static 需要指定类型
static mut STATIC_MUT_VAL: i32 = 66;

fn main() {
    const SECOND_HOUR: usize = 3600; // const 需要指定类型
    const SECOND_DAY:usize = SECOND_HOUR * 24;

    println!("SECOND_HOUR: {SECOND_HOUR}");
    println!("SECOND_DAY: {SECOND_DAY}");

    // STATIC_VAL = 200;
    println!("STATIC_VAL: {STATIC_VAL}");
    unsafe {
        STATIC_MUT_VAL = 99;
        println!("STATIC_MUT_VAL: {STATIC_MUT_VAL}");
    }
}

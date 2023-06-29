use std::fs::File;
use std::io::Read;

use ueberzug::prelude::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    if let Some(image_path) = std::env::args().nth(1) {
        let mut f = File::open(&image_path)?;
        let mut image_data = Vec::new();
        f.read_to_end(&mut image_data)?;

        // 创建终端屏幕
        let context = Context::create()?;
        let mut screen = Screen::create(&context)?;

        // 创建图像层
        let mut layer = ImageLayer::new(&context);
        layer.set_image(&image_data)?;
        layer.set_path(&image_path)?;

        // 在终端上显示图像层
        screen.place(&layer)?;
        screen.refresh()?;

        // 等待用户输入退出
        let mut stdin = std::io::stdin();
        let mut buf = [0; 1];
        stdin.read_exact(&mut buf)?;

        Ok(())
    } else {
        println!("Usage: preview <image>");
        Ok(())
    }
}


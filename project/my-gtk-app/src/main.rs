use gtk::prelude::*;
use gtk::{Button, glib, Application, ApplicationWindow};

const APP_ID: &str = "demo";

fn main() -> glib::ExitCode {
    // 创建一个新的应用程序
    let app = Application::builder().application_id(APP_ID).build();

    // 关联一个信号函数
    app.connect_activate(build_ui);

    app.run()
}

fn build_ui(app: &Application) {
    // 创建一个按钮
    // 设置按钮离边缘的距离
    let button = Button::builder()
        .label("Press me!")
        .margin_top(12)
        .margin_bottom(12)
        .margin_start(12)
        .margin_end(12)
        .build();

    // 给按钮关联一个点击后执行的函数
    button.connect_clicked(|button| {
        // 设置按钮标题
        button.set_label("Hello World!");
    });

    // 创建窗口
    // 把窗口指定为app中的窗口
    // 设置标题
    // 子窗口(组件)设置为button
    let window = ApplicationWindow::builder()
        .application(app)
        .title("Title")
        .child(&button)
        .build();

    // 显示窗口
    window.present();
}

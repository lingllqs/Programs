use glib::clone;
use gtk::prelude::*;
use gtk::{glib, Application, ApplicationWindow, Button};
use std::cell::Cell;
use std::rc::Rc;

const APP_ID: &str = "demo";

fn main() -> glib::ExitCode {
    // 创建一个新的应用程序
    let app = Application::builder().application_id(APP_ID).build();

    // 关联一个信号函数
    // app启动后执行
    app.connect_activate(build_ui);

    app.run()
}

fn build_ui(app: &Application) {
    // 创建一个按钮
    // 设置按钮离边缘的距离
    let button_increase = Button::builder()
        .label("Increase")
        .margin_top(12)
        .margin_bottom(12)
        .margin_start(12)
        .margin_end(12)
        .build();

    let button_decrease = Button::builder()
        .label("Decrease")
        .margin_top(12)
        .margin_bottom(12)
        .margin_start(12)
        .margin_end(12)
        .build();

    let number = Rc::new(Cell::new(0));

    // 给按钮关联一个点击后执行的闭包
    button_increase.connect_clicked(clone!(@weak number, @weak button_decrease => move |_| {
        number.set(number.get() + 1);
        button_decrease.set_label(&number.get().to_string());
    }));
    button_decrease.connect_clicked(clone!(@weak button_increase => move |_| {
        number.set(number.get() - 1);
        button_increase.set_label(&number.get().to_string());
    }));

    let gtk_box = gtk::Box::builder()
        .orientation(gtk::Orientation::Vertical)
        .build();
    gtk_box.append(&button_increase);
    gtk_box.append(&button_decrease);

    // 创建窗口
    // 把窗口指定为app中的窗口
    // 设置标题
    // 子窗口(组件)设置为gtk_box
    let window = ApplicationWindow::builder()
        .application(app)
        .title("GTK App")
        .child(&gtk_box)
        .build();

    // 显示窗口
    window.present();
}

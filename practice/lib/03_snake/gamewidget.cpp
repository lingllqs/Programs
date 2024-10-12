#include "gamewidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), timer(new QTimer(this)) {
    timer->setInterval(100); // 设置定时器时间间隔为 100 微秒
    connect(timer, &QTimer::timeout, this, &GameWidget::updateGame); // 超时更新游戏
    timer->start(); // 启动定时器
    placeFood(); // 放置初始食物
}

void GameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // 绘制蛇身
    for (const QPoint &point : snake.body()) {
        painter.drawRect(point.x() * 10, point.y() * 10, 10, 10);
    }

    // 绘制食物
    painter.drawRect(food.x() * 10, food.y() * 10, 10, 10);
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            snake.setDirection(Snake::LEFT);
            break;
        case Qt::Key_Right:
            snake.setDirection(Snake::RIGHT);
            break;
        case Qt::Key_Up:
            snake.setDirection(Snake::UP);
            break;
        case Qt::Key_Down:
            snake.setDirection(Snake::DOWN);
            break;
    }
}

void GameWidget::placeFood() {
    int maxX = width() / 10 - 1; // 界面宽度 / 10 - 1，蛇的身体每格宽度为 10，下标从 0 开始
    int maxY = height() / 10 - 1;

    if (maxX <= 0 || maxY <= 0) return; // 食物不能放在界外

    while (true) {
        int rx = QRandomGenerator::global()->bounded(maxX); // 随机生成食物坐标
        int ry = QRandomGenerator::global()->bounded(maxY);

        if (!snake.contains(QPoint(rx, ry))) { // 食物坐标不能在蛇身体位置
            food = QPoint(rx, ry);
            break;
        }
    }
}

void GameWidget::updateGame() {
    snake.move(); // 蛇移动

    if (snake.head() == food) { // 吃食物
        snake.grow();
        placeFood();
    }

    if (snake.checkCollision(width() / 10, height() / 10)) { // 游戏结束
        timer->stop();
        return;
    }

    update(); // 触发重绘事件
}

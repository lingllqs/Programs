#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QTimer>
#include "snake.h"

class GameWidget : public QWidget {
    Q_OBJECT

  public:
    explicit GameWidget(QWidget *parent = nullptr);

  protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

  private:
    QTimer *timer;
    Snake snake;
    QPoint food;

    void placeFood(); // 放置食物

  private slots:
    void updateGame(); // 更新游戏
};

#endif // GAMEWIDGET_H

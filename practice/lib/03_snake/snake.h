#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPoint>

class Snake {
public:
    enum Direction { LEFT, RIGHT, UP, DOWN };

    Snake();

    void setDirection(Direction dir); // 设置蛇的方向
    void move(); // 移动蛇
    void grow(); // 蛇成长
    bool checkCollision(int maxX, int maxY) const; // 碰撞检查
    bool contains(const QPoint &point) const; // 判断是否包含某个点
    const QPoint& head() const; // 获取蛇头
    const QList<QPoint>& body() const; // 获取蛇身体

private:
    QList<QPoint> m_body;
    Direction m_direction;
};

#endif // SNAKE_H

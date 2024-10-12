#include "snake.h"

Snake::Snake() : m_direction(RIGHT) { // 蛇方向初始为 RIGHT
    m_body.append(QPoint(0, 0));
    grow();
}

void Snake::setDirection(Direction dir) {
    // 不允许180度方向变换
    if((m_direction == LEFT && dir == RIGHT) || (m_direction == RIGHT && dir == LEFT)
        || (m_direction == UP && dir == DOWN) || (m_direction == DOWN && dir == UP)) return;

    m_direction = dir;
}

void Snake::move() {
    QPoint moveOffset(0, 0);

    switch (m_direction) { // 往下和往右为正
        case LEFT:
            moveOffset.setX(-1);
            break;
        case RIGHT:
            moveOffset.setX(1);
            break;
        case UP:
            moveOffset.setY(-1);
            break;
        case DOWN:
            moveOffset.setY(1);
            break;
    }

    for (int i = m_body.size() - 1; i > 0; --i) {
        m_body[i] = m_body[i - 1]; // 蛇身体的每个点的坐标等于前一个点的坐标
    }

    m_body[0] += moveOffset;
}

void Snake::grow() {
    QPoint tail = m_body.isEmpty() ? QPoint(0, 0) : m_body.last();
    m_body.append(tail);
}

bool Snake::checkCollision(int maxX, int maxY) const {
    const QPoint &headPos = head();
    if (headPos.x() < 0 || headPos.x() >= maxX || headPos.y() < 0 || headPos.y() >= maxY) { // 蛇撞墙
        return true;
    }

    auto bodyIt = m_body.cbegin();
    ++bodyIt; // 跳过蛇头
    while (bodyIt != m_body.cend()) { // 蛇自杀
        if (headPos == *bodyIt) { // 判断蛇头位置是否为身体
            return true;
        }
        ++bodyIt;
    }

    return false;
}

bool Snake::contains(const QPoint &point) const {
    return m_body.contains(point);
}

const QPoint& Snake::head() const {
    return m_body.first();
}

const QList<QPoint>& Snake::body() const {
    return m_body;
}

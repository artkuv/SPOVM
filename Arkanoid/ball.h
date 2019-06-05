#ifndef BALL_H
#define BALL_H

#define M_PI 3.15

#include <QGraphicsPixmapItem>
#include <QtMath>
#include <QList>
#include <QTimer>
#include "game.h"

class Ball: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Ball(int posx, int posy,qreal v,qreal phi,QGraphicsItem* parent = 0);
    void changeDirection(qreal);
    ~Ball();
private:
    QTimer *m_timer;
    qreal m_angle;
public slots:
    void move();
};

#endif // BALL_H

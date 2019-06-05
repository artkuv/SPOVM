#include "racket.h"

Racket::Racket(int posx, int posy, QGraphicsItem* parent):QObject(),QGraphicsPixmapItem(parent), is_moving_left(false),is_moving_right(false)
{
    QPixmap pix(":/img/racket.png");
    pix = pix.scaled(pix.width()*2,pix.height()*2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(pix);
    setPos(posx,posy);
    GameEngine::instance()->getScene()->addItem(this);
    startTimer(3);
}

Racket::~Racket()
{
    GameEngine::instance()->getScene()->removeItem(this);
}

void Racket::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        is_moving_left = true;
    if(event->key() == Qt::Key_Right)
        is_moving_right = true;
}

void Racket::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        is_moving_left = false;
    if(event->key() == Qt::Key_Right)
        is_moving_right = false;
}

void Racket::timerEvent(QTimerEvent *)
{
    if (is_moving_left)
        if(pos().x() > 12)
            setPos(x()-1,y());
    if (is_moving_right)
        if(pos().x() < 440 - 12 - sceneBoundingRect().width())
            setPos(x()+1,y());
}

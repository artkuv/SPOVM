#include "ball.h"

#define r_absx racket->pos().x()
#define r_absy racket->pos().y()
#define r_w racket->sceneBoundingRect().width()
#define r_h racket->sceneBoundingRect().height()
#define c_absx block->pos().x()
#define c_absy block->pos().y()
#define c_w block->sceneBoundingRect().width()
#define c_h block->sceneBoundingRect().height()
#define b_absx pos().x()
#define b_absy pos().y()
#define b_w sceneBoundingRect().width()
#define b_h sceneBoundingRect().height()

Ball::Ball(int posx, int posy,qreal v,qreal phi, QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent)
{
    m_angle = phi;
    QPixmap pix(":/img/ball.png");
    pix = pix.scaled(pix.width()*2,pix.height()*2, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(pix);
    setPos(posx,posy);
    GameEngine::instance()->getScene()->addItem(this);
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(move()));
    m_timer->start(10.0/v);
}

void Ball::changeDirection(qreal phi)
{
    m_angle = phi;
}

Ball::~Ball()
{
    delete m_timer;
    GameEngine::instance()->getScene()->removeItem(this);
}

void Ball::move()
{
    setPos(x() + qCos(m_angle),y() - qSin(m_angle));
    if(y() > LOOSELINE)
    {
        if(GameEngine::instance()->getLives()->getLives() == 1)
        {
            GameEngine::instance()->playSound(gameover);
            GameEngine::instance()->cleanup();
            GameEngine::instance()->showGameOver();
        }
        else
        {
            GameEngine::instance()->playSound(lose);
            GameEngine::instance()->setGameLost(true);
        }
        GameEngine::instance()->getLives()->decrease();
        GameEngine::instance()->remPlayer();
        return;
    }
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i )
    {
        if(Border* curr = dynamic_cast<Border*>(colliding_items[i]))
        {
            GameEngine::instance()->playSound(hitborder);
            switch(curr->getType())
            {
            case borderleftright:
                changeDirection(M_PI - m_angle);
                break;
            case bordertop:
                changeDirection(2*M_PI - m_angle);
                break;
            }
            break;
        }
        if(Racket* racket = dynamic_cast<Racket*>(colliding_items[i]))
        {
            if(r_absy > b_absy)
            {
                GameEngine::instance()->playSound(hitracket);
                setY(r_absy - b_h);
                changeDirection(M_PI/2 + 2.5 * (r_absx + r_w/2 - b_absx - b_w/2) / r_w );
            }
            break;
        }
        if(Cube* block = dynamic_cast<Cube*>(colliding_items[i]))
        {
            // CASE left
            if( b_absx < c_absx && b_absx + b_w - 2 < c_absx )
            {
                // subcase 1
                if( b_absy + b_h - 2 < c_absy && b_absy + b_h > c_absy )
                {
                    changeDirection(3*M_PI/4);
                }
                // subcase 2
                else if( b_absy < c_absy + c_h && b_absy + 2 > c_absy + c_h )
                {
                    changeDirection(5*M_PI/4);
                }
                // subcase 3
                else
                {
                    changeDirection(M_PI - m_angle);
                }
            }
            // CASE right
            else if( b_absx + b_w > c_absx + c_w && b_absx + 2 > c_absx + c_w )
            {
                // subcase 1
                if( b_absy + b_h - 2 < c_absy && b_absy + b_h > c_absy )
                {
                    changeDirection(-M_PI/4);
                }
                // subcase 2
                else if( b_absy < c_absy + c_h && b_absy + 2 > c_absy + c_h )
                {
                    changeDirection(M_PI/4);
                }
                // subcase 3
                else
                {
                    changeDirection(M_PI - m_angle);
                }
            }
            // CASE 2
            else
            {
                changeDirection(2*M_PI - m_angle);
            }
            block->actingOnCollision();
            if(GameEngine::instance()->getMatrix()->isEmpty())
            {
                GameEngine::instance()->playSound(gamewon);
                GameEngine::instance()->nextLvl();
                GameEngine::instance()->cleanup();
                GameEngine::instance()->startNewGame();
            }
            break;
        }
    }
}

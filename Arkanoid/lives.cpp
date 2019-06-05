#include "lives.h"

Lives::Lives(QGraphicsItem* parent): QGraphicsTextItem(parent)
{
    m_lives = 3;
    setPlainText(QString::number(m_lives) + QString(" LIFES"));
    setDefaultTextColor(Qt::red);
    setPos(50,0);
    GameEngine::instance()->getScene()->addItem(this);
}

void Lives::decrease()
{
    --m_lives;
    setPlainText(QString::number(m_lives) + QString(" LIFES"));
    setDefaultTextColor(Qt::red);
}

int Lives::getLives()
{
    return m_lives;
}

Lives::~Lives()
{
    GameEngine::instance()->getScene()->removeItem(this);
}

#include "score.h"

Score::Score(QGraphicsItem* parent): QGraphicsTextItem(parent)
{
    m_score = 0;
    setPlainText(QString::number(m_score) + QString("  SCORE"));
    setDefaultTextColor(Qt::white);
    setPos(50,30);
    GameEngine::instance()->getScene()->addItem(this);
}

void Score::increase(int x)
{
    m_score+=x;
    setPlainText(QString::number(m_score) + QString("  SCORE"));
    setDefaultTextColor(Qt::white);
}

int Score::getScore()
{
    return m_score;
}

Score::~Score()
{
    GameEngine::instance()->getScene()->removeItem(this);
}

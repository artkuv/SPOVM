#ifndef SCORE_H
#define SCORE_H

#include "game.h"

class Score: public QGraphicsTextItem {
public:
    Score(QGraphicsItem* parent=0);
    ~Score();
    void increase(int);
    int getScore();
private:
    int m_score;
};
#endif // SCORE_H

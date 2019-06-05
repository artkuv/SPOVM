#ifndef LIVES_H
#define LIVES_H

#include "game.h"

class Lives: public QGraphicsTextItem {
public:
    Lives(QGraphicsItem* parent=0);
    ~Lives();
    void decrease();
    int getLives();
private:
    int m_lives;
};

#endif // LIVES_H

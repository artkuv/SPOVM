#include "border.h"

Border::Border(const QPixmap &pix,char t): QObject(), QGraphicsPixmapItem(pix), type(t)
{
    GameEngine::instance()->getScene()->addItem(this);
}

char Border::getType()
{
    return type;
}

Border::~Border()
{
    GameEngine::instance()->getScene()->removeItem(this);
}

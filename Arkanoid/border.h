#ifndef BORDER_H
#define BORDER_H

#include <QGraphicsPixmapItem>
#include "game.h"

class Border : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Border(const QPixmap &pix,char t);
    char getType();
    ~Border();
private:
    char type;
};

#endif // BORDER_H

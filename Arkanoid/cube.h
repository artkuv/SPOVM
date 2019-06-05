#ifndef CUBE_H
#define CUBE_H

#include <QGraphicsRectItem>
#include <QStack>
#include "game.h"

#define CUBESWIDTH 32
#define CUBESHEIGHT 16
#define WSTART 12
#define HSTART SCOREHEIGHT + 15

class Cube: public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Cube(Qt::GlobalColor clr,int posx, int posy, int w, int h);
    virtual void actingOnCollision()=0;
    virtual ~Cube();

protected:
    bool deleted;

    void removeFromScene();
};

class UnbreakableCube: public Cube {
public:
    UnbreakableCube(int posx, int posy, int w=CUBESWIDTH, int h=CUBESHEIGHT) :Cube(Qt::gray,posx,posy,w,h) {}
    void actingOnCollision();
    ~UnbreakableCube(){}
};

class BreakableCube: public Cube {
public:
    BreakableCube(Qt::GlobalColor clr,int hlth,int posx, int posy, int w=CUBESWIDTH, int h=CUBESHEIGHT)
        :Cube(clr,posx,posy,w,h),m_health(hlth),m_score(0) {}
    void actingOnCollision();
    ~BreakableCube(){}
protected:
    int m_health;
    int m_score;
};

class RedCube: public BreakableCube {
public:
    RedCube(int posx, int posy, int w=CUBESWIDTH, int h=CUBESHEIGHT):BreakableCube(Qt::red,5,posx,posy,w,h) {}
    ~RedCube(){}
};

class YellowCube: public BreakableCube {
public:
    YellowCube(int posx, int posy, int w=CUBESWIDTH, int h=CUBESHEIGHT):BreakableCube(Qt::yellow,4,posx,posy,w,h) {}
    ~YellowCube(){}
};

class BlueCube: public BreakableCube {
public:
    BlueCube(int posx, int posy, int w=CUBESWIDTH, int h=CUBESHEIGHT):BreakableCube(Qt::blue,3,posx,posy,w,h) {}
    ~BlueCube(){}
};

class CyanCube: public BreakableCube {
public:
    CyanCube(int posx, int posy, int w=CUBESWIDTH, int h=CUBESHEIGHT):BreakableCube(Qt::cyan,2,posx,posy,w,h) {}
    ~CyanCube(){}
};

class GreenCube: public BreakableCube {
public:
    GreenCube(int posx, int posy, int w=CUBESWIDTH, int h=CUBESHEIGHT):BreakableCube(Qt::green,1,posx,posy,w,h) {}
    ~GreenCube(){}
};

class CubeMatrix {
public:
    CubeMatrix():cubes(new QStack<Cube*>),m_counting(0){}
    void fillLevel(unsigned char M[15][13],int n=15,int m=13);
    void decrement();
    bool isEmpty();
    ~CubeMatrix();
private:
    QStack<Cube*> *cubes;
    int m_counting;
};

#endif // CUBE_H

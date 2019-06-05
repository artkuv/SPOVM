#include "cube.h"

Cube::Cube(Qt::GlobalColor clr,int posx, int posy, int w, int h): deleted(false)
{
    setRect(0,0,w,h);
    setPos(posx,posy);
    setBrush(QBrush(clr));
    GameEngine::instance()->getScene()->addItem(this);
}

void Cube::removeFromScene()
{
    if(!deleted)
    {
        GameEngine::instance()->getScene()->removeItem(this);
        deleted = true;
    }
}

Cube::~Cube()
{
    removeFromScene();
}

void BreakableCube::actingOnCollision()
{
    --m_health;
    m_score+=100;
    GameEngine::instance()->playSound(hitbrk);
    if(!m_health)
    {
        GameEngine::instance()->getScore()->increase(m_score);
        GameEngine::instance()->getMatrix()->decrement();
        removeFromScene();
    }
}

void UnbreakableCube::actingOnCollision()
{
    GameEngine::instance()->playSound(hitubrk);
}

void CubeMatrix::fillLevel(unsigned char M[15][13],int n,int m)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            switch(M[i][j])
            {
            case empty:
                break;
            case green:
                cubes->push(new GreenCube(WSTART+j*CUBESWIDTH,HSTART+CUBESHEIGHT*i));
                ++m_counting;
                break;
            case cyan:
                cubes->push(new CyanCube(WSTART+j*CUBESWIDTH,HSTART+CUBESHEIGHT*i));
                ++m_counting;
                break;
            case blue:
                cubes->push(new BlueCube(WSTART+j*CUBESWIDTH,HSTART+CUBESHEIGHT*i));
                ++m_counting;
                break;
            case yellow:
                cubes->push(new YellowCube(WSTART+j*CUBESWIDTH,HSTART+CUBESHEIGHT*i));
                ++m_counting;
                break;
            case red:
                cubes->push(new RedCube(WSTART+j*CUBESWIDTH,HSTART+CUBESHEIGHT*i));
                ++m_counting;
                break;
            case ub:
                cubes->push(new UnbreakableCube(WSTART+j*CUBESWIDTH,HSTART+CUBESHEIGHT*i));
                break;
            }
        }
    }
}

void CubeMatrix::decrement()
{
    --m_counting;
}

bool CubeMatrix::isEmpty()
{
    return m_counting == 0;
}

CubeMatrix::~CubeMatrix()
{
    while(!cubes->empty()) {
        delete cubes->top();
        cubes->pop();
    }
    delete cubes;
}

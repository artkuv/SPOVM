#include "game.h"

GameEngine* GameEngine::s_instance;

unsigned char g_lvl_1[15][13] = {
    {   ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub     },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   empty,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   blue,   blue,   blue,   blue,   blue,   blue,   blue,   blue,   blue,   blue,   blue,   blue,   empty  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   empty,    red,    red,    red,    red,    red,    red,    red,    red,    red,    red,    red,    red  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
    {   ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     ub,     empty,     empty,     empty  },
    {   empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty,  empty  },
};


unsigned char g_lvl_2[15][13] = {
    {   empty,  empty,  empty,  ub,     ub,     empty,  empty,  empty,  ub,     ub,     empty,  empty,  empty   },
    {   empty,  empty,  ub,     yellow, yellow, ub,     empty,  ub,     blue,    blue,    ub,     empty,  empty   },
    {   empty,  ub,     yellow, yellow, yellow, yellow, ub,     blue,    blue,    blue,    blue,    ub,     empty   },
    {   empty,  ub,     yellow, yellow, yellow, yellow, yellow, blue,    blue,    blue,    blue,    ub,     empty   },
    {   ub,     yellow, yellow, yellow, yellow, yellow, blue,    blue,    blue,    blue,    blue,    blue,    ub      },
    {   ub,     yellow, yellow, yellow, yellow, yellow, yellow, blue,    blue,    blue,    blue,    blue,    ub      },
    {   ub,     yellow, yellow, yellow, yellow, yellow, blue,    blue,    blue,    blue,    blue,    blue,    ub      },
    {   cyan,   yellow, yellow, yellow, yellow, yellow, yellow, blue,    blue,    blue,    blue,    blue,    cyan    },
    {   empty,  cyan,   yellow, yellow, yellow, yellow, blue,    blue,    blue,    blue,    blue,    cyan,   empty   },
    {   empty,  cyan,   yellow, yellow, yellow, yellow, yellow, blue,    blue,    blue,    blue,    cyan,   empty   },
    {   empty,  empty,  cyan,   yellow, yellow, yellow, blue,    blue,    blue,    blue,    cyan,   empty,  empty   },
    {   empty,  empty,  empty,  cyan,   yellow, yellow, yellow, blue,    blue,    cyan,   empty,  empty,  empty   },
    {   empty,  empty,  empty,  empty,  cyan,   yellow, blue,    blue,    cyan,   empty,  empty,  empty,  empty   },
    {   empty,  empty,  empty,  empty,  empty,  cyan,   yellow, cyan,   empty,  empty,  empty,  empty,  empty   },
};

unsigned char g_lvl_3[15][13] = {
    {   empty,  empty,  empty,  yellow, empty,  empty,  empty,  empty,  empty,  yellow, empty,  empty,  empty   },
    {   empty,  empty,  empty,  yellow, empty,  empty,  empty,  empty,  empty,  yellow, empty,  empty,  empty   },
    {   empty,  empty,  empty,  empty,  yellow, empty,  empty,  empty,  yellow, empty,  empty,  empty,  empty   },
    {   empty,  empty,  empty,  empty,  yellow, empty,  empty,  empty,  yellow, empty,  empty,  empty,  empty   },
    {   empty,  empty,  empty,  green,  green,  green,  green,  green,  green,  green,  empty,  empty,  empty   },
    {   empty,  empty,  empty,  green,  green,  green,  green,  green,  green,  green,  empty,  empty,  empty   },
    {   empty,  empty,  green,  green,  red,    green,  green,  green,  red,    green,  green,  empty,  empty   },
    {   empty,  empty,  green,  green,  red,    green,  green,  green,  red,    green,  green,  empty,  empty   },
    {   empty,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  empty   },
    {   empty,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  empty   },
    {   empty,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  green,  empty   },
    {   empty,  green,  empty,  green,  green,  green,  green,  green,  green,  green,  empty,  green,  empty   },
    {   empty,  green,  empty,  green,  empty,  empty,  empty,  empty,  empty,  green,  empty,  green,  empty   },
    {   empty,  green,  empty,  green,  empty,  empty,  empty,  empty,  empty,  green,  empty,  green,  empty   },
};

QGraphicsScene *GameEngine::getScene() const
{
    return m_scene;
}

CubeMatrix *GameEngine::getMatrix() const
{
    return m_mtx;
}

Score *GameEngine::getScore() const
{
    return m_score;
}

Lives *GameEngine::getLives() const
{
    return m_lives;
}

bool GameEngine::lvlPassed() const
{
    return true;
}

bool GameEngine::gameLost() const
{
    return m_gamelose;
}

void GameEngine::setScene(QGraphicsScene *p_scene)
{
    m_scene = p_scene;
}

void GameEngine::initData(Border *p_lft, Border *p_top, Border *p_rght)
{
    m_lft = p_lft;
    m_top = p_top;
    m_rght = p_rght;
    m_score = new Score;
    m_lives = new Lives;
    m_gamequeue = new QQueue<unsigned char (*)[15][13]>;
    m_gamequeue->push_front(&g_lvl_1);
    m_gamequeue->push_front(&g_lvl_2);
    m_gamequeue->push_front(&g_lvl_3);
    m_brkcube = new QSound(":/sounds/hit_cube.wav");
    m_ubrkcube = new QSound(":/sounds/hit_unbreakable.wav");
    m_racket = new QSound(":/sounds/hit_racket.wav");
    m_border = new QSound(":/sounds/hit_border.wav");
    m_lose = new QSound(":/sounds/lose.wav");
    m_gameover = new QSound(":/sounds/game_over.wav");
    m_gamewon = new QSound(":/sounds/next_lvl.wav");
    setGameLost(false);
    m_ball = NULL;
    m_player = NULL;
    m_mtx = NULL;
}

void GameEngine::playSound(sounds p)
{
    switch (p)
    {
    case hitbrk:
        m_brkcube->play();
        break;
    case hitubrk:
        m_ubrkcube->play();
        break;
    case hitracket:
        m_racket->play();
        break;
    case hitborder:
        m_border->play();
        break;
    case lose:
        m_lose->play();
        break;
    case gameover:
        m_gameover->play();
        break;
    case gamewon:
        m_gamewon->play();
        break;
    }
}

void GameEngine::startNewGame()
{
    if(m_lives->getLives() && !m_player)
    {
        if(m_gamequeue->empty())
        {
            cleanup();
            showGameWon();
        }
        else
        {
            if(!gameLost())
            {
                m_mtx = new CubeMatrix;
                m_mtx->fillLevel(*m_gamequeue->back());
            }
            m_player = new Racket(180,520);
            m_ball = new Ball(210,400,qreal(3),qreal(-M_PI/2));
            m_player->setFlag(QGraphicsItem::ItemIsFocusable);
            m_player->setFocus();
            setGameLost(false);
        }
    }
}

void GameEngine::nextLvl()
{
    m_gamequeue->pop_back();
    m_gamelose = false;
}

void GameEngine::cleanup()
{
    delete m_ball;
    delete m_player;
    delete m_mtx;
}

void GameEngine::setGameLost(bool p)
{
    m_gamelose = p;
}

void GameEngine::remPlayer()
{
    delete m_player;
    delete m_ball;
    m_player = NULL;
    m_ball = NULL;
}

void GameEngine::showGameWon()
{
    m_gametxt = new QGraphicsTextItem;
    m_gametxt->setPlainText(QString("GAME WON :)"));
    m_gametxt->setDefaultTextColor(Qt::yellow);
    m_gametxt->setFont(QFont("Courier New",48));
    m_gametxt->setPos(10,400);
    m_scene->addItem(m_gametxt);
}

void GameEngine::showGameOver()
{
    m_gametxt = new QGraphicsTextItem;
    m_gametxt->setPlainText(QString("GAME OVER:("));
    m_gametxt->setDefaultTextColor(Qt::red);
    m_gametxt->setFont(QFont("Courier New",48));
    m_gametxt->setPos(10,400);
    m_scene->addItem(m_gametxt);
}

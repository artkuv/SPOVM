#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QSound>
#include <QQueue>
#include <QGraphicsPixmapItem>

#include "cube.h"
#include "ball.h"
#include "racket.h"
#include "border.h"
#include "lives.h"
#include "score.h"

#define SCOREHEIGHT 60
#define LOOSELINE 550

enum blocks { empty, green, cyan, blue, yellow, red, ub };
enum sounds { hitbrk, hitubrk, hitracket, hitborder, lose, gameover, gamewon };
enum border { borderleftright, bordertop };

class Ball;
class Score;
class Lives;
class Racket;
class Border;
class CubeMatrix;

class Pixmap : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
public:
    Pixmap(const QPixmap &pix): QObject(), QGraphicsPixmapItem(pix) {}
};

class GameEngine {
public:

    QGraphicsScene* getScene() const;
    CubeMatrix* getMatrix() const;
    Score* getScore() const;
    Lives* getLives() const;
    bool lvlPassed() const;
    bool gameLost() const;

    void setScene(QGraphicsScene* );
    void initData(Border *,Border *,Border *);
    void playSound(sounds);
    void startNewGame();
    void nextLvl();
    void cleanup();
    void setGameLost(bool);
    void remPlayer();
    void showGameWon();
    void showGameOver();

    static GameEngine *instance()
    {
        if (!s_instance)
        {
          s_instance = new GameEngine;
        }
        return s_instance;
    }

private:
    QGraphicsScene *m_scene;
    Ball *m_ball;
    Racket *m_player;
    CubeMatrix *m_mtx;
    Border *m_lft,*m_top,*m_rght;
    Score *m_score;
    Lives *m_lives;
    QQueue<unsigned char (*)[15][13]> *m_gamequeue;
    QSound *m_brkcube,*m_ubrkcube,*m_racket,*m_lose,*m_border,*m_gameover,*m_gamewon;
    QGraphicsTextItem *m_gametxt;
    bool m_gamelose;

    static GameEngine *s_instance;
    GameEngine(){}
};

#endif // GAME_H

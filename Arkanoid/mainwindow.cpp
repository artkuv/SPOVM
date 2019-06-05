#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_file = menuBar()->addMenu("Game");
    m_help = menuBar()->addMenu("Help");
    m_newGame = new QAction(tr("New Game"),this);
    m_exit = new QAction(tr("Exit"),this);
    m_about = new QAction(tr("About arkanoid"),this);
    m_newGame->setShortcut(QKeySequence::New);

    QPixmap bgPix(":/img/hexagon_pattern.png");
    QPixmap blft(":/img/border_left.png");
    QPixmap btop(":/img/border_top.png");
    QPixmap brght(":/img/border_right.png");
    bgPix = bgPix.scaled(bgPix.width()*2,bgPix.height()*1.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    blft = blft.scaled(blft.width()*2,blft.height()*1.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    btop = btop.scaled(btop.width()*2,btop.height()*1.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    brght = brght.scaled(brght.width()*2,brght.height()*1.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    setFixedSize(btop.width() + brght.width()+5,SCOREHEIGHT + btop.height() + bgPix.height()+25);
    m_scene = new QGraphicsScene(0,0,btop.width() + brght.width(),SCOREHEIGHT + btop.height() + bgPix.height());
    ui->graphicsView->setScene(m_scene);
    GameEngine::instance()->setScene(m_scene);

    Pixmap *sc_bgPix = new Pixmap(bgPix);
    sc_bgPix->setPos(blft.width() , btop.height() + SCOREHEIGHT);
    m_scene->addItem(sc_bgPix);

    Border *sc_blft = new Border(blft,borderleftright);
    Border *sc_btop = new Border(btop,bordertop);
    Border *sc_brght = new Border(brght,borderleftright);
    sc_btop->setPos(0 , SCOREHEIGHT);
    sc_blft->setPos(0 , btop.height() + SCOREHEIGHT);
    sc_brght->setPos(btop.width() - brght.width() , btop.height() + SCOREHEIGHT);

    GameEngine::instance()->initData(sc_blft,sc_btop,sc_brght);

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setBackgroundBrush(*new QBrush(Qt::black));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QIcon ico(tr(":/icon.ico"));
    setWindowIcon(ico);

    connect(m_newGame,SIGNAL(triggered()),this,SLOT(startNewGame()));
    connect(m_exit,SIGNAL(triggered()),this,SLOT(close()));
    connect(m_about,SIGNAL(triggered()),this,SLOT(openAbout()));

    m_file->addAction(m_newGame);
    m_file->addSeparator();
    m_file->addAction(m_exit);
    m_help->addAction(m_about);

    setCentralWidget(ui->graphicsView);
}

void MainWindow::startNewGame()
{
    GameEngine::instance()->startNewGame();
}

void MainWindow::openAbout()
{
    m_aboutDlg = new Dialog(this);
    m_aboutDlg->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

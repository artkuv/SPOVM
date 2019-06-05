#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "dialog.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *m_scene;

    QMenu *m_file,*m_help;
    QAction *m_newGame,*m_exit,*m_about;
    Dialog *m_aboutDlg;

private slots:
    void openAbout();
    void startNewGame();
};

#endif // MAINWINDOW_H

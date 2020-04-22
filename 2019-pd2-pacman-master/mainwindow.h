#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QLabel>
#include "pacman.h"
#include "background.h"
#include "ghost.h"
#include "ghost_blue.h"
#include "ghost_green.h"
#include "ghost_orange.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent*);
    void end(bool);


public slots:
    void pacmove();
    void ghostRun();
    void ghostChangeBack();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int scoreOnTable=0;
    int f,count;
    int x,y;
    bool color;
    QTimer *time,*ghosttime;
    pacman *Pac;
    background *map;
    ghost *red;
    ghost_blue *blue;
    ghost_green *green;
    ghost_orange *orange;
    QLabel *gameover, *win;

};

#endif // MAINWINDOW_H

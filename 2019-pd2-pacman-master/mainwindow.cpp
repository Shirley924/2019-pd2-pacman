#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pacman.h"
#include <QWidget>
#include <QDebug>
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(0,0,ui->graphicsView->width()-2,ui->graphicsView->height()-2);
    ui->graphicsView->setScene(scene);

    map=new background();
    map->setPos(11,10);
    scene->addItem(map);

    map->setball();
    for (int i=0;i<map->Ball.size();++i)
         scene->addItem(map->Ball.at(i));

    scene->addItem(map->power1);
    scene->addItem(map->power2);
    scene->addItem(map->power3);
    scene->addItem(map->power4);

    Pac=new pacman();
    Pac->setPos(35,120);
    //Pac->setPos(365,430);
    scene->addItem(Pac);
    f=3;
    count=0;
    x=0; y=0;
    color=true;

    red=new ghost();
    red->setPos(640,676);
//    red->setPos(400,410);
    scene->addItem(red);

    blue=new ghost_blue();
    blue->setPos(190,241);
    scene->addItem(blue);

    green=new ghost_green();
    green->setPos(280,763);
    scene->addItem(green);

    orange=new ghost_orange();
    orange->setPos(370,415);
    scene->addItem(orange);

    time =new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(pacmove()));
    ghosttime=new QTimer(this);
    connect(ghosttime,SIGNAL(timeout()),this,SLOT(ghostRun()));
    ghosttime->start(40);

    setFocus();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    //qDebug() << Pac->find_block();
    //qDebug() << map->judge[Pac->find_block()];
    if(map->judge[Pac->find_block()]==2)
    {
        Pac->setPos(map->point[Pac->find_block()].x()-15,map->point[Pac->find_block()].y()-15);
        switch(e->key())
        {
        case Qt::Key_Up:
            //qDebug()<<"up"<<endl;
            f=1;
            break;

        case Qt::Key_Down:
            f=2;
            break;

        case Qt::Key_Left:
            f=3;
            break;

        case Qt::Key_Right:
            f=4;
            break;
        }
    }
    time->start(40);
//    pacmove();

   /* if(map->judge[blue->find_block()]==2)
    {
        blue->setPos(map->point[blue->find_block()].x()-15,map->point[blue->find_block()].y()-15);
        switch(e->key())
        {
        case Qt::Key_W:
            //qDebug()<<"up"<<endl;
            blue->f=1;
            break;

        case Qt::Key_S:
            blue->f=2;
            break;

        case Qt::Key_A:
            blue->f=3;
            break;

        case Qt::Key_D:
            blue->f=4;
            break;
        }
    }
   //  blue->f=blue->shortestPath(Pac->find_block(),map->judge,0,blue->find_block());
    blue->move();*/
}

void MainWindow::ghostRun()
{
    //qDebug() << blue->shortestPath(Pac->find_block(),blue->find_block(),0);
    //qDebug()<<++x;
    ghost *G;
    G=red;
    G->shortestPath(Pac->find_block(),map->judge,0,red->find_block());
    G=blue;
    G->shortestPath(Pac->find_block(),map->judge,0,blue->find_block());
    G=green;
    G->shortestPath(Pac->find_block(),map->judge,0,green->find_block());
    G=orange;
    G->shortestPath(Pac->find_block(),map->judge,0,orange->find_block());

    if(color==true)
    {
        red->move(true);
        blue->move(true);
        green->move(true);
        orange->move(true);
    }
    else {
        red->move(false);
        blue->move(false);
        green->move(false);
        orange->move(false);
    }

    if(Pac->pos()==QPointF(1000,1000))
        end(false);
    else if(scoreOnTable==3020)
        end(true);

}

void MainWindow::ghostChangeBack()
{
    red->setPixmap(QPixmap(":/img/ghost_red.png").scaled(35,35));
    blue->setPixmap(QPixmap(":/img/ghost_blue.png").scaled(35,35));
    green->setPixmap(QPixmap(":/img/ghost_green.png").scaled(35,35));
    orange->setPixmap(QPixmap(":/img/ghost_orange.png").scaled(35,35));
    color=true;
}


void MainWindow::pacmove()
{
    QList<QGraphicsItem *> bomb = Pac->collidingItems();
    foreach(QGraphicsItem *i, bomb){
        QGraphicsEllipseItem *oops = dynamic_cast<QGraphicsEllipseItem *>(i);
        QGraphicsEllipseItem *yes = dynamic_cast<powerball *>(i);
        if(oops){
            oops->hide();
            scoreOnTable+=10;
            ui->score->display(scoreOnTable);
        }
        if(yes){
            red->setPixmap(QPixmap(":/img/ghost_change.png").scaled(35,35));
            blue->setPixmap(QPixmap(":/img/ghost_change.png").scaled(35,35));
            green->setPixmap(QPixmap(":/img/ghost_change.png").scaled(35,35));
            orange->setPixmap(QPixmap(":/img/ghost_change.png").scaled(35,35));
            color=false;
            QTimer::singleShot(5000,this,SLOT(ghostChangeBack()));
            //change ghost
        }
        if(color==false)
        {
            QGraphicsPixmapItem *attack = dynamic_cast<ghost *>(i);
            if(attack){
//                attack->hide();
                attack->setPos(370,766);

            }
        }
    }
    int k=Pac->find_block();

    if(Pac->pos()==QPointF(65,502))
        Pac->setPos(789,502);

    if(Pac->pos()==QPointF(790,502))
        Pac->setPos(66,502);

    qDebug()<<Pac->pos()<<' '<<k<<endl;
    //qDebug()<<x<<' '<<y<<endl;
    switch (f)
    {
    case 1:
        if(k-26>=0)
        {
            if(map->judge[k-26]==0)
                return;
            else if(map->judge[k-26]!=0)
                Pac->setPos(Pac->pos().x(),Pac->pos().y()-5);

         }
        else
            return;

//        Pac->setPos(Pac->pos().x(),Pac->pos().y()-5);
        break;

    case 2:
        if(k+26<754)
        {
            if(map->judge[k+26]==0)
                return;
            else if(map->judge[k+26]!=0)
                Pac->setPos(Pac->pos().x(),Pac->pos().y()+5);

        }
        else
            return;

//        Pac->setPos(Pac->pos().x(),Pac->pos().y()+5);

        break;

    case 3:
        //x=(Pac->pos().x()>0)?Pac->pos().x()-5:640;
        if(k%26>0)
        {
        if(map->judge[k-1]==0)
            return;
        else if(map->judge[k-1]!=0)
            Pac->setPos(Pac->pos().x()-5,Pac->pos().y());
        }
        else
            return;

//        Pac->setPos(Pac->pos().x()-5,Pac->pos().y());

        break;

    case 4:
        //x=(Pac->pos().x()<640)?Pac->pos().x()+5:0;
        if(k%26<25)
        {
        if(map->judge[k+1]==0)
            return;
        else if(map->judge[k+1]!=0)
            Pac->setPos(Pac->pos().x()+5,Pac->pos().y());
        }
        else
            return;

//        Pac->setPos(Pac->pos().x()+5,Pac->pos().y());

        break;
    }
    Pac->draw(f,count);
    ++count;

    if(count>3)
        count=0;
    //qDebug()<<Pac->pos().x()<<' '<<Pac->pos().y()<<endl;
}

void MainWindow::end(bool result)
{
    scene->removeItem(Pac);
    scene->removeItem(red);
    scene->removeItem(blue);
    scene->removeItem(green);
    scene->removeItem(orange);
//    scene->removeItem(map->power1);
//    scene->removeItem(map->power2);
//    scene->removeItem(map->power3);
//    scene->removeItem(map->power4);
//    scene->removeItem(map->Ball);
//    scene->removeItem(map);


    time->stop();
    ghosttime->stop();

    if(result==false)
    {
        gameover=new QLabel();
        gameover->setPixmap(QPixmap(":/img/game over.jpg"));
        gameover->setGeometry(55,120,679,856);
    }
    else {
        win=new QLabel();
        win->setPixmap((QPixmap(":/img/win.jpg")));
        win->setGeometry(55,120,840,600);
    }


//    back->getNumber(scoreOnTable);
    scoreOnTable=0;
}

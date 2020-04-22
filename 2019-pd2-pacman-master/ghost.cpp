#include "ghost.h"
//#include "mainwindow.h"
#include <QDebug>

ghost::ghost()
{
    f=0;
    k=0;
    min=0;
    inside=true;

    setPixmap(QPixmap(":/img/ghost_red.png").scaled(35,35));
}

int ghost::find_block()
{    
    j = pos().x()-40;
    j/=30;

    i=pos().y()-125;
    i/=29;
    //qDebug() << i/30 << j/29 <<endl;
    return i*26+j;
}


int ghost::shortestPath(int pacman, int tempMap[754], int distance,int K)
{
    //int K=find_block();
//    qDebug()<<"pacman"<<pacman<<"ghost"<<K<<"distance"<<distance;
    if((tempMap[K]==2)||(distance>30)||(find_block()==338)||(find_block()==363))
    {
        min=qrand()%4+1;
        min=qrand()%4+1;
        return distance;
    }
    int the_shortest=55;
    int path[4]={0};
    int way=tempMap[K];

    tempMap[K]=0;
    if (tempMap[K-26]==true && K>=0)
    {
        path[0]=shortestPath(pacman,tempMap,++distance,K-26);
//        qDebug()<<"path[0]"<<path[0];
    }
    if (tempMap[K+26]==true && K<753)
    {
        path[1]=shortestPath(pacman,tempMap,++distance,K+26);
//        qDebug()<<"path[1]"<<path[1];
    }
    if (tempMap[K-1]==true && K>=0)
    {
        path[2]=shortestPath(pacman,tempMap,++distance,K-1);
//        qDebug()<<"path[2]"<<path[2];
    }
    if (tempMap[K+1]==true && K<753)
    {
        path[3]=shortestPath(pacman,tempMap,++distance,K+1);
//        qDebug()<<"path[3]"<<path[3];
    }
    tempMap[K]=way;
    for (int n=0;n<3;++n)
    {
/*        if(path[n]<path[n+1])
        {
            the_shortest=path[n];
            min=n+1;
        }
        else {
            the_shortest=path[n+1];
            min=n+2;
        }
*/
        if((path[n]<the_shortest) && path[n]>0)
        {
            the_shortest=path[n];
            min=n+1;
//            qDebug()<<"direction"<<min;
        }
    }
    return the_shortest;
}

//void ghost::first_go()
//{

//}


/*
int ghost::shortestPath(int pacman,int K,int distant)
{
    k=K;
    qDebug()<<"pac"<<pacman;
    qDebug()<<"k"<<k;
qDebug()<<distant;
    int the_shortest=55;
    int path[4]={0};
    int way=tempMap[k];
    qDebug()<<min<<"direct"<<endl;

//    int testMap[754];
    //qDebug()<<k;

    if(k==pacman)
    {//all path=0

        return distant; //wrong way
    }
    if(k!=pacman)
    {
        tempMap[k]=0;
//        for (int n=0;n<754;++n)
//            tempMap[n]=tempMap[n];

        if(k-26>0)
        {
            if(tempMap[k-26]!=0)
            {

                path[0]=shortestPath(pacman,k-26,++distant);
//                qDebug()<<"up"<<distant;

            }
        }
        if(k+26<754)
        {
            if(tempMap[k+26]!=0)

                path[1]=shortestPath(pacman,k+26,++distant);
            {
//                qDebug()<<"down"<<distant;

            }
        }
        if(k-1>0)
        {
            if(tempMap[k-1]!=0)
            {
                path[2]=shortestPath(pacman,k-1,++distant);

//                qDebug()<<"left"<<distant;

            }
        }
        if(k+1<754)
        {
            if(tempMap[k+1]!=0)
            {

                path[3]=shortestPath(pacman,k+1,++distant);
//                qDebug()<<"right"<<distant;

            }
        }
        tempMap[k]=way;
//        if(k-26>=0&&k+26<754&&k-1>=0&&k+1<754)
//        {
//            if(testMap[k-26]==0&&testMap[k+26]==0&&testMap[k-1]==0&&testMap[k+1]==0)
//                qDebug()<<"hi"<<distant;
//                return distant;
//        }
        for(int n=0;n<4;++n)
        {
            if(path[n]!=0)
            {
                if(path[n]<the_shortest)
                {
                    the_shortest=path[n];
                    min=n+1;
                }
            }
        }
//        qDebug()<<"path[0]"<<path[0];
//        qDebug()<<"path[1]"<<path[1];
//        qDebug()<<"path[2]"<<path[2];
//        qDebug()<<"path[3]"<<path[3];
//        qDebug()<<"the shortest"<<the_shortest;
        return the_shortest;
    }

}
*/

void ghost::move(bool color)
{
    if(color==true)
    {
        QList<QGraphicsItem *> pac = collidingItems();
        foreach(QGraphicsItem *i, pac){
            QGraphicsPixmapItem *die = dynamic_cast<pacman *>(i);
            if(die){
                die->hide();
                die->setPos(1000,1000);
//a function to end the game
            }
         }
    }

    int k=find_block();
    //qDebug()<<"move";
    //qDebug()<<f;
    switch (min)
    {
    case 1:
        if(k-26>=0)
        {
            if(background::judge[k-26]==0)
                return;
            else if(background::judge[k-26]!=0)
                setPos(pos().x(),pos().y()-5);

         }
        else
            return;

//        Pac->setPos(Pac->pos().x(),Pac->pos().y()-5);
        break;

    case 2:
        if(k+26<754)
        {
            if(background::judge[k+26]==0)
                return;
            else if(background::judge[k+26]!=0)
                setPos(pos().x(),pos().y()+5);

        }
        else
            return;

//        Pac->setPos(Pac->pos().x(),Pac->pos().y()+5);

        break;

    case 3:
        //x=(Pac->pos().x()>0)?Pac->pos().x()-5:640;
        qDebug()<<"go";
        if(k%26>0)
        {
        if(background::judge[k-1]==0)
            return;
        else if(background::judge[k-1]!=0)
            setPos(pos().x()-5,pos().y());
        }
        else
            return;

//        Pac->setPos(Pac->pos().x()-5,Pac->pos().y());

        break;

    case 4:
        //x=(Pac->pos().x()<640)?Pac->pos().x()+5:0;
        if(k%26<25)
        {
        if(background::judge[k+1]==0)
            return;
        else if(background::judge[k+1]!=0)
            setPos(pos().x()+5,pos().y());
        }
        else
            return;

//        Pac->setPos(Pac->pos().x()+5,Pac->pos().y());

        break;
    }

    //qDebug()<<Pac->pos().x()<<' '<<Pac->pos().y()<<endl;
}

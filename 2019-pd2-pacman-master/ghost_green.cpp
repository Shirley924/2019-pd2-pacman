#include "ghost_green.h"

ghost_green::ghost_green()
{
    setPixmap(QPixmap(":/img/ghost_green.png").scaled(35,35));
}

int ghost_green::shortestPath(int pacman, int tempMap[754], int distance,int K)
{
    //int K=find_block();
//    qDebug()<<"pacman"<<pacman<<"ghost"<<K<<"distance"<<distance;
    if((tempMap[K]==2)||(distance>30)||(find_block()==338)||(find_block()==363))
    {
        min=qrand()%4+1;
        return distance;
    }
    int the_shortest=55;
    int path[4]={0};
    int way=tempMap[K];

    tempMap[K]=0;

    if (tempMap[K+26]==true && K<753)
    {
        path[0]=shortestPath(pacman,tempMap,++distance,K+26);
//        qDebug()<<"path[0]"<<path[0];
    }
    if (tempMap[K-1]==true && K>=0)
    {
        path[1]=shortestPath(pacman,tempMap,++distance,K-1);
//        qDebug()<<"path[1]"<<path[1];
    }
    if (tempMap[K+1]==true && K<753)
    {
        path[2]=shortestPath(pacman,tempMap,++distance,K+1);
//        qDebug()<<"path[2]"<<path[2];
    }
    if (tempMap[K-26]==true && K>=0)
    {
        path[3]=shortestPath(pacman,tempMap,++distance,K-26);
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

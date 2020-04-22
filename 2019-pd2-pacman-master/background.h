#ifndef BACKGROUND_H
#define BACKGROUND_H

#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QPainter>
#include<QVector>
#include"powerball.h"

class background : public QGraphicsPixmapItem
{
public:
    background();

    powerball *power1,*power2,*power3,*power4;
    QVector<ball*> Ball;
    QVector<QPoint> point;  //store the location of blocks
    //road or wall
    static int judge[754];
    void setball();

private:



};

#endif // BACKGROUND_H

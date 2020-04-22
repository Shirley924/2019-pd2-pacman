#ifndef BALL_H
#define BALL_H
#include<QGraphicsItem>
#include<QGraphicsScene>


class ball : public QGraphicsEllipseItem
{
public:
    ball(int,int,int,int);
};

#endif // BALL_H

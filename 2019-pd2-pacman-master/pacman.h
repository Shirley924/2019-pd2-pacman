#ifndef PACMAN_H
#define PACMAN_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
class pacman : public QGraphicsPixmapItem
{

public:
    pacman();

    void draw(int,int);
    int find_block();

private:

    QPixmap right1,right2,left1,left2;
    QPixmap up1,up2,down1,down2,round;

};
#endif // PACMAN_H

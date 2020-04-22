#include "pacman.h"

pacman::pacman()
{
    right1=QPixmap(":/img/right1.png");
    right2=QPixmap(":/img/right2.png");

    left1=QPixmap(":/img/left1.png");
    left2=QPixmap(":/img/left2.png");

    up1=QPixmap(":/img/up1.png");
    up2=QPixmap(":/img/up2.png");

    down1=QPixmap(":/img/down1.png");
    down2=QPixmap(":/img/down2.png");

    round=QPixmap(":/img/round.png");
    setPixmap(left1.scaled(30,30));
}

void pacman::draw(int f,int count)
{
    switch(f)
    {
        case 1:
            if(count%3==0)
                setPixmap(round.scaled(30,30));
            else if (count%3==1)
                setPixmap(up1.scaled(30,30));
            else
                setPixmap(up2.scaled(30,30));
        break;

        case 2:
            if(count%3==0)
                setPixmap(round.scaled(30,30));
            else if (count%3==1)
                setPixmap(down1.scaled(30,30));
            else
                setPixmap(down2.scaled(30,30));
        break;

        case 3:
            if(count%3==0)
                setPixmap(round.scaled(30,30));
            else if (count%3==1)
                setPixmap(left1.scaled(30,30));
            else
                setPixmap(left2.scaled(30,30));
        break;

        case 4:
            if(count%3==0)
                setPixmap(round.scaled(30,30));
            else if (count%3==1)
                setPixmap(right1.scaled(30,30));
            else
                setPixmap(right2.scaled(30,30));
        break;

    }


}

int pacman::find_block()
{
    int i,j;
    j = pos().x()-40;
    j/=30;

    i=pos().y()-125;
    i/=29;
    //qDebug() << i/30 << j/29 <<endl;
    return i*26+j;
}

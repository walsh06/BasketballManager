#include "PlayerGraphic.h"

PlayerGraphic::PlayerGraphic() : blackPen(Qt::black), player(0,0,30,30)
{
    player.setPen(blackPen);
    number.setDefaultTextColor(Qt::white);
}

QGraphicsTextItem * PlayerGraphic::getNumber()
{
    return &number;
}

QGraphicsEllipseItem * PlayerGraphic::getPlayer()
{
    return &player;
}

int PlayerGraphic::getX()
{
    return x;
}

int PlayerGraphic::getY()
{
    return y;
}

void PlayerGraphic::setPos(int x, int y)
{
    player.setPos(x, y);
    number.setPos(x + 8, y + 3);
    this->x = x; this->y = y;
}

void PlayerGraphic::setNumber(int n)
{
    number.setPlainText(QString::number(n));
}

void PlayerGraphic::setColour(QBrush *brush)
{
    player.setBrush(*brush);
}

void PlayerGraphic::setTextColour()
{
    number.setDefaultTextColor(Qt::white);
}

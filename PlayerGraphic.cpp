#include "PlayerGraphic.h"

/** PlayerGraphic Constructor */
PlayerGraphic::PlayerGraphic() : blackPen(Qt::black), player(0,0,30,30)
{
    player.setPen(blackPen);
    number.setDefaultTextColor(Qt::white);
}

/** Return the number text item */
QGraphicsTextItem * PlayerGraphic::getNumber()
{
    return &number;
}

/** Return the ellipse graphical item */
QGraphicsEllipseItem * PlayerGraphic::getPlayer()
{
    return &player;
}

/** Return x position */
int PlayerGraphic::getX()
{
    return x;
}

/** Return y position */
int PlayerGraphic::getY()
{
    return y;
}

/** Set x and y position of the player graphic */
void PlayerGraphic::setPos(int x, int y)
{
    player.setPos(x, y);
    //offset the number to the middle of the ellipse
    number.setPos(x + 8, y + 3);
    this->x = x; this->y = y;
}

/** Set the value of the number */
void PlayerGraphic::setNumber(int n)
{
    number.setPlainText(QString::number(n));
}

/** Set the colour of the player */
void PlayerGraphic::setColour(QBrush *brush)
{
    player.setBrush(*brush);
}

/** Set the text colour of the player */
void PlayerGraphic::setTextColour()
{
    number.setDefaultTextColor(Qt::white);
}

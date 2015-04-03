#ifndef PLAYERGRAPHIC_H
#define PLAYERGRAPHIC_H

#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QPen>

/* Class used to represent a graphical player in the match screen
 * Stores elements such as graphical ellipse, number, name and
 * position
 */
class PlayerGraphic
{
public:
    PlayerGraphic();

    QGraphicsTextItem *getNumber();
    QGraphicsEllipseItem *getPlayer();
    int getX();
    int getY();
    void setPos(int x, int y);
    void setNumber(int n);
    void setColour(QBrush *brush);
    void setTextColour();

private:
    QGraphicsTextItem number;
    QGraphicsEllipseItem player;
    QGraphicsTextItem name;
    QPen blackPen;
    int x, y;
};

#endif // PLAYERGRAPHIC_H

#include "GUI/gosoba.h"

gOsoba::gOsoba(short sifra)
    :_sifra(sifra)
{

}

gOsoba::~gOsoba()
{

}

QRectF gOsoba::boundingRect() const
{
    return QRectF();
}

QPainterPath gOsoba::shape() const
{
    return QPainterPath();
}

void gOsoba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //samo da se vidi nesto
    QColor color(0, 255, 0);
    painter->setBrush(color);
    painter->drawEllipse(this->pos(), 20, 20);
}


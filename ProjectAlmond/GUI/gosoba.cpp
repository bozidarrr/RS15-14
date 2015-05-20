#include "gosoba.h"

GOsoba::GOsoba(short sifra, QString ime_prezime)
    :_sifra(sifra)
{
}

GOsoba::~GOsoba()
{

}

QRectF GOsoba::boundingRect() const
{
    qreal d = 1;
    return QRectF(-40-d, -20-d, 80+d, 40+d);
}

//QPainterPath gOsoba::shape() const
//{
//    return QPainterPath();
//}

void GOsoba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //samo da se vidi nesto
    QColor color(Qt::darkGreen);
    painter->setBrush(color);
    painter->drawEllipse(-40, -20, 80, 40);
    //painter->setPen(Qt::darkRed);
    //painter->drawText(-40, 30, "ime i prezime");
}

int GOsoba::type() const
{
    //ovo da bi qgraphicscast funkcionisao
    return Type;
}

short GOsoba::Sifra() const
{
    return _sifra;
}

void GOsoba::obavestiRelacije()
{
    emit pomerilaSe(pos());
}

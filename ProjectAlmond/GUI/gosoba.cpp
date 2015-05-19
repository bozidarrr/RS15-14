#include "GUI/gosoba.h"

gOsoba::gOsoba(short sifra, QString ime_prezime)
    :_sifra(sifra)
{
    setData(IME_PREZIME, ime_prezime);
}

gOsoba::~gOsoba()
{

}

QRectF gOsoba::boundingRect() const
{
    qreal d = 1;
    return QRectF(-40-d, -20-d, 80+d, 40+d);
}

//QPainterPath gOsoba::shape() const
//{
//    return QPainterPath();
//}

void gOsoba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //samo da se vidi nesto
    QColor color(Qt::darkGreen);
    painter->setBrush(color);
    painter->drawEllipse(-40, -20, 80, 40);
    //painter->setPen(Qt::darkRed);
    //painter->drawText(-40, 30, "ime i prezime");
}

int gOsoba::type() const
{
    //ovo da bi qgraphicscast funkcionisao
    return Type;
}

short gOsoba::Sifra() const
{
    return _sifra;
}

//void gOsoba::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "pritisnuto na osobu";
//}


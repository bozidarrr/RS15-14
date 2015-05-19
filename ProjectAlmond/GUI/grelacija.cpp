#include "GUI/grelacija.h"

gRelacija::gRelacija(short sifra, QPointF prva, QPointF druga, bool brak)
    : _sifra(sifra), _prva(prva), _druga(druga), _brak(brak)
{
}

gRelacija::~gRelacija()
{}

QRectF gRelacija::boundingRect() const
{
    qreal d = 1;
    return QRectF(-20-d, -20-d, 40+d, 40+d);
}

void gRelacija::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    postaviNaSredinu();
    painter->setPen(Qt::green);
    painter->drawLine(mapFromScene(_prva), mapFromScene(_druga));
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(-20, -20, 40, 40);
}

int gRelacija::type() const
{
    return Type;
}

short gRelacija::Sifra() const
{
    return _sifra;
}

bool gRelacija::BrakJe() const
{
    return _brak;
}

void gRelacija::postaviNaSredinu()
{
    QPointF pozicija((_prva.x() + _druga.x())/2, (_prva.y() + _druga.y())/2);
    setPos(pozicija);
}


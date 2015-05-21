#include "GUI/grelacija.h"

GRelacija::GRelacija(short sifra, QPointF prva, QPointF druga, bool brak)
    : _sifra(sifra), _prva(prva), _druga(druga), _brak(brak)
{
    postaviNaSredinu();
}

GRelacija::~GRelacija()
{}

QRectF GRelacija::boundingRect() const
{
    qreal d = 1;
    return QRectF(-20-d, -20-d, 40+d, 40+d);
}

void GRelacija::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//        qDebug() << "crta se";
//            qDebug() << _sifra;
    painter->setPen(Qt::green);
    painter->drawLine(mapFromScene(_prva), mapFromScene(_druga));
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(-20, -20, 40, 40);
    //QRect okvir(-40, -40, 80, 80);
    //QPixmap slika(":/images/images/RelacijaSupruznici.ico");
    //painter->drawPixmap(okvir, slika);
}

int GRelacija::type() const
{
    return Type;
}

short GRelacija::Sifra() const
{
    return _sifra;
}

bool GRelacija::BrakJe() const
{
    return _brak;
}

void GRelacija::pomeriDrugu(QPointF druga)
{
    //qDebug() << "pomera drugu";
    _druga = druga;
    postaviNaSredinu();
}

void GRelacija::pomeriPrvu(QPointF prva)
{
       // qDebug() << "pomera prvu";
    _prva = prva;
    postaviNaSredinu();
}

void GRelacija::postaviNaSredinu()
{
    QPointF pozicija((_prva.x() + _druga.x())/2, (_prva.y() + _druga.y())/2);
    setPos(pozicija);
    emit pomerilaSe(pozicija);
}

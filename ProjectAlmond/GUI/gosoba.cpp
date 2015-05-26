#include "gosoba.h"
#include <QGraphicsScene>

GOsoba::GOsoba(short sifra, QString ime_prezime)
    :_sifra(sifra), _sirina(100), _visina(40), _ime(ime_prezime)
{
}

GOsoba::~GOsoba()
{

}

QRectF GOsoba::boundingRect() const
{
    qreal d = 1;
    return QRectF(-_sirina/2-d, -_visina/2-d, _sirina+d, _visina+d);
}

//QPainterPath gOsoba::shape() const
//{
//    return QPainterPath();
//}

void GOsoba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //samo da se vidi nesto
    //QColor color(Qt::darkGreen);
    painter->setBrush(_osnovnaBoja);
    QRectF rect(-_sirina/2, -_visina/2, _sirina, _visina);
    painter->setRenderHint(QPainter::Antialiasing,false);
    painter->drawRoundedRect( rect.translated(0.5,0.5), 3.0, 3.0 );
    //painter->drawRoundedRect(-40, -20, 80, 40, 2, 2);
    painter->setPen(Qt::green);
    //painter->drawText(-40, 0, _ime);
    painter->drawText(rect, Qt::AlignCenter | Qt::TextWordWrap, _ime);//doterati malo
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

void GOsoba::promeniIme(const QString &novoIme)
{
    _ime = novoIme;
}

void GOsoba::obavestiRelacije()
{
    emit pomerilaSe(pos());
}

void GOsoba::promeniStil(Stil stil)
{
    _ukljuceniFlegovi |= stil;//TO DO
    //napraviti .css za ovo
    switch (stil)
    {
    case SELEKTOVANA:
            _osnovnaBoja = Qt::darkYellow;
            break;
    case POKOJNA:
            _osnovnaBoja = Qt::gray;
            break;
    case OBICNA:
    default:
            _osnovnaBoja = Qt::darkGreen;
            break;
    }
}

void GOsoba::skloniSeSaScene(short sifra)
{
    if (_sifra != sifra)
        return;
    if (scene() != 0)
        scene()->removeItem(this);
    deleteLater();
}

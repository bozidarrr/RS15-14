#ifndef GRELACIJA_H
#define GRELACIJA_H
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QString>


class gRelacija : public QGraphicsItem
{
public:
    enum { Type = UserType + 2 };
    /** konstruktor prihvata sifru relacije, i pozicije onoga sto spaja (dve osobe, ili brak i dete) **/
    gRelacija(short sifra, QPointF prva, QPointF druga, bool brak);
    ~gRelacija();

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    int type() const;

    short int Sifra() const;
    bool BrakJe() const;

private:
    short _sifra;
    QPointF _prva, _druga;
    bool _brak;

    void postaviNaSredinu();
};

#endif // GRELACIJA_H

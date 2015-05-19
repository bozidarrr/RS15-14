#ifndef GOSOBA_H
#define GOSOBA_H
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QString>

class gOsoba : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };

    enum {IME_PREZIME};

    gOsoba(short int sifra, QString ime_prezime);
    ~gOsoba();

    QRectF boundingRect() const override;

    //QPainterPath shape() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    int type() const;

    short int Sifra() const;

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    short int _sifra;
    int _sirina, _duzina;
};

#endif // GOSOBA_H

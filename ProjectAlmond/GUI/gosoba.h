#ifndef GOSOBA_H
#define GOSOBA_H
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>

class gOsoba : public QGraphicsItem
{
public:
    gOsoba(short int sifra);
    ~gOsoba();

    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
private:
    short int _sifra;
};

#endif // GOSOBA_H

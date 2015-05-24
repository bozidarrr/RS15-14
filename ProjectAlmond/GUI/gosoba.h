#ifndef GOSOBA_H
#define GOSOBA_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QString>

class GOsoba : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum { Type = UserType + 1 };

    enum Stil { OBICNA, KORENA, SELEKTOVANA, POKOJNA, NEPOZNATA, SLAVLJENIK };//DA LI OVAKO OVO DA RADIMO?
    //mozda bi bolje bilo nesto kao sa flegovima, da onda radimo bitovsko & i |, nemam pojma

    GOsoba(short int sifra, QString ime_prezime);
    ~GOsoba();

    QRectF boundingRect() const override;

    //QPainterPath shape() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    int type() const;

    short int Sifra() const;

    void promeniIme(const QString &novoIme);

    void obavestiRelacije();

    void promeniStil(Stil stil);

signals:
    void pomerilaSe(QPointF);

public slots:
    void skloniSeSaScene(short sifra);

private:
    short int _sifra;
    int _sirina, _visina;
    QString _ime;
    QColor _osnovnaBoja = Qt::darkGreen;
};

#endif // GOSOBA_H



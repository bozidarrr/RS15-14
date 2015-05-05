#ifndef WIDGETRELACIJA_H
#define WIDGETRELACIJA_H


#include <QWidget>

#include <QLabel>
#include <string>
#include <QString>
#include "GUI/glavniprozor2.h"
#include "GUI/okvirstabla.h"

class GlavniProzor2;

namespace Ui {
class WidgetRelacija;
}

class WidgetRelacija : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetRelacija(short int sifra, int x, int y,
                         GlavniProzor2 *gp, QWidget *parent = 0);
    ~WidgetRelacija();

    int X()const;

    int Y()const;

    void setX(int x);

    void setY(int y);

    short Sifra()const;


private:
    Ui::WidgetRelacija *ui;

    short int _sifra;
    int _x;
    int _y;
    GlavniProzor2 *w;
};


#endif // WIDGETRELACIJA_H



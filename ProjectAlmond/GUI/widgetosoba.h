#ifndef WIDGETOSOBA_H
#define WIDGETOSOBA_H

#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <string>
#include <QString>
#include "GUI/glavniprozor.h"
#include "alati/filterzalabelu.h"
#include "alati/filterobject.h"
#include "GUI/okvirstabla.h"


class GlavniProzor;

namespace Ui {
class WidgetOsoba;
}

class WidgetOsoba : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetOsoba(short int sifra, int x, int y,
                         GlavniProzor *gp, QWidget *parent = 0);
    ~WidgetOsoba();

    void postaviImePrezime(const std::string &ip);

    int X()const;

    int Y()const;

    void setX(int x);

    void setY(int y);

    short Sifra()const;

    //bool sadrziTacku(int x, int y);
    //bool operator ==(const WidgetOsoba& druga)const;


private:
    Ui::WidgetOsoba *ui;

    short int _sifra;
    int _x;
    int _y;

    GlavniProzor *w;
};

#endif // WIDGETOSOBA_H

#ifndef WIDGETOSOBA_H
#define WIDGETOSOBA_H

#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <string>
#include <QString>
#include "GUI/glavniprozor.h"
#include "GUI/glavniprozor2.h"

class GlavniProzor;
class GlavniProzor2;

namespace Ui {
class WidgetOsoba;
}

class WidgetOsoba : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetOsoba(short int sifra, int x, int y,const QString &ime, const QString &prezime,
                         GlavniProzor2 *gp, QWidget *parent = 0);
    ~WidgetOsoba();

    void postaviImePrezime(const std::string &ip);

    int X()const;

    int Y()const;
    short Sifra()const;

    bool sadrziTacku(int x, int y);
    //bool operator ==(const WidgetOsoba& druga)const;

private slots:
    void on_btnOsoba_clicked();

    void on_btnOsoba_pressed();

    void on_btnOsoba_released();

    //void on_btnOsoba_toggled(bool checked);


private:
    Ui::WidgetOsoba *ui;

    short int _sifra;
    int _x;
    int _y;
    //GlavniProzor *w;
    GlavniProzor2 *w;
};

#endif // WIDGETOSOBA_H

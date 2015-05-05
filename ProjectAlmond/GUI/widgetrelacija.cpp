#include "widgetrelacija.h"
#include "ui_widgetrelacija.h"
#include "GUI/glavniprozor.h"
#include <iostream>
#include <QtGui>
WidgetRelacija::WidgetRelacija(short int sifra, int x, int y,  GlavniProzor2 *gp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetRelacija),
    _sifra(sifra),_x(x),_y(y),
    w(gp)
{
    ui->setupUi(this);

}


WidgetRelacija::~WidgetRelacija()
{
    delete ui;
}

int WidgetRelacija::X()const{
    return _x;
}

int WidgetRelacija::Y()const
{
    return _y;
}
short int WidgetRelacija::Sifra()const
{
    return _sifra;
}

void WidgetRelacija::setX(int x)
{
    //provera da li je u redu!
    _x=x;
}

void WidgetRelacija::setY(int y)
{
    //provera da li je u redu!
    _y=y;
}




/*#include "widgetosoba.h"
#include "ui_widgetosoba.h"
#include "GUI/glavniprozor.h"
#include <iostream>
#include <QtGui>
WidgetOsoba::WidgetOsoba(short int sifra, int x, int y,  GlavniProzor *gp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetOsoba),
    _sifra(sifra),_x(x),_y(y),
    w(gp)
{
    ui->setupUi(this);
    //ovako se menja izgled pomocu css-a
    ui->ImeOsobe->setStyleSheet (" background-color:rgb(128,255,128);"
                                 "color: blue;"
                                 "font-style:italic;"
                                 "selection-background-color: rgb(128,255,128);"
                                 "border:1px dashed green;"
                                 //"backgruond-image:url(".....");"
                                 " font-size:12px; ");
    //sad kad sam nasla kako se to implementira mozda bi hteli malo drugacije da napravimo widget posto sam trazila i ne postoji
    //toolkit u Qt mislila sam mozda da dodamo neku labelu sa zaobljenim ivicama posto u css-u to moze da se kaze
    ui->ImeOsobe->installEventFilter(new filterZaLabelu());
    this->installEventFilter(new FilterObject(gp->stabloOkvir));


}


WidgetOsoba::~WidgetOsoba()
{
    delete ui;
}

int WidgetOsoba::X()const{
    return _x;
}

int WidgetOsoba::Y()const
{
    return _y;
}
short int WidgetOsoba::Sifra()const
{
    return _sifra;
}

void WidgetOsoba::setX(int x)
{
    //provera da li je u redu!
    _x=x;
}

void WidgetOsoba::setY(int y)
{
    //provera da li je u redu!
    _y=y;
}


//bool WidgetOsoba::sadrziTacku(int x, int y)
//{
//    bool rez = x >= _x
//            && x <= _x + ui->ImeOsobe->width()
//            && y >= _y
//            && y <= _y + ui->ImeOsobe->height();
//    return rez;

//}

void WidgetOsoba::postaviImePrezime(const std::string &ip)
{
    QString q_ip = QString::fromStdString(ip);
    ui->ImeOsobe->setText(q_ip);
}





//bool WidgetOsoba::operator ==(const WidgetOsoba& druga)const{
//    //za proveru jednakosti 2 widgeta dovoljno je da proverimo njihove sifre jer je to jedinstveni identifikator
//    if(_sifra==druga._sifra)
//        return true;
//    return false;
//}

*/

#include "widgetosoba.h"
#include "ui_widgetosoba.h"
#include "GUI/glavniprozor.h"
#include <iostream>

WidgetOsoba::WidgetOsoba(short int sifra, int x, int y, const QString &ime, const QString &prezime, GlavniProzor2 *gp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetOsoba),
    _sifra(sifra),_x(x),_y(y),
    w(gp)
{
    //QString tmp(ime);
    //tmp.append(" ");
    //tmp.append(prezime);
    //ui->btnOsoba->setText(ime);
    ui->setupUi(this);
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

void WidgetOsoba::postaviImePrezime(const std::string &ip)
{
    QString q_ip = QString::fromStdString(ip);
    ui->btnOsoba->setText(q_ip);
}


void WidgetOsoba::on_btnOsoba_clicked()
{
    w->promeniSelektovanu(_sifra);
    w->popuniInformacije();
}

void WidgetOsoba::on_btnOsoba_pressed()
{
    //pocinjemo povezivanje sa drugom osobom - tj kreiranje relacije u zavisnosti od radio buttona
    //nece moci ovako jer se ovo desava i na clicked :P
    w->postaviSifru1(_sifra);
}

void WidgetOsoba::on_btnOsoba_released()
{
    //a na ovo kreiramo relaciju ako je sve bilo ok
    //- pozivamo konstruktor odgovarajuci iz engin-a,
    //a on vraca podatke i poziva iscrtavanje relacije

    //recimo

    w->postaviSifru2(_sifra);
    w->poveziOsobe();
}
/*
void WidgetOsoba::on_btnOsoba_toggled(bool checked)
{
    if (checked)
        GlavniProzor::promeniSelektovanu(_sifra);
    else
        GlavniProzor::promeniSelektovanu(-1);

    GlavniProzor::popuniInformacije();
        //std::cout<<"Radi"<<std::endl;
}
*/

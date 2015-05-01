#include "widgetosoba.h"
#include "ui_widgetosoba.h"

WidgetOsoba::WidgetOsoba(short int sifra, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetOsoba),
    _sifra(sifra)
{
    /*
    btnOsoba = new QPushButton(this);

    btnOsoba->setFlat(true);
    btnOsoba->setGeometry(this->geometry().x(), this->geometry().y(),
                          this->geometry().width(), this->geometry().height());
    btnOsoba->setText("");

    //connect(tbOsoba,SIGNAL(pressed()),this,SLOT(postavi_na_0()));

    connect(btnOsoba, SIGNAL(clicked()),this,SLOT(on_btnOsoba_clicked()));
    connect(btnOsoba, SIGNAL(pressed()),this,SLOT(on_btnOsoba_pressed()));
    connect(btnOsoba, SIGNAL(released()),this,SLOT(on_btnOsoba_released()));*/


    ui->setupUi(this);
}

WidgetOsoba::~WidgetOsoba()
{
    delete ui;
}

void WidgetOsoba::postaviImePrezime(const std::string &ip)
{
    QString q_ip = QString::fromStdString(ip);
    //btnOsoba->setText(q_ip);
    //btnOsoba->show();
}


void WidgetOsoba::on_btnOsoba_clicked()
{
    //ispisujemo informacije u osobi tamo sa leve strane

    //samo kako da odavde uticem na parent-a? Biso javljaj ako znas!

    //iz engina - nesto ovako : Osoba* poSifri(_sifra) ---> dobijemo podatke
    this->setToolTip("Ili da ovako ispisemo detalje?");
}

void WidgetOsoba::on_btnOsoba_pressed()
{
    //pocinjemo povezivanje sa drugom osobom - tj kreiranje relacije u zavisnosti od radio buttona
}

void WidgetOsoba::on_btnOsoba_released()
{
    //a na ovo kreiramo relaciju ako je sve bilo ok
    //- pozivamo konstruktor odgovarajuci iz engin-a,
    //a on vraca podatke i poziva iscrtavanje relacije

    //recimo
}

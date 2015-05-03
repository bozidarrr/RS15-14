#include "widgetosoba.h"
#include "ui_widgetosoba.h"
#include "GUI/glavniprozor.h"
#include <iostream>
#include <QtGui>
WidgetOsoba::WidgetOsoba(short int sifra, int x, int y,  GlavniProzor2 *gp, QWidget *parent) :
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

bool WidgetOsoba::sadrziTacku(int x, int y)
{
    bool rez = x >= _x
            && x <= _x + ui->ImeOsobe->width()
            && y >= _y
            && y <= _y + ui->ImeOsobe->height();
    return rez;

}

void WidgetOsoba::postaviImePrezime(const std::string &ip)
{
    QString q_ip = QString::fromStdString(ip);
    ui->ImeOsobe->setText(q_ip);
}

void WidgetOsoba::mousePressEvent(QMouseEvent *event)
{

      std::cout<<"pritisao misa na osobu "<<_sifra<<std::endl;
    if (event->button() == Qt::LeftButton) {
        QDrag *drag = new QDrag(this);
              QMimeData *mimeData = new QMimeData;
              mimeData->setText(QString(_sifra));
              drag->setMimeData(mimeData);
              w->postaviSifru1(_sifra);
              drag->exec();


    }

}

void WidgetOsoba::dragEnterEvent(QDragEnterEvent *event)
{
           event->acceptProposedAction();
}


void WidgetOsoba::dropEvent(QDropEvent *event)
{
  w->postaviSifru2(_sifra);
  w->otpustenaOsoba();
    event->acceptProposedAction();

}


void WidgetOsoba::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout<<"pustio misa sa osobe "<<_sifra<<std::endl;
 /*   if (event->button() == Qt::LeftButton) {
  //     emit otpusten();
    }*/

}




/*
void WidgetOsoba::on_btnOsoba_clicked()
{
    if (w->Povezivati())
    {
        //std::cout<<"ovo znaci da treba oznaciti prvu i drugu"<<std::endl;
        if (w->Sifra1() > 0 && w->Sifra1() != _sifra && w->Sifra2() < 0)
        {
            std::cout<<"if"<<std::endl;
            w->postaviSifru2(_sifra);
            w->poveziOsobe();
        }
        if (w->Sifra1() < 0)
            w->postaviSifru1(_sifra);
    }
    else
    {
        w->promeniSelektovanu(_sifra);
        w->popuniInformacije();
    }
}
*//*
void WidgetOsoba::on_btnOsoba_pressed()
{
    //pocinjemo povezivanje sa drugom osobom - tj kreiranje relacije u zavisnosti od radio buttona
    //nece moci ovako jer se ovo desava i na clicked :P
   // w->postaviSifru1(_sifra);
}
*//*
void WidgetOsoba::on_btnOsoba_released()
{
    //a na ovo kreiramo relaciju ako je sve bilo ok
    //- pozivamo konstruktor odgovarajuci iz engin-a,
    //a on vraca podatke i poziva iscrtavanje relacije
    //mozda bi ovde mogla umesto ovaj metod sto pravis da predefinises void releasemouse()
    //recimo

   // w->postaviSifru2(_sifra);
   // w->poveziOsobe();
}*/
//bool WidgetOsoba::operator ==(const WidgetOsoba& druga)const{
//    //za proveru jednakosti 2 widgeta dovoljno je da proverimo njihove sifre jer je to jedinstveni identifikator
//    if(_sifra==druga._sifra)
//        return true;
//    return false;
//}

//void WidgetOsoba::on_btnOsoba_toggled(bool checked)
//{
//    //mislila sam na ovaj signal da uklanjamo osobu iz stabla
//    if (checked)
//        w->ukloniOsobu(this);
//    std::cout<<"uklanjamo"<<std::endl;
//}

#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "unetiosobu.h"
#include <QGraphicsScene>

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
    QPixmap osobapix(":/images/images/Ellipse-tool-icon.png");
      QPixmap mzpix(":/images/images/heart.png");
      QPixmap bspix(":/images/images/children.png");
       QPixmap rdpix(":/images/images/index.jpeg");

      QToolBar *toolbar= addToolBar("main toolbar");
      toolbar->addAction(QIcon(osobapix), "Osoba", ui->Stablo,"");
      toolbar->addAction(QIcon(mzpix), "Supruznici",ui->Stablo,"");
      toolbar->addAction(QIcon(bspix), "Brat - Sestra",ui->Stablo,"");
      toolbar->addAction(QIcon(rdpix), "Roditelj - dete",ui->Stablo,"");


      toolbar->addSeparator();
}


GlavniProzor::~GlavniProzor()
{
    delete ui;
}

#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "unetiosobu.h"
#include <QGraphicsScene>

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
    QPixmap osobapix("Ellipse-tool-icon.png");
      QPixmap mzpix("heart.png");
      QPixmap bspix("children.png");
       QPixmap rdpix("index.jpeg");

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

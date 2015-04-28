#include "unetiosobu.h"
#include "ui_unetiosobu.h"

Unetiosobu::Unetiosobu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Unetiosobu)
{
    ui->setupUi(this);
    connect(ui->Prihvati,SIGNAL(clicked()),this,SLOT(NapraviOsobu()));
    connect(ui->Odustani,SIGNAL(clicked()),this,SLOT(Odustani()));
}

void Unetiosobu::NapraviOsobu(){
   // novaO=Osoba(ui->ImeTF->text(),ui->PrezimeTF->text(),ui->DatR->text(),ui->DatS->text(),ui->Muski->isChecked()? "M" : "Z");
    this->hide();
    //metod nam pravi novu osobu i nakon toga zatvara prozor za unos osobe
    ui->ImeTF->setText(QString(""));
     ui->PrezimeTF->setText(QString(""));
}
void Unetiosobu::Odustani(){
    this->hide();
    ui->ImeTF->setText(QString(""));
     ui->PrezimeTF->setText(QString(""));
}


Unetiosobu::~Unetiosobu()
{
    delete ui;
}

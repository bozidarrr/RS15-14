#include "unetiosobu.h"
#include "ui_unetiosobu.h"

Unetiosobu::Unetiosobu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Unetiosobu)
{
    ui->setupUi(this);
}
/*
Unetiosobu::NapraviOsobu(Osoba & novaO){
    novaO=new Osoba(ui->ImeTF->text(),ui->PrezimeTF->text(),ui->DatR->text(),ui->DatS->text(),ui->Muski->isChecked()? "M" : "Z");
    close();
    //metod nam pravi novu osobu i nakon toga zatvara prozor za unos osobe
}
*/

Unetiosobu::~Unetiosobu()
{
    delete ui;
}

#include "unetiosobu.h"
#include "ui_unetiosobu.h"

Unetiosobu::Unetiosobu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Unetiosobu)
{
    ui->setupUi(this);
    connect(ui->Prihvati,SIGNAL(clicked()),this,SLOT(Procitaj()));
    connect(ui->Odustani,SIGNAL(clicked()),this,SLOT(Odustani()));
}

void Unetiosobu::Procitaj(){
    m_ime=ui->ImeTF->text();
    m_prezime= ui->PrezimeTF->text();
    m_datRodj=ui->DatR->text();
    m_datSmrti=ui->DatS->text();
    pol=ui->Muski->isChecked();

    this->hide();

    ui->ImeTF->setText(QString(""));
     ui->PrezimeTF->setText(QString(""));
}
void Unetiosobu::Odustani(){
    m_ime=QString("");
    m_prezime= QString("");
    m_datRodj=QString("");
    m_datSmrti=QString("");
    pol=false;
    this->hide();
    ui->ImeTF->setText(QString(""));
    ui->PrezimeTF->setText(QString(""));
}
void Unetiosobu::Ponisti(){
    m_ime=QString("");
    m_prezime= QString("");
    m_datRodj=QString("");
    m_datSmrti=QString("");
    pol=false;
}

Unetiosobu::~Unetiosobu()
{
    delete ui;
}

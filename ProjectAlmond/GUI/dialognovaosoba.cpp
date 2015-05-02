#include "GUI/dialognovaosoba.h"
#include "ui_dialognovaosoba.h"
#include <QRegExp>
#include <QRegExpValidator>

DialogNovaOsoba::DialogNovaOsoba(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNovaOsoba)
{
    ui->setupUi(this);
    setModal(true);

    popuniDugmice();
    postaviProvere();

}

DialogNovaOsoba::~DialogNovaOsoba()
{
    delete ui;
}

void DialogNovaOsoba::popuniPodatke(QString &ime, QString &prezime, QString &pol, QDate &rodjenje, QDate &smrt)
{
//    ime = new QString(ui->unosIme->text());
//    prezime = new QString(ui->unosPrezime->text());
//    pol = new QString(ui->unosPol->text());
//    rodjenje = new QDate(ui->unosRodjenje->date());
//    if (ui->chkSmrt->checkState())
//        smrt = new QDate(ui->UnosSmrt->date());
//    else
//        smrt = nullptr;
    ime = ui->unosIme->text();
    prezime = ui->unosPrezime->text();
    pol = ui->unosPol->text();
    rodjenje = ui->unosRodjenje->date();
    if (ui->chkSmrt->checkState())
           smrt = ui->UnosSmrt->date();
//      else
//           smrt = NULL;

}

void DialogNovaOsoba::promenaUnosa()
{
    ok->setEnabled(ui->unosIme->hasAcceptableInput() &&
                   ui->unosPrezime->hasAcceptableInput() &&
                   ui->unosPol->hasAcceptableInput());
}

void DialogNovaOsoba::popuniDugmice()
{
    ok = new QPushButton(tr("OK"));
    ok->setEnabled(false);
    cancel = new QPushButton(tr("Ponisti"));

    ui->buttonBox->addButton(ok, QDialogButtonBox::AcceptRole);
    ui->buttonBox->addButton(cancel, QDialogButtonBox::RejectRole);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    ok->show();
    cancel->show();
}

void DialogNovaOsoba::postaviProvere()
{
    QRegExp ime("[A-Za-z]+");
    QRegExp prezime("[A-Za-z]+");
    QRegExp pol(tr("M|m|Z|z"));
    ui->unosIme->setValidator(new QRegExpValidator(ime, this));
    ui->unosPrezime->setValidator(new QRegExpValidator(prezime, this));
    ui->unosPol->setValidator(new QRegExpValidator(pol, this));

    connect(ui->unosIme,SIGNAL(textChanged(QString)),this,SLOT(promenaUnosa()));
    connect(ui->unosPrezime,SIGNAL(textChanged(QString)),this,SLOT(promenaUnosa()));
    connect(ui->unosPol,SIGNAL(textChanged(QString)),this,SLOT(promenaUnosa()));
}

void DialogNovaOsoba::on_chkSmrt_stateChanged(int arg1)
{
    ui->UnosSmrt->setEnabled(ui->chkSmrt->checkState());
}

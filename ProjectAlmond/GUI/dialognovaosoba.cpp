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



}

DialogNovaOsoba::~DialogNovaOsoba()
{
    delete ui;
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
    cancel = new QPushButton(tr("Ponisti"));

    ui->buttonBox->addButton(ok, QDialogButtonBox::AcceptRole);
    ui->buttonBox->addButton(cancel, QDialogButtonBox::RejectRole);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
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

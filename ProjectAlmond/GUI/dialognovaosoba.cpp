#include "GUI/dialognovaosoba.h"
#include "ui_dialognovaosoba.h"
//#include <QRegExp>
//#include <QRegExpValidator>

DialogNovaOsoba::DialogNovaOsoba(bool saRelacijom, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNovaOsoba),
    _saRelacijom(saRelacijom)
{
    ui->setupUi(this);
    setModal(true);

    popuniDugmice();
    postaviProvere();
    ui->chkNepoznatDR->setToolTip(tr("Datum rodjenja nije poznat ili ne zelite da ga unosite"));
    ui->chkSmrt->setToolTip(tr("Osoba je ziva, ili je datum smrti nepoznat"));
    connect(ui->chkSmrt,SIGNAL(stateChanged(int)),this,SLOT(on_chkSmrt_stateChanged(int)));
    connect(ui->chkNepoznatDR,SIGNAL(stateChanged(int)),this,SLOT(on_chkNepoznatDR_stateChanged(int)));

    if(_saRelacijom)
    {
        labelaTrivija = new QLabel("Trivije o relaciji");
        ui->hlTrivija->addWidget(labelaTrivija);
        trivija = new QTextEdit();
        ui->hlTrivija->addWidget(trivija, 1);
    }
}

DialogNovaOsoba::~DialogNovaOsoba()
{
    delete ui;
}

void DialogNovaOsoba::popuniPodatke(QString &ime, QString &prezime, QString &pol, QDate &rodjenje, QDate &smrt, QString &triv)
{
    ime = ui->unosIme->text();
    prezime = ui->unosPrezime->text();
    pol = ui->unosPol->text();
    if(ui->chkNepoznatDR->isChecked() == false)
        rodjenje = ui->unosRodjenje->date();
    if (ui->chkSmrt->isChecked() == false)
           smrt = ui->UnosSmrt->date();
    if(_saRelacijom)
        triv = trivija->toPlainText();
    else
        triv = "";
}

void DialogNovaOsoba::popuniPodatke(std::string &ime, std::string &prezime, char &pol,
                                    std::string &rodjenje, std::string &smrt, std::string &trivija)
{
    if (ui->checkBox->isChecked())
        return;

    QString _ime, _prezime, _pol, _trivija;
    QDate _rodjenje, _smrt;

    popuniPodatke(_ime, _prezime, _pol, _rodjenje, _smrt, _trivija);

    ime = _ime.QString::toStdString();
    prezime = _prezime.QString::toStdString();
    pol = _pol.toStdString().c_str()[0];
    if(!_rodjenje.isValid())
        rodjenje="";
    else
        rodjenje = _rodjenje.toString("dd.MM.yyyy.").toStdString();
    if (!_smrt.isValid())
        smrt = "";
    else
        smrt = _smrt.toString("dd.MM.yyyy.").toStdString();
    trivija = _trivija.toStdString();
}

void DialogNovaOsoba::promenaUnosa()
{
    ok->setEnabled((ui->unosIme->hasAcceptableInput() &&
                   ui->unosPrezime->hasAcceptableInput() &&
                   ui->unosPol->hasAcceptableInput())
                   || ui->checkBox->isChecked());
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
    QRegExp ime("[A-Z][A-Za-z ]+");
    QRegExp prezime("[A-Z][A-Za-z ]+");
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
    ui->UnosSmrt->setDisabled(arg1);
}
void DialogNovaOsoba::on_chkNepoznatDR_stateChanged(int arg1)
{
    ui->unosRodjenje->setDisabled(arg1);
}

void DialogNovaOsoba::on_checkBox_stateChanged(int arg1)
{
    ui->unosIme->setDisabled(arg1);
    ui->unosPrezime->setDisabled(arg1);
    ui->unosRodjenje->setDisabled(ui->chkNepoznatDR->isChecked() || arg1);
    ui->UnosSmrt->setDisabled(ui->chkSmrt->isChecked() || arg1);
    ui->chkNepoznatDR->setDisabled(arg1);
    ui->chkSmrt->setDisabled(arg1);
    ui->unosPol->setDisabled(arg1);
    if (_saRelacijom)
        trivija->setDisabled(arg1);
    promenaUnosa();
}

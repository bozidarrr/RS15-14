#include "GUI/dijalogizmenaosobe.h"
#include "ui_dijalogizmenaosobe.h"

DijalogIzmenaOsobe::DijalogIzmenaOsobe(Osoba *osoba, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DijalogIzmenaOsobe)

{
    ui->setupUi(this);
    setModal(true);
    _osoba = osoba;
    popuniDugmice();
    popuniPolja();
}

DijalogIzmenaOsobe::~DijalogIzmenaOsobe()
{
    delete ui;
}

void DijalogIzmenaOsobe::popuniDugmice()
{
    ok = new QPushButton(tr("Primeni izmene"));
    cancel = new QPushButton(tr("Ponisti"));
    cancel->setToolTip(tr("Nijedna izmena nece ostati zapamcena."));

    ui->buttonBox->addButton(ok, QDialogButtonBox::AcceptRole);
    ui->buttonBox->addButton(cancel, QDialogButtonBox::RejectRole);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ok, SIGNAL(clicked()), this, SLOT(primeniIzmene()));

    ok->show();
    cancel->show();
}

void DijalogIzmenaOsobe::popuniPolja()
{
    ui->unosIme->setPlaceholderText(QString::fromStdString(_osoba->Ime()));
    ui->unosPrezime->setPlaceholderText(QString::fromStdString(_osoba->Prezime()));
    //ui->unosRodjenje->setDate(_osoba->_datumRodjenja);
    //ui->UnosSmrt->setDate(_osoba->_datumSmrti);
    //ui->unosPol->setPlaceholderText(QString::fromStdString(tmp));
}

void DijalogIzmenaOsobe::primeniIzmene()
{
    std::cout << "treba uneti izmene u stablo" << std::endl;
    //nemamo settere u osobi
}

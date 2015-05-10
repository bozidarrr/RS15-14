#include "GUI/dijalogizmenaosobe.h"
#include "ui_dijalogizmenaosobe.h"

DijalogIzmenaOsobe::DijalogIzmenaOsobe(short sifra, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DijalogIzmenaOsobe),
    _sifra(sifra)
{
    ui->setupUi(this);
    setModal(true);
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
    //ok->setEnabled(true);
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
    ui->unosIme->setPlaceholderText("Staro ime (iz porodicnog stabla)");
    //...
}

void DijalogIzmenaOsobe::primeniIzmene()
{
    std::cout << "treba uneti izmene u stablo" << std::endl;
}

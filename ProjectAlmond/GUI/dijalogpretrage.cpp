#include "GUI/dijalogpretrage.h"
#include "ui_dijalogpretrage.h"
#include <QPushButton>
#include <QDebug>

DijalogPretrage::DijalogPretrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DijalogPretrage)
{
    ui->setupUi(this);

    ui->unosDatum->setHidden(true);
    connect(ui->IzaberiOpciju, SIGNAL(currentIndexChanged(int)), this, SLOT(tekstIliDatum()));
    //connect(ok, SIGNAL(clicked()), this, SLOT(procitajPodatke()));
}

DijalogPretrage::~DijalogPretrage()
{
    delete ui;
}

void DijalogPretrage::procitajPodatke(int &opcija, int &kriterijum, QString &podatak)
{
    opcija = ui->IzaberiOpciju->currentIndex();//0 ime, 1 prezime, 2 datum rodjenja, 3 datum smrti, 4 pol NAPRAVITI NEKI ENUM ILI NESTO
    kriterijum = ui->IzaberiKriterijum->currentIndex();//< = >
    if (opcija == 2 || opcija == 3)
        podatak = ui->unosDatum->date().toString("dd.MM.yyyy.");
    else
        podatak = ui->unosText->text();
}

void DijalogPretrage::tekstIliDatum()
{
    int k = ui->IzaberiOpciju->currentIndex();
    qDebug() << k;
    ui->unosDatum->setVisible(k == 3 || k == 2);
    ui->unosText->setVisible(k == 0 || k == 1 || k == 4);
}

void DijalogPretrage::popuniDugmice()
{
    ok = new QPushButton(tr("OK"));
    ok->setEnabled(false);
    cancel = new QPushButton(tr("Ponisti"));

    ui->buttonBox->addButton(ok, QDialogButtonBox::AcceptRole);
    ui->buttonBox->addButton(cancel, QDialogButtonBox::RejectRole);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

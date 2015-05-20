#include "GUI/dijalogrelacija.h"
#include "ui_dijalogrelacija.h"

DijalogRelacija::DijalogRelacija(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DijalogRelacija)
{
    ui->setupUi(this);

    popuniDugmice();
}

DijalogRelacija::~DijalogRelacija()
{
    delete ui;
}

void DijalogRelacija::popuniPodatke(std::string &trivija)
{
    trivija = ui->unosTrivija->toPlainText().toStdString();
}

void DijalogRelacija::popuniDugmice()
{
    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Ponisti"));

    ui->buttonBox->addButton(ok, QDialogButtonBox::AcceptRole);
    ui->buttonBox->addButton(cancel, QDialogButtonBox::RejectRole);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

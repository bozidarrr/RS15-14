#include "dialogpretrage.h"
#include "ui_dialogpretrage.h"

DialogPretrage::DialogPretrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPretrage)
{
    ui->setupUi(this);
    setModal(true);
    setWindowTitle(tr("Pretraga"));
    ponisti = new QPushButton(tr("Ponisti"));
    ok = new QPushButton(tr("Ok"));
    ui->buttonBox->addButton(ok, QDialogButtonBox::AcceptRole);
    ui->buttonBox->addButton(ponisti, QDialogButtonBox::RejectRole);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ok, SIGNAL(clicked()), this, SLOT(procitajPodatke()));
}
bool DialogPretrage::procitajPodatke(){
//    _ime=QString();
//    _prezime=QString();
//    _datumRodj=QDate();
//    _datumSmr=QDate();
//    _pol=QChar();
//    if(ui->IzaberiOpciju->currentIndex()==0){
//        //vrsimo pretragu po imenu
//        _ime=ui->PoljeIme->text();

//    }
//    if(ui->IzaberiOpciju->currentIndex()==1){
//        //vrsimo pretragu po prezimenu
//        _prezime=ui->PoljePrezime->text();
//    }
//    if(ui->IzaberiOpciju->currentIndex()==2){
//        //vrsimo pretragu po datumu rodjenja
//        _datumRodj=ui->datRodj->date();
//    }
//    if(ui->IzaberiOpciju->currentIndex()==3){
//        //vrsimo pretragu po datumu smrti
//        _datumSmr=ui->datSmrti->date();
//    }
//    if(ui->IzaberiOpciju->currentIndex()==4){
//        //vrsimo pretragu po datumu smrti
//        _pol=ui->PoljePol->text().at(0);
//    }
//    _kriterijum=ui->IzaberiKriterijum->currentIndex();
    return true;
}

DialogPretrage::~DialogPretrage()
{
    delete ui;
}

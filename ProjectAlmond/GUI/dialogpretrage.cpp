#include "dialogpretrage.h"
#include "ui_dialogpretrage.h"

DialogPretrage::DialogPretrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPretrage)
{
    ui->setupUi(this);
    connect(ui->Odustanibtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->Prihvatibtn,SIGNAL(clicked()),this,SLOT(izvrsiPretragu()));
}
bool DialogPretrage::izvrsiPretragu(){
    _ime=QString();
    _prezime=QString();
    _datumRodj=QDate();
    _datumSmr=QDate();
    _pol=QChar();
    if(ui->IzaberiOpciju->currentIndex()==0){
        //vrsimo pretragu po imenu
        _ime=ui->PoljeIme->text();

    }
    if(ui->IzaberiOpciju->currentIndex()==1){
        //vrsimo pretragu po prezimenu
        _prezime=ui->PoljePrezime->text();
    }
    if(ui->IzaberiOpciju->currentIndex()==2){
        //vrsimo pretragu po datumu rodjenja
        _datumRodj=ui->datRodj->date();
    }
    if(ui->IzaberiOpciju->currentIndex()==3){
        //vrsimo pretragu po datumu smrti
        _datumSmr=ui->datSmrti->date();
    }
    if(ui->IzaberiOpciju->currentIndex()==4){
        //vrsimo pretragu po datumu smrti
        _pol=ui->PoljePol->text().at(0);
    }
    _kriterijum=ui->IzaberiKriterijum->currentIndex();
    return true;
}

DialogPretrage::~DialogPretrage()
{
    delete ui;
}

#include "GUI/glavniprozor2.h"
#include "ui_glavniprozor2.h"
#include "GUI/dialognovaosoba.h"
#include <algorithm>
GlavniProzor2::GlavniProzor2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor2)
{
    ui->setupUi(this);

    //    _sifra1 = -1;
    //    _sifra2 = -1;


    QIcon icon(":images/ProjectAlmond.ico");
    this->setWindowIcon(icon);
    this->setWindowTitle("Project Almond");

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("pera", "detlic", 'm', "12.04.1963.");


    kreirajToolbar();
    krerajMestoZaInfo();
    kreirajPlatnoZaCrtanje();
    //kreirajOpcije();
//        FilterObject *f = new FilterObject(stabloOkvir);
        QPushButton *b1 = new QPushButton("1", stabloOkvir);
         QPushButton *b2 = new QPushButton("2", stabloOkvir);
         b2->move(250,100);
       b1->installEventFilter(filter);
       b1->show();
       b2->installEventFilter(filter);
       b2->show();


}

GlavniProzor2::~GlavniProzor2()
{
    delete ui;

}

void GlavniProzor2::promeniSelektovanu(short novaSifra)
{
    _selektovanaSifra = novaSifra;
}

void GlavniProzor2::popuniInformacije()
{
    if (_selektovanaSifra > 0)
    {
        Osoba *osoba = stablo->nadjiOsobuPoSifri(_selektovanaSifra);
        ui->label->setText(QString::fromStdString("<H1>"+osoba->Ime()+"<H1/>\n"+osoba->Prezime()));//i sve ostalo
    }
}

void GlavniProzor2::kreirajPlatnoZaCrtanje()
{
    stabloOkvir=new okvirStabla(ui->stabloFrame);

    connect(stabloOkvir,SIGNAL(kliknut()),this,SLOT(kliknutoPlatno()));

    filter = new FilterObject(stabloOkvir);

}

void GlavniProzor2::kreirajOpcije()
{






}

 QToolButton* GlavniProzor2::kreirajJedanAlat(QToolButton * alat, const char* ime,const char* info)
 {
alat=new QToolButton();
alat->setCheckable(true);
alat->setFocusPolicy(Qt::NoFocus);
alat->setToolTip(info);
std::string ikonica(":/images/images/"+std::string(ime)+".ico");
const char* pocetak=&ikonica[0];
alat->setIcon(QIcon(pocetak));
alat->setIconSize(QSize(200,200));
return alat;
 }


void GlavniProzor2::kreirajToolbar()
{

    toolbar = addToolBar(tr("Alati"));

    grpToolBar=new QButtonGroup();

    tbOsoba=kreirajJedanAlat(tbOsoba,"NovaOsoba","Kreirajte novu osobu");
    tbMuzZena=kreirajJedanAlat(tbMuzZena,"RelacijaSupruznici","Kreirajte novi odnos dva supruznika");
    tbBratSestra=kreirajJedanAlat(tbBratSestra,"RelacijaBratSestra","Kreirajte novi odnos dvoje brace/sestara");
    tbRoditeljDete=kreirajJedanAlat(tbRoditeljDete,"RelacijaDete","Kreirajte novi odnos tipa roditelj-dete");
    tbPomeranje=kreirajJedanAlat(tbPomeranje,"Pomeri","Pomerite rucicom odabranu osobu ili relaciju na crtezu");
    tbDetalji=kreirajJedanAlat(tbDetalji,"Informacija","Detalji o odabranoj osobi");
    tbMenjaj=kreirajJedanAlat(tbMenjaj,"","Izmenite podatke o odabranoj osobi ili relaciji");
    tbBrisi=kreirajJedanAlat(tbBrisi,"Ukloni","Obrisite osobu ili relaciju iz stabla");

    /*tbOsoba = new QToolButton();
    tbOsoba->setCheckable(true);
    tbOsoba->setToolTip(tr("Kreirajte novu osobu"));
    tbOsoba->setFocusPolicy(Qt::NoFocus);
    tbOsoba->setIcon(QIcon(":/images/images/NovaOsoba.ico"));
    tbOsoba->adjustSize();
    tbOsoba->setShortcut(tr("ALT+N"));

    tbMuzZena = new QToolButton();
    tbMuzZena->setCheckable(true);
    tbMuzZena->setToolTip(tr("Kreirajte novi odnos dva supruznika"));
    tbMuzZena->setFocusPolicy(Qt::NoFocus);
    tbMuzZena->setIcon(QIcon(":/images/images/RelacijaSupruznici.ico"));
    tbMuzZena->adjustSize();
    tbMuzZena->setShortcut(tr("ALT+V"));

    tbBratSestra = new QToolButton();
    tbBratSestra->setCheckable(true);
    tbBratSestra->setToolTip(tr("Kreirajte novi odnos dvoje brace/sestara"));
    tbBratSestra->setFocusPolicy(Qt::NoFocus);
    tbBratSestra->setIcon(QIcon(":/images/images/RelacijaBratSestra.ico"));
    tbBratSestra->adjustSize();
    tbBratSestra->setShortcut(tr("ALT+B"));

    tbRoditeljDete = new QToolButton();
    tbRoditeljDete->setCheckable(true);
    tbRoditeljDete->setToolTip(tr("Kreirajte novi odnos tipa roditelj-dete"));
    tbRoditeljDete->setFocusPolicy(Qt::NoFocus);
    tbRoditeljDete->setIcon(QIcon(":/images/images/RelacijaDete.ico"));
    tbRoditeljDete->adjustSize();
    tbRoditeljDete->setShortcut(tr("ALT+M"));

    tbPomeranje = new QToolButton();
    tbPomeranje->setToolTip(tr("Pomerite rucicom odabranu osobu ili relaciju na crtezu"));
    tbPomeranje->setCheckable(true);
    tbPomeranje->setFocusPolicy(Qt::NoFocus);
    tbPomeranje->setIcon(QIcon(":/images/images/Pomeri.ico"));
    tbPomeranje->adjustSize();
    tbPomeranje->setShortcut(tr("ALT+P"));

    tbDetalji = new QToolButton();
    tbDetalji->setCheckable(true);
    tbDetalji->setToolTip(tr("Detalji o odabranoj osobi"));
    tbDetalji->setFocusPolicy(Qt::NoFocus);
    tbDetalji->setIcon(QIcon(":/images/images/Informacija.ico"));
    tbDetalji->adjustSize();
    tbDetalji->setShortcut(tr("ALT+I"));

    tbMenjaj = new QToolButton();
    tbMenjaj->setCheckable(true);
    tbMenjaj->setText("M");
    tbMenjaj->setToolTip(tr("Izmenite podatke o odabranoj osobi ili relaciji"));
    tbMenjaj->setFocusPolicy(Qt::NoFocus);
    // tbMenjaj->setIcon(QIcon(":/images/images/Menjaj.ico"));
    tbMenjaj->adjustSize();
    tbMenjaj->setShortcut(tr("ALT+U"));


    tbBrisi = new QToolButton();
    tbBrisi->setCheckable(true);
    tbBrisi->setToolTip(tr("Obrisite osobu ili relaciju iz stabla"));
    tbBrisi->setFocusPolicy(Qt::NoFocus);
    tbBrisi->setIcon(QIcon(":/images/images/Ukloni.ico"));
    tbBrisi->adjustSize();
    tbBrisi->setShortcut(tr("ALT+R"));*/

    grpToolBar->addButton(tbOsoba);
    grpToolBar->addButton(tbRoditeljDete);
    grpToolBar->addButton(tbBratSestra);
    grpToolBar->addButton(tbMuzZena);
    grpToolBar->addButton(tbPomeranje);
    grpToolBar->addButton(tbDetalji);
    grpToolBar->addButton(tbMenjaj);
    grpToolBar->addButton(tbBrisi);

   /* for(QObject* tb : grpToolBar->buttons())
    {
        toolbar->addWidget((QWidget *)tb);
    }*/

    toolbar->addWidget(tbOsoba);
    toolbar->addSeparator();
    toolbar->addWidget(tbMuzZena);
    toolbar->addWidget(tbBratSestra);
    toolbar->addWidget(tbRoditeljDete);
    toolbar->addSeparator();
    toolbar->addWidget(tbPomeranje);
    toolbar->addWidget(tbDetalji);
    toolbar->addWidget(tbMenjaj);
    toolbar->addWidget(tbBrisi);

    QDockWidget *alati = new QDockWidget(tr("Alati"));
    alati->setWidget(toolbar);//i recimo
    alati->setAllowedAreas(Qt::TopDockWidgetArea
                           | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::TopDockWidgetArea, alati);
    //delete alati;
}

void GlavniProzor2::krerajMestoZaInfo()
{
    QDockWidget *info = new QDockWidget(tr("Informacije"));
    info->setWidget(ui->label);//i recimo
    ui->label->setToolTip("Sredicu ovo :)");
    info->setAllowedAreas(Qt::RightDockWidgetArea
                          | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, info);
    //delete info;
}

void GlavniProzor2::kliknutoPlatno()
{


    if(tbOsoba->isChecked()){
        tbOsoba->setChecked(false);
        dodajNovuOsobu(stabloOkvir->X1(),stabloOkvir->Y1());

    }
    else if(tbBratSestra->isChecked()){
    }
    else if(tbMuzZena->isChecked()){
        //poveziOsobe();

    }
    else if(tbRoditeljDete->isChecked()){

    }
    else if(tbDetalji->isChecked()){
        //std::cout<<"sto ne pise"<<std::endl;
        //popuniInformacije();

    }
    else if(tbPomeranje->isChecked()){

    }

    tbDetalji->setChecked(true);
}

void GlavniProzor2::dodajNovuOsobu(int x,int y)
{
    DialogNovaOsoba *d = new DialogNovaOsoba(this);
    if (d->exec())
    {
        QString ime, prezime;
        QString pol;
        char p=pol.toStdString().c_str()[0];//konvertovala sam string u nisku karaktera i uzela prvi karakter
        QDate rodjenje, smrt;
        d->popuniPodatke(ime, prezime, pol, rodjenje, smrt);
        std::string r = rodjenje.toString("dd.MM.yyyy.").toStdString();
        std::string s; //preimenovala sam jer ti se isto zovu i dodaj novu osobu i datum smrti
        if (!smrt.isValid())
            s = "";
        else
            s = smrt.toString("dd.MM.yyyy.").toStdString();
        short int novaSifra = stablo->DodajOsobu(ime.toStdString(),
                                                 prezime.toStdString(), p, r, s); //Ubacila sam prvi karakter iz QStringa za pol
        if (novaSifra < 0)
            //nastao problem, obavestavamo korisnika, nece biti ovako naravno
            ui->label->setText("Neuspelo dodavanje");//OVO DA SE PRETVORI U OBAVESTENJE U STATUS BARU KADA GA NAPRAVIMO
        else
            ui->label->setText("Uspelo");

        WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra,x,y, this, ui->stabloFrame);
        std::string tmp = ime.toStdString() + " " + prezime.toStdString();
        novaOsoba->postaviImePrezime(tmp);
        novaOsoba->move(novaOsoba->X(),novaOsoba->Y());

  //      connect(novaOsoba,SIGNAL(stisnut(int)),this,SLOT(stisnutaOsoba(int)));
   //     connect(novaOsoba,SIGNAL(otpusten()),this,SLOT(otpustenaOsoba()));

        //novaOsoba->installEventFilter(filter);

        novaOsoba->show();
        _osobe.push_back(novaOsoba);

        _sifra1 = -1;
        _sifra2 = -1;

    }

    delete d;
}

//ovde se ispituju akcije kada je stisnut mis na nekoj osobi. osoba kada je pritisnuta odaje svoju sifru (kao i inace u zivotu :P)
/*void GlavniProzor2::stisnutaOsoba(int sifra)
{
    // std::cout<<"mhm stisnut"<<stablo->nadjiOsobuPoSifri(sifra)->Ime()<<std::endl;
    if(tbMuzZena->isChecked())
        postaviSifru1(sifra);
    else
        postaviSifru1(-1);
}*/

void GlavniProzor2::otpustenaOsoba()
{
    if(tbMuzZena->isChecked() && !(_sifra1<0)&&!(_sifra2<0)){
         std::cout<<"prva sifra: "<<_sifra1<<std::endl<<"druga sifra: "<<_sifra2<<std::endl;
        if(_sifra1!=_sifra2){//std::cout<<"Pravim novu relaciju"<<std::endl;
            short novaRelacija=stablo->PoveziOsobe(_sifra1,_sifra2,Odnos::SUPRUZNIK);
            std::cout<<"Sifra nove relacije je "<< novaRelacija <<std::endl;
        }
    }
    postaviSifru1(-1);
    postaviSifru2(-1);

}

void GlavniProzor2::kliknutaRelacija()
{

}


void GlavniProzor2::postaviSifru1(short nova)
{
    _sifra1 = nova;
}

void GlavniProzor2::postaviSifru2(short nova)
{
    _sifra2 = nova;
}

short GlavniProzor2::Sifra1() const
{
    return _sifra1;
}

short GlavniProzor2::Sifra2() const
{
    return _sifra2;
}

bool GlavniProzor2::Povezivati() const
{
    return tbBratSestra->isChecked() || tbRoditeljDete->isChecked()
            || tbMuzZena->isChecked();
}

void GlavniProzor2::poveziOsobe()
{
    //mislim da ovo moze mnogo bolje da se uradi ali da probamo ovako
    std::cout<<_sifra1<<" "<<_sifra2<<std::endl;
    if (_sifra1 > 0 && _sifra2 > 0 && _sifra1 != _sifra2)
    {
        std::cout<<"Povezuje 2 osobe"<<std::endl;
        //short sifraRelacije = stablo->PoveziOsobe(_sifra1, _sifra2, Odnos::SUPRUZNIK);
    }
    else
        std::cout<<"nesto ne valja"<<std::endl;//neki dijalog da nije kako treba

    //zapravo bice dovoljno samo
    /*
        short sifraRelacije = stablo->PoveziOsobe(_sifra1, _sifra2, Odnos::SUPRUZNIK);
        odnos cemo naci lako koji je
        if sifraRelacije < 0 greska
        else
        cuvamo u vektor,
        pravimo widget za relaciju i iscrtavamo ga na sredini
        tu negde pozivamo i dijalog za relaciju
    */

    //na kraju resetujemo sifre na -1
    _sifra1 = -1;
    _sifra2 = -1;
    std::cout<<_sifra1<<" "<<_sifra2<<std::endl;
}

//void GlavniProzor2::ukloniOsobu(WidgetOsoba *o){
//    auto osoba=_osobe.begin();
//    for(;osoba!=_osobe.end();osoba++){
//        if((*o)==*(*osoba)){
//             bool uspelo=stablo->UkloniOsobuPoSifri(o->Sifra());
//             if(uspelo){
//                _osobe.erase(osoba);

//                o->hide();
//             }
//            //treba da sakrijemo i sve njene veze

//        }
//    }
//}

short int GlavniProzor2::_selektovanaSifra = -1;
short int GlavniProzor2::_sifra1 = -1;
short int GlavniProzor2::_sifra2 = -1;

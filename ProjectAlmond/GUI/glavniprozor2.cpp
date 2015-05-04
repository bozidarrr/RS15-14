#include "GUI/glavniprozor2.h"
#include "ui_glavniprozor2.h"
#include "GUI/dialognovaosoba.h"
#include <algorithm>
GlavniProzor2::GlavniProzor2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor2)
{
    ui->setupUi(this);

    QIcon icon(":images/ProjectAlmond.ico");
    this->setWindowIcon(icon);
    this->setWindowTitle("Project Almond");

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("pera", "detlic", 'm', "12.04.1963.");


    kreirajToolbar();
    krerajMestoZaInfo();
    kreirajPlatnoZaCrtanje();
    //kreirajOpcije();

    WidgetOsoba *w1 = new WidgetOsoba(1,12,12,this,stabloOkvir);
        WidgetOsoba *w2 = new WidgetOsoba(2,50,50,this,stabloOkvir);

        w1->move(12,12);
        w2->move(50,50);
        w1->installEventFilter(filter);
        w2->installEventFilter(filter);


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
    tbMenjaj=kreirajJedanAlat(tbMenjaj,"Menjaj","Izmenite podatke o odabranoj osobi ili relaciji");
    tbBrisi=kreirajJedanAlat(tbBrisi,"Ukloni","Obrisite osobu ili relaciju iz stabla");
    tbUredi=kreirajJedanAlat(tbUredi,"UrediStablo","Rasporedite cvorove stabla automatski");

    grpToolBar->addButton(tbOsoba);
    grpToolBar->addButton(tbRoditeljDete);
    grpToolBar->addButton(tbBratSestra);
    grpToolBar->addButton(tbMuzZena);
    grpToolBar->addButton(tbPomeranje);
    grpToolBar->addButton(tbDetalji);
    grpToolBar->addButton(tbMenjaj);
    grpToolBar->addButton(tbBrisi);

    toolbar->addWidget(tbOsoba);
    toolbar->addSeparator();
    toolbar->addWidget(tbMuzZena);
    toolbar->addWidget(tbBratSestra);
    toolbar->addWidget(tbRoditeljDete);
    toolbar->addSeparator();
    toolbar->addWidget(tbPomeranje);
    toolbar->addWidget(tbMenjaj);
    toolbar->addWidget(tbBrisi);
    toolbar->addSeparator();
    toolbar->addWidget(tbUredi);
    toolbar->addWidget(tbDetalji);

    QDockWidget *alati = new QDockWidget(tr("Alati"));
    alati->setWidget(toolbar);
    alati->setAllowedAreas(Qt::TopDockWidgetArea
                           | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::TopDockWidgetArea, alati);
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

    std::cout<<"---KLIKNUTO--"<<std::endl;

    if(tbOsoba->isChecked()){
        tbOsoba->setChecked(false);
        if ((stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1())) != nullptr)
            qDebug() << "tu vec postoji nesto";
        else
            dodajNovuOsobu(stabloOkvir->X1(),stabloOkvir->Y1());

    }
    else if(tbBratSestra->isChecked()){
    }
    else if(tbMuzZena->isChecked()){
        //poveziOsobe();
        if ((stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1())) == nullptr)

            qDebug() << "nije kliknuto na prvu osobu";

        else
            if ((stabloOkvir->childAt(stabloOkvir->X2(), stabloOkvir->Y2())) == nullptr)
                qDebug() << "nije kliknuto na drugu osobu";
            else
                poveziOsobe(1,2,3);


    }
    else if(tbRoditeljDete->isChecked()){

    }
    else if(tbDetalji->isChecked()){
        if ((stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1())) == nullptr)
            qDebug() << "kliknuto u prazno";
        else
        {
            WidgetOsoba *osobaZaInfo = qobject_cast<WidgetOsoba*>(stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1()));
            if (osobaZaInfo == nullptr)
                qDebug() << "Nije osoba na koju je kliknuto";
            else
                qDebug() << osobaZaInfo->Sifra();
        }

    }
    else if(tbPomeranje->isChecked()){
        if ((stabloOkvir->childAt(stabloOkvir->X2(), stabloOkvir->Y2())) != nullptr)
            qDebug() << "tu vec postoji nesto";
        else
            if ((stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1())) == nullptr)
            {
                qDebug() << "nije kliknuto na osobu koju treba pomeriti";
                qDebug() << stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1())->metaObject()->className();
            }
            else
            {
                qDebug() << stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1())->metaObject()->className();

//                WidgetOsoba *osobaZaPomeranje = dynamic_cast<WidgetOsoba*>(stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1()));
//                if (osobaZaPomeranje == nullptr)
//                    qDebug() << "Nije osoba na koju je kliknuto";
//                else
//                    osobaZaPomeranje->move(stabloOkvir->X2(), stabloOkvir->Y2());

                //(stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1()))->move(stabloOkvir->X2(), stabloOkvir->Y2());
                //(stabloOkvir->childAt(stabloOkvir->X1(), stabloOkvir->Y1()))->show();
            }

    }

    tbDetalji->setChecked(true);

//        std::cout<<stabloOkvir->X1()<<stabloOkvir->X2()<<stabloOkvir->Y1()<<stabloOkvir->Y2()<<std::endl;
//    std::cout<<stabloOkvir->resetovan()<<std::endl;
    //stabloOkvir->resetujKoordinate();
//    std::cout<<stabloOkvir->resetovan()<<std::endl;
//            std::cout<<stabloOkvir->X1()<<stabloOkvir->X2()<<stabloOkvir->Y1()<<stabloOkvir->Y2()<<std::endl;
}

void GlavniProzor2::test()
{
    stabloOkvir->resetujKoordinate();
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

void GlavniProzor2::poveziOsobe(short sifra1, short sifra2, short tip)
{

    qDebug() << "povezuje";
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

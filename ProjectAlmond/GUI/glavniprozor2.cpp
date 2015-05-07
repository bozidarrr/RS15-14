#include "GUI/glavniprozor2.h"
#include "ui_glavniprozor2.h"
#include "GUI/dialognovaosoba.h"
#include <algorithm>
GlavniProzor2::GlavniProzor2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor2)
{
    ui->setupUi(this);

    QIcon icon(":images/images/ProjectAlmond.ico");
    this->setWindowIcon(icon);
    this->setWindowTitle("Project Almond");

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("pera", "detlic", 'm', "12.04.1963.");

    kreirajPlatnoZaCrtanje();
    kreirajToolbar();
    krerajMestoZaInfo();

    //kreirajOpcije();

//    WidgetOsoba *w1 = new WidgetOsoba(111,12,12,this,stabloOkvir);
//    WidgetOsoba *w2 = new WidgetOsoba(222,50,50,this,stabloOkvir);

//    w1->move(12,12);
//    w2->move(50,50);
}

GlavniProzor2::~GlavniProzor2()
{
    delete ui;

}

void GlavniProzor2::promeniSelektovanu(short novaSifra)
{
    _selektovanaSifra = novaSifra;
}

void GlavniProzor2::popuniInformacije(short sifra)
{
    if (sifra > 0)
    {
        Osoba *osoba = stablo->nadjiOsobuPoSifri(sifra);
        if (osoba != nullptr)
            Labela->setText(QString::fromStdString("<H1>"+osoba->Ime()+"<H1/>\n"+osoba->Prezime()));//i sve ostalo
    }
}

void GlavniProzor2::kreirajPlatnoZaCrtanje()
{
    QVBoxLayout* lejaut=new QVBoxLayout();
    QScrollArea* skrolPanel=new QScrollArea();
    lejaut->addWidget(skrolPanel);
    ui->centralwidget->setLayout(lejaut);

    stabloOkvir=new okvirStabla(skrolPanel);
    stabloOkvir->setGeometry(0,0,5000,5000);
    stabloOkvir->updateGeometry();
    skrolPanel->setWidget(stabloOkvir);
    stabloOkvir->setStyleSheet("background-color:rgb(0, 0, 0);");
    connect(stabloOkvir,SIGNAL(kliknut()),this,SLOT(kliknutoPlatno()));

    filter = new FilterObject(stabloOkvir);


}

void GlavniProzor2::kreirajOpcije()
{
}

QPushButton* GlavniProzor2::kreirajJedanAlat(QPushButton * alat, const char* ime,const char* info)
{
    alat=new QPushButton();
    alat->setCheckable(true);
    alat->setFocusPolicy(Qt::NoFocus);
    alat->setToolTip(info);
    std::string ikonica(":/images/images/"+std::string(ime)+".ico");
    const char* pocetak=&ikonica[0];
    alat->setIcon(QIcon(pocetak));
    alat->setIconSize(QSize(48,48));
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

    tbUredi->setCheckable(false);

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

    tbDetalji->setChecked(true);

    QDockWidget *alati = new QDockWidget(tr("Alati"));
    alati->setWidget(toolbar);
    alati->setAllowedAreas(Qt::TopDockWidgetArea
                           | Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::TopDockWidgetArea, alati);
}

void GlavniProzor2::krerajMestoZaInfo()
{
    QDockWidget *info = new QDockWidget(tr("Informacije"));
    Labela=new QLabel("Informacije");
    info->setWidget(Labela);//i recimo
    Labela->setToolTip("Ovde mozete pronaci informacije o trenutno aktivnoj osobi");
    info->setAllowedAreas(Qt::RightDockWidgetArea
                          | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, info);
}

void GlavniProzor2::kliknutoPlatno()
{

    std::cout<<"---KLIKNUTO--"<<std::endl;
    int x1 = stabloOkvir->X1();
    int y1 = stabloOkvir->Y1();
    int x2 = stabloOkvir->X2();
    int y2 = stabloOkvir->Y2();
    QWidget *labela1, *labela2;
    WidgetOsoba *prva, *druga;
    labela1 = stabloOkvir->childAt(x1, y1);
    labela2 = stabloOkvir->childAt(x2, y2);


    if(tbOsoba->isChecked()){
        //tbOsoba->setChecked(false);
        if ((stabloOkvir->childAt(x2, y2)) != nullptr)
            qDebug() << "tu vec postoji nesto";
        else
            dodajNovuOsobu(x2, y2);

    }
    else if(tbBratSestra->isChecked()){
        if (labela1 == nullptr)
            qDebug() << "nije kliknuto na prvu osobu";
        else
            if (labela2 == nullptr)
                qDebug() << "nije kliknuto na drugu osobu";
            else
            {
                prva = qobject_cast<WidgetOsoba*>(labela1->parent());
                druga = qobject_cast<WidgetOsoba*>(labela2->parent());
                poveziOsobe(prva->Sifra(),druga->Sifra(),Odnos::BRAT_SESTRA,x1,y1,x2,y2);
            }
    }
    else if(tbMuzZena->isChecked()){
        if (labela1 == nullptr)
            qDebug() << "nije kliknuto na prvu osobu";
        else
            if (labela2 == nullptr)
                qDebug() << "nije kliknuto na drugu osobu";
            else
            {
                prva = qobject_cast<WidgetOsoba*>(labela1->parent());
                druga = qobject_cast<WidgetOsoba*>(labela2->parent());
                poveziOsobe(prva->Sifra(),druga->Sifra(),Odnos::SUPRUZNIK,x1,y1,x2,y2);

            }
    }
    else if(tbRoditeljDete->isChecked()){
        if (labela1 == nullptr)
            qDebug() << "nije kliknuto na prvu osobu";
        else
            if (labela2 == nullptr)
                qDebug() << "nije kliknuto na drugu osobu";
            else
            {
                prva = qobject_cast<WidgetOsoba*>(labela1->parent());
                druga = qobject_cast<WidgetOsoba*>(labela2->parent());
                poveziOsobe(prva->Sifra(),druga->Sifra(),Odnos::RODITELJ,x1,y1,x2,y2);
            }

    }
    else if(tbDetalji->isChecked()){
        if (labela1 == nullptr)
            qDebug() << "kliknuto u prazno";
        else
        {
            prva = qobject_cast<WidgetOsoba*>(labela1->parent());
            if (prva == nullptr)
                qDebug() << "Nije osoba na koju je kliknuto";
            else
            {
                qDebug() << prva->Sifra();
                //promeniSelektovanu(prva->Sifra());
                popuniInformacije(prva->Sifra());
            }
        }

    }
    else if(tbPomeranje->isChecked()){
        if (labela2 != nullptr)
            qDebug() << "tu vec postoji nesto";
        else
            if (labela1 == nullptr)
            {
                qDebug() << "nije kliknuto na osobu koju treba pomeriti";
            }
            else
            {
                prva = qobject_cast<WidgetOsoba*>(labela1->parent());
                prva->setX(x2);
                prva->setY(y2);
                prva->move(x2, y2);
            }

    }
    else if(tbBrisi->isChecked()){
        if (labela2 == nullptr)
            qDebug() << "KLiknuti na osobu za brisanje!";
        else
        {
            druga = qobject_cast<WidgetOsoba*>(labela2->parent());
            if (druga == nullptr)
                qDebug() << "ne moze cast u wosobu";
            else
                //stablo->UkloniOsobuPoSifri(druga->Sifra());
                druga->hide();
            //DORADITI
        }

    }
    else if(tbMenjaj->isChecked()){
        //izbaci dijalog za menjanje podataka
    }


    tbDetalji->setChecked(true);
}


void GlavniProzor2::dodajNovuOsobu(int x,int y)
{
    DialogNovaOsoba *d = new DialogNovaOsoba(this);
    if (d->exec())
    {
        std::string ime, prezime, rodjenje, smrt;
        char pol;

        d->popuniPodatke(ime, prezime, pol, rodjenje, smrt);

        short int novaSifra = stablo->DodajOsobu(ime, prezime, pol, rodjenje, smrt);
        if (novaSifra < 0)
            qDebug() << "Neuspelo dodavanje";//OVO DA SE PRETVORI U OBAVESTENJE U STATUS BARU KADA GA NAPRAVIMO
        else
            qDebug() << "Uspelo dodavanje";

        WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra,x,y, this, stabloOkvir);
        std::string tmp = ime + " " + prezime;
        novaOsoba->postaviImePrezime(tmp);
        novaOsoba->move(novaOsoba->X(),novaOsoba->Y());
        novaOsoba->show();
    }

    delete d;
}


void GlavniProzor2::kliknutaRelacija()
{

}

void GlavniProzor2::poveziOsobe(short sifra1, short sifra2, Odnos odnos,int x1,int y1,int x2, int y2)
{

    qDebug() << "povezuje";
    if (sifra1 == sifra2){
        qDebug() << "iste osobe povezujes!";

    }
    else
    {qDebug() << odnos;


        short sifraRelacije = stablo->PoveziOsobe(sifra1, sifra2, odnos);

        if (sifraRelacije < 0){

            qDebug() << "Povezivanje nije uspelo";
        }
        else
        {

            WidgetRelacija *novaRelacija = new WidgetRelacija(sifraRelacije,(x1+x2)/2-25,(y1+y2)/2-25, this, stabloOkvir);
            novaRelacija->move(novaRelacija->X(),novaRelacija->Y());
            novaRelacija->show();
            stabloOkvir->povuciLiniju(x1,y1,x2,y2);
            stabloOkvir->repaint();
            qDebug() << "Povezivanje jeste uspelo";

        }
    }

    //        cuvamo u vektor,
    //        pravimo widget za relaciju i iscrtavamo ga na sredini
    //        tu negde pozivamo i dijalog za relaciju

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

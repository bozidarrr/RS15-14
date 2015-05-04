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
    int x1 = stabloOkvir->X1();
    int y1 = stabloOkvir->Y1();
    int x2 = stabloOkvir->X2();
    int y2 = stabloOkvir->Y2();
    WidgetOsoba *prva, *druga;
    QWidget *labela1, *labela2;

    if(tbOsoba->isChecked()){
        tbOsoba->setChecked(false);
        if ((stabloOkvir->childAt(x2, y2)) != nullptr)
            qDebug() << "tu vec postoji nesto";
        else
            dodajNovuOsobu(x2, y2);

    }
    else if(tbBratSestra->isChecked()){
    }
    else if(tbMuzZena->isChecked()){
        //poveziOsobe();
        if ((labela1 = (stabloOkvir->childAt(x1, y1))) == nullptr)

            qDebug() << "nije kliknuto na prvu osobu";

        else
            if ((labela2 = (stabloOkvir->childAt(x2, y2))) == nullptr)
                qDebug() << "nije kliknuto na drugu osobu";
            else
            {
                prva = qobject_cast<WidgetOsoba*>(labela1->parent());
                druga = qobject_cast<WidgetOsoba*>(labela2->parent());
                poveziOsobe(prva->Sifra(),druga->Sifra(),3);
            }


    }
    else if(tbRoditeljDete->isChecked()){

    }
    else if(tbDetalji->isChecked()){
        if ((labela1  = (stabloOkvir->childAt(x1, y1))) == nullptr)
            qDebug() << "kliknuto u prazno";
        else
        {
            prva = qobject_cast<WidgetOsoba*>(labela1->parent());
            if (prva == nullptr)
                qDebug() << "Nije osoba na koju je kliknuto";
            else
                qDebug() << prva->Sifra();
        }

    }
    else if(tbPomeranje->isChecked()){
        if ((labela2 = (stabloOkvir->childAt(x2, y2))) != nullptr)
            qDebug() << "tu vec postoji nesto";
        else
            if ((labela1 = (stabloOkvir->childAt(x1, y1))) == nullptr)
            {
                qDebug() << "nije kliknuto na osobu koju treba pomeriti";
            }
            else
            {
                prva = qobject_cast<WidgetOsoba*>(labela1->parent());
                prva->move(y1, y2);

            }

    }

    tbDetalji->setChecked(true);

//        std::cout<<stabloOkvir->X1()<<stabloOkvir->X2()<<stabloOkvir->Y1()<<stabloOkvir->Y2()<<std::endl;
//    std::cout<<stabloOkvir->resetovan()<<std::endl;
    //stabloOkvir->resetujKoordinate();
//    std::cout<<stabloOkvir->resetovan()<<std::endl;
//            std::cout<<stabloOkvir->X1()<<stabloOkvir->X2()<<stabloOkvir->Y1()<<stabloOkvir->Y2()<<std::endl;
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

        WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra,x,y, this, stabloOkvir);
        std::string tmp = ime.toStdString() + " " + prezime.toStdString();
        novaOsoba->postaviImePrezime(tmp);
        novaOsoba->move(novaOsoba->X(),novaOsoba->Y());

        novaOsoba->installEventFilter(filter);

        novaOsoba->show();
        //_osobe.push_back(novaOsoba);

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


void GlavniProzor2::poveziOsobe(short sifra1, short sifra2, short tip)
{

    qDebug() << "povezuje";
    if (sifra1 == sifra2)
        qDebug() << "iste osobe povezujes!";
    else
        qDebug() << tip;

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

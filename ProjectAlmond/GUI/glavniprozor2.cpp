#include "GUI/glavniprozor2.h"
#include "ui_glavniprozor2.h"
#include "GUI/dialognovaosoba.h"

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
//    FilterObject *f = new FilterObject();
//    QPushButton *b = new QPushButton("dugem");
//    b->installEventFilter(f);
//    b->show();


}

GlavniProzor2::~GlavniProzor2()
{
//    delete ui;
//    delete stablo;
//       delete stabloOkvir;
//       delete grpToolBar;
//       delete tbOsoba;
//       delete tbMuzZena;
//       delete tbBratSestra;
//       delete tbRoditeljDete;
//       delete tbPomeranje;
//       delete tbDetalji;
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

    connect(stabloOkvir,SIGNAL(kliknut()),this,SLOT(izvrsiAkciju()));

}

void GlavniProzor2::kreirajOpcije()
{






}

void GlavniProzor2::kreirajToolbar()
{

    toolbar = addToolBar(tr("Alati"));

    grpToolBar=new QButtonGroup();
    tbOsoba = new QToolButton();
    tbOsoba->setCheckable(true);
    tbOsoba->setText("Nova osoba");
    tbOsoba->setToolTip(tr("Kreirajte novu osobu"));
    tbOsoba->setFocusPolicy(Qt::NoFocus);
    //tbOsoba->setIcon(ikonica); za sad je tekst
    //tbOsoba->setShortcut();

    tbMuzZena = new QToolButton();
    tbMuzZena->setText("Supruznik");
    tbMuzZena->setCheckable(true);
    tbMuzZena->setToolTip(tr("Kreirajte novi odnos dva supruznika"));
    tbMuzZena->setFocusPolicy(Qt::NoFocus);

    tbBratSestra = new QToolButton();
    tbBratSestra->setText("Brat/Sestra");
    tbBratSestra->setCheckable(true);
    tbBratSestra->setToolTip(tr("Kreirajte novi odnos dvoje brace/sestara"));
    tbBratSestra->setFocusPolicy(Qt::NoFocus);

    tbRoditeljDete = new QToolButton();
    tbRoditeljDete->setText("Roditelj/Dete");
    tbRoditeljDete->setCheckable(true);
    tbRoditeljDete->setToolTip(tr("Kreirajte novi odnos tipa roditelj-dete"));
    tbRoditeljDete->setFocusPolicy(Qt::NoFocus);

    tbPomeranje = new QToolButton();
    tbPomeranje->setText("Pomeri");
    tbPomeranje->setToolTip(tr("Pomerite rucicom odabranu osobu ili relaciju na crtezu"));
    tbPomeranje->setCheckable(true);
    tbPomeranje->setFocusPolicy(Qt::NoFocus);

    tbDetalji = new QToolButton();
    tbDetalji->setText("Detalji");
    tbDetalji->setCheckable(true);
    tbDetalji->setToolTip(tr("Detalji o odabranoj osobi"));
    tbDetalji->setFocusPolicy(Qt::NoFocus);

    tbMenjaj = new QToolButton();
    tbMenjaj->setText("Promeni");
    tbMenjaj->setCheckable(true);
    tbMenjaj->setToolTip(tr("Izmenite podatke o odabranoj osobi ili relaciji"));
    tbMenjaj->setFocusPolicy(Qt::NoFocus);

    tbBrisi = new QToolButton();
    tbBrisi->setText("Obrisi");
    tbBrisi->setCheckable(true);
    tbBrisi->setToolTip(tr("Obrisite osobu ili relaciju iz stabla"));
    tbBrisi->setFocusPolicy(Qt::NoFocus);

    grpToolBar->addButton(tbMuzZena);
    grpToolBar->addButton(tbBratSestra);
    grpToolBar->addButton(tbRoditeljDete);
    grpToolBar->addButton(tbOsoba);
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

void GlavniProzor2::izvrsiAkciju()
{


    if(tbOsoba->isChecked()){
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

}

void GlavniProzor2::dodajNovuOsobu(int x,int y)
{
    //iscitamo podatke preko onog dijaloga ili kako vec
    // -> ime, prezime, pol, datume

    // short int sifra = stablo->DodajOsobu(...);

    //onda
    //Widget *novaOsoba = new WidgetOsoba(sifra, this)
    //i negde je smestimo xD

    //WidgetOsoba *novaOsoba = new WidgetOsoba(1, this, ui->stabloOkvir);
    //novaOsoba->postaviImePrezime("Pera Peric");

    //novaOsoba->show();
    //ui->stabloOkvir->repaint();
    DialogNovaOsoba *d = new DialogNovaOsoba(this);
    if (d->exec())
    {/*citamo*/

        /*
            u knjizi pristupa direktno lineEditu, to je malo bzvz

            saljemo enginu

            pamtimo vracenu sifru osobe

            kreiramo widget osobu

            tj zahtevamo klik na panel gde cemo je smestiti
        */
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
            ui->label->setText("Neuspelo dodavanje");
        else
            ui->label->setText("Uspelo");

        WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra,x,y, ime, prezime, this, ui->stabloFrame);
        std::string tmp = ime.toStdString() + " " + prezime.toStdString();
        novaOsoba->postaviImePrezime(tmp);
        novaOsoba->move(novaOsoba->X(),novaOsoba->Y());
        novaOsoba->show();
        _osobe.push_back(novaOsoba);

        _sifra1 = -1;
        _sifra2 = -1;
    }

    delete d;
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

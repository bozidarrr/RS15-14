#include "GUI/glavniprozor2.h"
#include "ui_glavniprozor2.h"
#include "GUI/dialognovaosoba.h"

GlavniProzor2::GlavniProzor2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor2)
{
    ui->setupUi(this);

    _sifra1 = -1;
    _sifra2 = -1;


    QIcon icon(":images/ProjectAlmond.ico");
    this->setWindowIcon(icon);
    this->setWindowTitle("Project Almond");

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("pera", "detlic", 'm', "12.04.1963.");


    kreirajToolbar();
    krerajMestoZaInfo();
    kreirajPlatnoZaCrtanje();
    //kreirajOpcije();



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

    grpToolBar->addButton(tbMuzZena);
    grpToolBar->addButton(tbBratSestra);
    grpToolBar->addButton(tbRoditeljDete);
    grpToolBar->addButton(tbOsoba);
    grpToolBar->addButton(tbPomeranje);
    grpToolBar->addButton(tbDetalji);

    toolbar->addWidget(tbOsoba);
    toolbar->addSeparator();
    toolbar->addWidget(tbMuzZena);
    toolbar->addWidget(tbBratSestra);
    toolbar->addWidget(tbRoditeljDete);
    toolbar->addSeparator();
    toolbar->addWidget(tbPomeranje);
    toolbar->addWidget(tbDetalji);



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
}

void GlavniProzor2::izvrsiAkciju()
{


    if(tbOsoba->isChecked()){
        dodajNovuOsobu(stabloOkvir->X1(),stabloOkvir->Y1());
    }
    else if(tbBratSestra->isChecked()){


    }
    else if(tbMuzZena->isChecked()){
        poveziOsobe();
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
        QString pol; // Kako pretvoriti u char -- TO DO
        QDate rodjenje, smrt;
        d->popuniPodatke(ime, prezime, pol, rodjenje, smrt);
        std::string r = rodjenje.toString("dd.MM.yyyy.").toStdString();
        std::string d;
        if (smrt.isValid())
            d = "";
        else
            d = smrt.toString("dd.MM.yyyy.").toStdString();
        short int novaSifra = stablo->DodajOsobu(ime.toStdString(),
                                                 prezime.toStdString(), 'm', r, d); //POL!
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

void GlavniProzor2::poveziOsobe()
{
    //za sifra1, sifra2
    //ako je sve ok
    //iscrtava se i ta relacija
    std::cout<<"poceo"<<std::endl;
    for (WidgetOsoba *o : _osobe)
    {
        std::cout<<"trazi"<<std::endl;
        //ovo nam ne radi ovako jer se zapravo klikne na dugme, a ne na okvir
//        if (o->sadrziTacku(stabloOkvir->X1(), stabloOkvir->Y1()))
//        {
//            std::cout<<"nasao 1"<<std::endl;
//        }
        if (o->sadrziTacku(stabloOkvir->X2(), stabloOkvir->Y2()))
        {
            std::cout<<"nasao 2"<<std::endl;
        }
    }

    if (_sifra1 > 0 && _sifra2 > 0 && _sifra1 != _sifra2)
        std::cout<<"Povezuje 2 osobe"<<std::endl;
    else
        std::cout<<"nesto ne valja"<<std::endl;
    _sifra1 = -1;
    _sifra2 = -1;

    //short sifraRelacije = stablo->PoveziOsobe(sifra1, sifra2, Odnos::SUPRUZNIK);
}

short int GlavniProzor2::_selektovanaSifra = -1;

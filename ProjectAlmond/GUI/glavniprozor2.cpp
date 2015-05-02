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

    connect(tbOsoba,SIGNAL(clicked()),this,SLOT(dodajNovuOsobu()));

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
    Osoba *osoba = stablo->nadjiOsobuPoSifri(_selektovanaSifra);
    ui->label->setText(QString::fromStdString("<H1>"+osoba->Ime()+"<H1/>\n"+osoba->Prezime()));//i sve ostalo
}

void GlavniProzor2::kreirajOpcije()
{
    //snimi, otvori, sve sto treba
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

void GlavniProzor2::dodajNovuOsobu()
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

        WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra,123,123, ime, prezime, this, ui->stabloOkvir);
        std::string tmp = ime.toStdString() + " " + prezime.toStdString();
        novaOsoba->postaviImePrezime(tmp);
        novaOsoba->move(novaOsoba->X(),novaOsoba->Y());//ovde ce se prosledjivati point koji je dobijen klikom
        novaOsoba->show();
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
    //ovde pozivamo konstruktor za relaciju
    //prema radio buttonu
    //za sifra1, sifra2
    //ako je sve ok
    //iscrtava se i ta relacija

    //short sifraRelacije = stablo->PoveziOsobe(sifra1, sifra2, Odnos::SUPRUZNIK);
}

short int GlavniProzor2::_selektovanaSifra = -1;

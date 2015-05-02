#include "GUI/glavniprozor2.h"
#include "ui_glavniprozor2.h"
#include "GUI/dialognovaosoba.h"

GlavniProzor2::GlavniProzor2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor2)
{
    ui->setupUi(this);

    sifra1 = -1;
    sifra2 = -1;

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("pera", "detlic", 'm', "12.04.1963.");

    kreirajToolbar();

    connect(tbOsoba,SIGNAL(clicked()),this,SLOT(dodajNovuOsobu()));

    //kreirajOpcije();

}

GlavniProzor2::~GlavniProzor2()
{
    delete ui;
}

void GlavniProzor2::promeniSelektovanu(short novaSifra)
{
    selektovana_sifra = novaSifra;
}

void GlavniProzor2::popuniInformacije()
{
    //Osoba* osoba = stablo->nadjiOsobuPoSifri(selektovana_sifra);
    // if  == nullptr greska
    //inace pisemo
    //QString tmp = QString::fromStdString(osoba->Ime());
    //pisemo u neki QLabel, QTextBrowser?
}

void GlavniProzor2::kreirajOpcije()
{
    //snimi, otvori, sve sto treba
}

void GlavniProzor2::kreirajToolbar()
{
    toolbar = addToolBar(tr("Alati"));
    tbOsoba = new QToolButton();
    //tbOsoba->setIcon(ikonica); za sad je tekst
    //tbOsoba->setShortcut();
    //tbOsoba->setCheckable(true);
    tbOsoba->setText("Nova osoba");
    toolbar->addWidget(tbOsoba);

    toolbar->addSeparator();
//<RadioButton Style="{StaticResource {x:Type ToggleButton}}" />
    grpRelacije = new QButtonGroup();
    rbMuzZena = new QRadioButton("Supruznik");
    rbMuzZena->setChecked(true);
    rbBratSestra = new QRadioButton("Brat/Sestra");
    rbRoditelj = new QRadioButton("Roditelj");
    rbDete = new QRadioButton("Dete");
    grpRelacije->addButton(rbMuzZena);
    grpRelacije->addButton(rbBratSestra);
    grpRelacije->addButton(rbRoditelj);
    grpRelacije->addButton(rbDete);

    toolbar->addWidget(rbMuzZena);
    toolbar->addWidget(rbBratSestra);
    toolbar->addWidget(rbRoditelj);
    toolbar->addWidget(rbDete);

    toolbar->addSeparator();

    tbPomeranje = new QToolButton();
    tbPomeranje->setText("Pomeri");
    tbPomeranje->setToolTip("Sluzice za pomeranje stvari nakon sto su smestene");
    //stavicemo slicicu
    tbDetalji = new QToolButton();
    tbDetalji->setText("?");
    tbDetalji->setToolTip("Jasno valjda, da ispise detalje o onome na sta se posle klikne");

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

        WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra, ime, prezime, this, ui->stabloOkvir);
        std::string tmp = ime.toStdString() + " " + prezime.toStdString();
        novaOsoba->postaviImePrezime(tmp);
        novaOsoba->move(123,123);//ovde ce se prosledjivati point koji je dobijen klikom
        novaOsoba->show();
    }

    delete d;
}

void GlavniProzor2::postaviSifru1(short nova)
{
    sifra1 = nova;
}

void GlavniProzor2::postaviSifru2(short nova)
{
    sifra2 = nova;
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

short int GlavniProzor2::selektovana_sifra = -1;

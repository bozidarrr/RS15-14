#include "GUI/glavniprozor.h"
#include "ui_glavniprozor.h"
#include "GUI/dialognovaosoba.h"
#include <algorithm>

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor),
    _nesacuvaneIzmene(false)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    QIcon icon(":images/images/ProjectAlmond.ico");
    this->setWindowIcon(icon);
    this->setWindowTitle("Project Almond");

//DODATO---------------------------------------------------
        //ovo treba bolje da se uradi
//    DialogNovaOsoba *d = new DialogNovaOsoba(false, this);
//    if (d->exec())
//    {
//        std::string ime, prezime, rodjenje, smrt, trivija;
//        char pol;
//        d->popuniPodatke(ime, prezime, pol, rodjenje, smrt, trivija);

//        stablo = new PorodicnoStablo(ime, prezime, pol, true);

//        short int novaSifra = stablo->KljucnaOsoba()->Sifra();

//        ui->statusBar->showMessage("Kreirano novo stablo", 2000);
//        WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra, 0, 0, this, stabloOkvir);
//        std::string tmp = stablo->NadjiOsobuSifrom(novaSifra)->Ime() + " " + stablo->NadjiOsobuSifrom(novaSifra)->Prezime();
//        novaOsoba->postaviImePrezime(tmp);
//       // novaOsoba->setX((stabloOkvir->width()-novaOsoba->width())/2);
//       // novaOsoba->setY((stabloOkvir->height()-novaOsoba->height())/2);
//        novaOsoba->move(novaOsoba->X(),novaOsoba->Y());
//        novaOsoba->show();
//        delete d;

//        _nesacuvaneIzmene = true;

//    }
//    else
//        ui->statusBar->showMessage("Nesto nije bilo u redu sa kreiranjem stabla!");
//DODATO---------------------------------------------------------------------

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("Pera", "Detlic", 'm');

    kreirajPlatnoZaCrtanje();
    kreirajToolbar();
    kreirajMestoZaInfo();
    kreirajStatusBar();

    WidgetOsoba *korena=new WidgetOsoba(stablo->KljucnaOsoba()->Sifra(),50,50,this,stabloOkvir);
    korena->postaviImePrezime(stablo->KljucnaOsoba()->Ime()+" "+stablo->KljucnaOsoba()->Prezime());
    korena->move(50,50);

    kreirajOpcije();
}

GlavniProzor::~GlavniProzor()
{
    delete ui;

}

void GlavniProzor::promeniSelektovanu(short novaSifra)
{
    _selektovanaSifra = novaSifra;
}

void GlavniProzor::popuniInformacije(short sifra)
{
    if (sifra == -1)
    {
        Labela->setText("");
        return;
    }
    Osoba *osoba = stablo->NadjiOsobuSifrom(sifra);
    //Neka provera da li je osoba poznata ili ne
    if (osoba != nullptr)
        Labela->setText(QString::fromStdString("<H1>"+osoba->Ime()+"<H1/>\n"+osoba->Prezime()));//i sve ostalo
}

void GlavniProzor::ispisiStatus(const QString &poruka)
{
    labelaStatus->setText(poruka);
}

void GlavniProzor::kreirajPlatnoZaCrtanje()
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

void GlavniProzor::kreirajStatusBar()
{
    labelaStatus = new QLabel(" ...");
    labelaStatus->setMinimumSize(labelaStatus->sizeHint());
    ui->statusBar->addWidget(labelaStatus, 1);
}

void GlavniProzor::prikaziToolbar()
{
    alati->setVisible(ui->aAlati->isChecked());
}

QPushButton* GlavniProzor::kreirajJedanAlat(QPushButton * alat, const char* ime,const char* info)
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

void GlavniProzor::kreirajOpcije()
{
    connect(ui->aAlati,SIGNAL(triggered()),this,SLOT(prikaziToolbar()));
    connect(tbDetalji,SIGNAL(clicked()),this,SLOT(promeniKursor()));

    connect(ui->aNovoStablo, SIGNAL(triggered()), this, SLOT(novoStablo()));
    connect(ui->aOtvori, SIGNAL(triggered()), this, SLOT(otvoriPostojeceStablo()));
    //connect(ui->aSacuvaj, SIGNAL(triggered()), this, SLOT());
    connect(ui->aZatvori, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->aUgasi, SIGNAL(triggered()),qApp, SLOT(closeAllWindows()));
    connect(ui->aSacuvaj, SIGNAL(triggered()), this, SLOT(sacuvaj()));
}

void GlavniProzor::kreirajToolbar()
{
    toolbar = addToolBar(tr("Alati"));

    grpToolBar=new QButtonGroup();

    tbMuzZena=kreirajJedanAlat(tbMuzZena,"RelacijaSupruznici","Dodajte u stablo supruznika nekoj od osoba");
    tbRoditeljDete=kreirajJedanAlat(tbRoditeljDete,"RelacijaDete","Dodajte u neku vezu novo dete");
    tbBratSestra=kreirajJedanAlat(tbBratSestra,"RelacijaBratSestra","Dodajte u stablo brata ili sestru nekoj osobi");
    tbPomeranje=kreirajJedanAlat(tbPomeranje,"Pomeri","Pomerite rucicom odabranu osobu ili relaciju na crtezu");
    tbDetalji=kreirajJedanAlat(tbDetalji,"Informacija","Detalji o odabranoj osobi ili odnosu");
    tbMenjaj=kreirajJedanAlat(tbMenjaj,"Menjaj","Izmenite podatke o odabranoj osobi ili odnosu");
    tbBrisi=kreirajJedanAlat(tbBrisi,"Ukloni","Obrisite osobu ili relaciju iz stabla");
    tbUredi=kreirajJedanAlat(tbUredi,"UrediStablo","Rasporedite cvorove stabla automatski");

    tbUredi->setCheckable(false);

    grpToolBar->addButton(tbRoditeljDete);
    grpToolBar->addButton(tbMuzZena);
    grpToolBar->addButton(tbBratSestra);
    grpToolBar->addButton(tbPomeranje);
    grpToolBar->addButton(tbDetalji);
    grpToolBar->addButton(tbMenjaj);
    grpToolBar->addButton(tbBrisi);

    toolbar->addWidget(tbMuzZena);
    toolbar->addWidget(tbRoditeljDete);
    toolbar->addWidget(tbBratSestra);
    toolbar->addSeparator();
    toolbar->addWidget(tbPomeranje);
    toolbar->addWidget(tbMenjaj);
    toolbar->addWidget(tbBrisi);
    toolbar->addSeparator();
    toolbar->addWidget(tbUredi);
    toolbar->addWidget(tbDetalji);

    tbDetalji->setChecked(true);

    alati = new QDockWidget(tr("Alati"));
    alati->setWidget(toolbar);
    alati->setAllowedAreas(Qt::TopDockWidgetArea
                           | Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    addDockWidget(Qt::TopDockWidgetArea, alati);
}

void GlavniProzor::kreirajMestoZaInfo()
{
    QDockWidget *info = new QDockWidget(tr("Informacije"));
    Labela=new QLabel("Informacije");
    info->setWidget(Labela);//i recimo
    Labela->setToolTip("Ovde mozete pronaci informacije o trenutno aktivnoj osobi");
    info->setAllowedAreas(Qt::RightDockWidgetArea
                          | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, info);
}

void GlavniProzor::kliknutoPlatno()
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

    if(tbMuzZena->isChecked()){
        if (labela1 == nullptr)
            qDebug() << "nije kliknuto na prvu osobu";
        else
        {
            prva = qobject_cast<WidgetOsoba*>(labela1->parent());
            short int novaSifraOsobe=dodajNovuOsobu(x2, y2, false);
            if (novaSifraOsobe < 0)
                ui->statusBar->showMessage("Odustali ste od dodavanja novog supruznika", 2000);
            else{
                short int novaSifraBraka=stablo->DodajBrak(prva->Sifra(),novaSifraOsobe);
                WidgetRelacija *novaRelacija = new WidgetRelacija(novaSifraBraka,(x1+x2)/2-25,(y1+y2)/2-25, this, stabloOkvir);
                novaRelacija->move(novaRelacija->X(),novaRelacija->Y());
                novaRelacija->show();
                stabloOkvir->povuciLiniju(x1,y1,x2,y2);
                stabloOkvir->repaint();
            }
        }
    }
    else if(tbRoditeljDete->isChecked()){
        if (labela1 == nullptr)
            qDebug() << "nije kliknuto na prvu osobu";
        else
            {
                prva = qobject_cast<WidgetOsoba*>(labela1->parent());
                short int novaSifraOsobe=dodajNovuOsobu(x2,y2,true);
                if (novaSifraOsobe < 0)
                        ui->statusBar->showMessage("Odustali se od dodavanja novog deteta", 2000);
                else
                {
                   // short int novaSifraDeteta = stablo->DodajDete(prva->)

                }
            }
    }
    else if(tbDetalji->isChecked()){
        if (labela1 == nullptr)
        {
            qDebug() << "kliknuto u prazno";
            popuniInformacije(-1);
        }
        else
        {
            prva = qobject_cast<WidgetOsoba*>(labela1->parent());
            if (prva == nullptr)
                qDebug() << "Nije osoba na koju je kliknuto";
            else
            {
                qDebug() << prva->Sifra();
                promeniSelektovanu(prva->Sifra());
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
                prva->setX(x2);//treba malo preracunati ovo
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
            {
                //ne znam koliko ovo ima smisla, pretpostavljam da treba drugacije reagovati
                //u svakom od slucajeva
                //ZA SADA IPAK RADE ISTO
                QString upozorenje;
                if (druga->Sifra() == stablo->KljucnaOsoba()->Sifra())
                    upozorenje = tr("Jeste li sigurni da zelite da uklonite korenu osobu?"
                                    " To ce prouzrokovati brisanje celog stabla!");
                else
                    if (stablo->NadjiOsobuSifrom(druga->Sifra())->JeKrvniSrodnik())
                        upozorenje = tr("Jeste li sigurni da zelite da uklonite selektovanu osobu,"
                                        "a time i sve njene supruznike i potomke?");
                    else
                        upozorenje = tr("Jeste li sigurni da zelite da uklonite selektovanu osobu?");
                QMessageBox *poruka = new QMessageBox();
                QPushButton *da = poruka->addButton(tr("Da"), QMessageBox::AcceptRole);
                poruka->setDefaultButton(da);
                QPushButton *ne = poruka->addButton(tr("Ne"), QMessageBox::RejectRole);
                poruka->setEscapeButton(ne);
                poruka->setIcon(QMessageBox::Question);
                poruka->setObjectName(tr("Uklanjanje osobe"));
                //poruka->setText(tr("Jeste li sigurni da zelite da uklonite selektovanu osobu i sve njene veze?"));
                poruka->setText(upozorenje);
////                QMessageBox *poruka = QMessageBox::warning(this, tr("Brisanje osobe"),
////                                                           tr("Jeste li sigurni da zelite da izbrisete osobu i njene veze?"),
////                                                           QMessageBox::Yes | QMessageBox::Default,
////                                                           QMessageBox::Cancel | QMessageBox::Escape);
                poruka->exec();
                if (poruka->clickedButton() == da)
                {
                    stablo->UkloniOsobuSifrom(druga->Sifra());
                //druga->hide();
                    delete druga;
                    ui->statusBar->showMessage(tr("Uspesno izvrseno uklanjanje izabrane osobe."), 2000);
                    _nesacuvaneIzmene = true;
                }
                else
                    ui->statusBar->showMessage(tr("Osoba nije uklonjena"), 2000);
            }
            //DORADITI
        }

    }
    else if(tbMenjaj->isChecked()){
        //izbaci dijalog za menjanje podataka
        if (labela2 == nullptr)
            qDebug() << "nista nije izabrano";
        else
        {
            //dijalog
            druga = qobject_cast<WidgetOsoba*>(labela2->parent());
            if (druga == nullptr)
            {
                qDebug() << "ne moze cast u wosobu";
                WidgetRelacija *druga = qobject_cast<WidgetRelacija*>(labela2->parent());
                if (druga == nullptr)
                    qDebug() << "ne moze cast ni u wrelaciju";
                else
                    //dijalog za menjanje relacije...
                    qDebug() << "menjanje relacije";
            }
            else
            {
                qDebug() << "menjanje osobe";

                DijalogIzmenaOsobe *d = new DijalogIzmenaOsobe(druga->Sifra(), this);
                d->exec();
                /*if (d.exec())

                else
                   bila greska...

                */
            }
        }
    }
    tbDetalji->setChecked(true);
}


short int GlavniProzor::dodajNovuOsobu(int x, int y, bool krvniSrodnik)
{
    DialogNovaOsoba *d = new DialogNovaOsoba(true, this);
    if (d->exec())
    {
        std::string ime, prezime, rodjenje, smrt, trivija;
        char pol;

        d->popuniPodatke(ime, prezime, pol, rodjenje, smrt, trivija);

        short int novaSifra = stablo->DodajOsobu(ime, prezime, pol, krvniSrodnik);
        if (novaSifra < 0){
            ui->statusBar->showMessage("Neuspelo dodavanje nove osobe, pokusajte ponovo.", 2000);
            //ispisiStatus("Neuspelo dodavanje nove osobe, pokusajte ponovo.");//OVO DA SE PRETVORI U OBAVESTENJE U STATUS BARU KADA GA NAPRAVIMO
            delete d;
            return -1;
        }
        else{
            //ispisiStatus("Uspelo dodavanje nove osobe.");
            ui->statusBar->showMessage("Uspelo dodavanje nove osobe.", 2000);
            WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra,x,y, this, stabloOkvir);
            std::string tmp = stablo->NadjiOsobuSifrom(novaSifra)->Ime() + " " + stablo->NadjiOsobuSifrom(novaSifra)->Prezime();
            novaOsoba->postaviImePrezime(tmp);
            novaOsoba->move(novaOsoba->X(),novaOsoba->Y());
            novaOsoba->show();
            delete d;

            _nesacuvaneIzmene = true;

            return novaSifra;
        }
    }
    return -1;
}


void GlavniProzor::kliknutaRelacija()
{

}

void GlavniProzor::promeniKursor()
{
    //TO DO
    //this->setCursor(Qt::CursorShape::ClosedHandCursor);
}

bool GlavniProzor::nastaviti()
{
    //TO DO : dugmici ne treba da budu na engleskom
    if (_nesacuvaneIzmene == true)
    {
        QMessageBox *poruka = new QMessageBox();
        poruka->setInformativeText(tr("Postoje nesacuvane izmene u trenutnom stablu. Da li zelite da ih snimite?"));
        poruka->setModal(true);

        poruka->setObjectName(tr("Project Almond"));
        QPushButton *da = poruka->addButton(tr("Da"), QMessageBox::AcceptRole);
        poruka->setDefaultButton(da);
        poruka->addButton(tr("Ne"), QMessageBox::NoRole);
        QPushButton *odustani = poruka->addButton(tr("Odustani"), QMessageBox::RejectRole);
        poruka->setEscapeButton(odustani);
        poruka->setIcon(QMessageBox::Warning);
        poruka->exec();
        //int odgovor = poruka->exec();
        //qDebug() << odgovor;

//        int odgovor = QMessageBox::warning(this, tr("Project Almond"),
//                                           tr("Postoje nesacuvane izmene u trenutnom stablu. Da li zelite da ih snimite?"),
//                                           QMessageBox::Yes | QMessageBox::Default, QMessageBox::No,
//                                           QMessageBox::Cancel | QMessageBox::Escape);
//        if (odgovor == 0)
//            return snimiIzmene();
//        if (odgovor == 2)
//            return false;
        if (poruka->clickedButton() == da)
            return snimiIzmene();
        if (poruka->clickedButton() == odustani)
            return false;
    }
    return true;
}

bool GlavniProzor::snimiIzmene()
{
    //TO DO
    _nesacuvaneIzmene = false;
    ui->statusBar->showMessage("Snimljeno", 2000);
    return true;
}

void GlavniProzor::novoStablo()
{
    //TO DO
//    if (nastaviti())
//        qDebug() << "treba otvoriti novi fajl";
//    else
//        qDebug() << "ne otvarati";
    GlavniProzor *w = new GlavniProzor();
    w->show();
}

void GlavniProzor::otvoriPostojeceStablo()
{
    //TO DO
    if (nastaviti())
    {
        qDebug() << "treba otvoriti postojeci fajl";
        QString imeFajla = QFileDialog::getOpenFileName(this,
                                                        tr("Otvorite postojece stablo."),
                                                        tr("ProjectAlmond (*.alm)")); //sta su nam ekstenzije?
        if (!imeFajla.isEmpty())
            qDebug() << "nasli fajl i treba  ga otvoriti";
        //loadFile(imeFajla());
        else
            qDebug() << "odustali od otvaranja";
    }
    else
        qDebug() << "ne otvarati";
}

void GlavniProzor::closeEvent(QCloseEvent *event)
{
    if (nastaviti())
    {
        //storeSettings TODO
        qDebug() << "Zatvaramo fajl";
        event->accept();
    }
    else
    {
        qDebug() << "Otkazano izlazenje";
        event->ignore();
    }
}

bool GlavniProzor::sacuvaj()
{
    //Hmmmm
    return snimiIzmene();
}

bool GlavniProzor::sacuvajKao()
{
    //To DO
    return snimiIzmene();
}

short int GlavniProzor::_selektovanaSifra = -1;

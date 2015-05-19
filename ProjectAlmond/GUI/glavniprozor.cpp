#include "GUI/glavniprozor.h"
#include "ui_glavniprozor.h"
#include "GUI/dialognovaosoba.h"
#include <algorithm>

#include <QGraphicsRectItem>
#include <QTransform>

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    QIcon icon(":images/images/ProjectAlmond.ico");
    this->setWindowIcon(icon);
    this->setWindowTitle("Project Almond[*]");

    translator = new QTranslator();

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
//    }
//    else
//        ui->statusBar->showMessage("Nesto nije bilo u redu sa kreiranjem stabla!");
//DODATO---------------------------------------------------------------------

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("Pera", "Detlic", 'm');

    kreirajToolbar();
    kreirajMestoZaInfo();    
    kreirajPogledZaStablo();
    kreirajOpcije();
    obnoviSkoroOtvarane();

    gOsoba *korena = new gOsoba(stablo->KljucnaOsoba()->Sifra(),
                                QString::fromStdString(stablo->KljucnaOsoba()->Ime()+" "+stablo->KljucnaOsoba()->Prezime()));
    korena->setPos(123,123);
    korena->setZValue(2);
    scena->addItem(korena);
    //readSettings();
}

GlavniProzor::~GlavniProzor()
{
    delete ui;

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

void GlavniProzor::prikaziToolbar()
{
    alati->setVisible(ui->aAlati->isChecked());
    info->setVisible(ui->aInformacije->isChecked());
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
    connect(ui->aInformacije, SIGNAL(triggered()), this, SLOT(prikaziToolbar()));
    connect(tbDetalji,SIGNAL(clicked()),this,SLOT(promeniKursor()));

    connect(ui->aNovoStablo, SIGNAL(triggered()), this, SLOT(novoStablo()));
    connect(ui->aOtvori, SIGNAL(triggered()), this, SLOT(otvoriPostojeceStablo()));
    connect(ui->aZatvori, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->aUgasi, SIGNAL(triggered()),qApp, SLOT(closeAllWindows()));
    connect(ui->aSacuvaj, SIGNAL(triggered()), this, SLOT(sacuvaj()));
    connect(ui->aIzvezi, SIGNAL(triggered()), this, SLOT(sacuvajKao()));//?
    connect(ui->aEngleski,SIGNAL(triggered()),this,SLOT(promeniJezikE()));
    connect(ui->aNemacki,SIGNAL(triggered()),this,SLOT(promeniJezikN()));
    connect(ui->aSrpski,SIGNAL(triggered()),this,SLOT(promeniJezikS()));

    for (int i = 0; i < maxSkoroOtvaranih; ++i)
    {
        skoroOtvaraniAkcije[i] = new QAction(this);
        skoroOtvaraniAkcije[i]->setVisible(false);
        connect(skoroOtvaraniAkcije[i], SIGNAL(triggered()), this, SLOT(otvoriSkoroOtvaraniFajl()));
        ui->aSkoroOtvarani->addAction(skoroOtvaraniAkcije[i]);
    }
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

    connect(alati,SIGNAL(visibilityChanged(bool)),this,SLOT(osveziPrikazAlata(bool)));

}

void GlavniProzor::kreirajMestoZaInfo()
{
    info = new QDockWidget(tr("Informacije"));
    Labela=new QLabel("Informacije");
    info->setWidget(Labela);//i recimo
    Labela->setToolTip("Ovde mozete pronaci informacije o trenutno aktivnoj osobi");
    info->setAllowedAreas(Qt::RightDockWidgetArea
                          | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, info);
    connect(info,SIGNAL(visibilityChanged(bool)),this,SLOT(osveziPrikazInformacija(bool)));
}

short int GlavniProzor::dodajNovuOsobu(QPoint pozicija, bool krvniSrodnik)
{
    short int novaSifra = -1;
    DialogNovaOsoba *d = new DialogNovaOsoba(true, this);
    if (d->exec())
    {
        std::string ime, prezime, rodjenje, smrt, trivija;
        char pol;

        d->popuniPodatke(ime, prezime, pol, rodjenje, smrt, trivija);

        novaSifra = stablo->DodajOsobu(ime, prezime, pol, krvniSrodnik);
        if (novaSifra < 0)
            ui->statusBar->showMessage("Neuspelo dodavanje nove osobe, pokusajte ponovo.", 2000);
        else
        {
            ui->statusBar->showMessage("Uspelo je dodavanje nove osobe.", 2000);
            //WidgetOsoba *novaOsoba = new WidgetOsoba(novaSifra,x,y, this, stabloOkvir);
            std::string tmp = stablo->NadjiOsobuSifrom(novaSifra)->Ime() + " " + stablo->NadjiOsobuSifrom(novaSifra)->Prezime();
            //novaOsoba->postaviImePrezime(tmp);
            //novaOsoba->move(novaOsoba->X(),novaOsoba->Y());
            //novaOsoba->show();
            //setWindowModified(true);
            gOsoba *novaOsoba = new gOsoba(novaSifra, QString::fromStdString(tmp));
            scena->addItem(novaOsoba);
            novaOsoba->setPos(pogled->mapToScene(pozicija));
            novaOsoba->setZValue(1);
            _pozicijeOsoba[novaSifra] = pogled->mapToScene(pozicija);
        }
        delete d;
    }
    return novaSifra;
}

short GlavniProzor::ukloniOsobu(short sifra)
{
            //ne znam koliko ovo ima smisla, pretpostavljam da treba drugacije reagovati
                    //u svakom od slucajeva
                    //ZA SADA IPAK RADE ISTO
    QString upozorenje;
    if (sifra == stablo->KljucnaOsoba()->Sifra())
        upozorenje = tr("Jeste li sigurni da zelite da uklonite korenu osobu?"
                        " To ce prouzrokovati brisanje celog stabla!");
    else
        if (stablo->NadjiOsobuSifrom(sifra)->JeKrvniSrodnik())
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
    poruka->setText(upozorenje);

    poruka->exec();
    if (poruka->clickedButton() == da)
    {
        stablo->UkloniOsobuSifrom(sifra);
        ui->statusBar->showMessage(tr("Uspesno izvrseno uklanjanje izabrane osobe."), 2000);
        //_pozicijeOsoba.erase(druga->Sifra());
        return sifra;
    }
    else
        ui->statusBar->showMessage(tr("Osoba nije uklonjena"), 2000);
    return -1;
}


short GlavniProzor::izmeniOsobu(short sifra)
{
    DijalogIzmenaOsobe *d = new DijalogIzmenaOsobe(stablo->NadjiOsobuSifrom(sifra), this);
    if (d->exec())
        //treba nekako pokupiti podatke nove i uneti ih u stablo, setteri...
        return sifra;
    delete d;
    return -1;
}

void GlavniProzor::promeniKursor()
{
    //TO DO
    //this->setCursor(Qt::CursorShape::ClosedHandCursor);
}

bool GlavniProzor::nastaviti()
{
    if (isWindowModified())
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
        if (poruka->clickedButton() == da)
            return sacuvaj();
        if (poruka->clickedButton() == odustani)
            return false;
    }
    return true;
}

bool GlavniProzor::snimiIzmene(const QString &imeFajla)
{
    //TO DO
    if (!stablo->IspisiFajl(imeFajla))
    {
        ui->statusBar->showMessage(tr("Snimanje otkazano."), 2000);
        return false;
    }
    postaviTrenutniFajl(imeFajla);
    ui->statusBar->showMessage(tr("Fajl je sacuvan."), 2000);
    return true;
}

void GlavniProzor::obnoviSkoroOtvarane()
{
    QMutableStringListIterator i(GlavniProzor::skoroOtvarani);
    while (i.hasNext())
        if (!QFile::exists(i.next()))
            i.remove();
    for (int j = 0; j < maxSkoroOtvaranih; ++j)
    {
        if (j < GlavniProzor::skoroOtvarani.count())
        {
            QString text = tr("&%1 %2")
                           .arg(j + 1)
                           .arg(QFileInfo(GlavniProzor::skoroOtvarani[j]).fileName());
            skoroOtvaraniAkcije[j]->setText(text);
            skoroOtvaraniAkcije[j]->setData(GlavniProzor::skoroOtvarani[j]);
            skoroOtvaraniAkcije[j]->setVisible(true);
        }
        else
            skoroOtvaraniAkcije[j]->setVisible(false);
    }

}

bool GlavniProzor::otvoriFajl(const QString &imeFajla)
{
    if (!stablo->ProcitajFajl(imeFajla))
    {
        ui->statusBar->showMessage(tr("Ucitavanje fajla otkazano."), 2000);
        return false;
    }
    postaviTrenutniFajl(imeFajla);
    ui->statusBar->showMessage(tr("Fajl uspesno ucitan."), 2000);
    return true;
}

void GlavniProzor::postaviTrenutniFajl(const QString &imeFajla)
{
    otvoreniFajl = imeFajla;
    setWindowModified(false);
    if (!otvoreniFajl.isEmpty())
    {
        skoroOtvarani.removeAll(otvoreniFajl);
        skoroOtvarani.prepend(otvoreniFajl);
        qDebug() << "uneo fajl u skoroOtvarane";
        foreach (QWidget *win, QApplication::topLevelWidgets())
        {
            if (GlavniProzor  *glavni = qobject_cast<GlavniProzor*>(win))
                glavni->obnoviSkoroOtvarane();
        }
    }
}

void GlavniProzor::writeSettings()
{
    QSettings settings("MATF", "Project Almond"); //ne znam
    settings.setValue("skoroOtvarani", skoroOtvarani);
    //settings.setValue("pozicijeOsoba", _pozicijeOsoba);
    settings.setValue("geometry", geometry());
}

void GlavniProzor::readSettings()
{
    QSettings settings("MATF", "Project Almond");
    //...
    skoroOtvarani = settings.value("skoroOtvarani").toStringList();
    obnoviSkoroOtvarane();
}

void GlavniProzor::kreirajPogledZaStablo()
{
    pogled = new Stablo();
    scena = new QGraphicsScene(0, 0, pogled->width(), pogled->height(), this);
    pogled->setScene(scena);
    setCentralWidget(pogled);
    connect(pogled, SIGNAL(kliknut(QPoint)), this, SLOT(kliknutoStablo(QPoint)));
    connect(pogled, SIGNAL(vucen(QPoint,QPoint)), this, SLOT(vucenoStablo(QPoint,QPoint)));
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
        {
            qDebug() << "nasli fajl i treba  ga otvoriti";
            otvoriFajl(imeFajla);
        }
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
        writeSettings();
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
    if (otvoreniFajl.isEmpty())
        return sacuvajKao();
    return snimiIzmene(otvoreniFajl);
}

bool GlavniProzor::sacuvajKao()
{
    QString ime = QFileDialog::getSaveFileName(this, tr("Sacuvajte stablo."),
                                               ".", tr("Project Almond (*.alm)")); //EKSTENZIJE
    if (ime.isEmpty())
        return false;
    return snimiIzmene(ime);
}

void GlavniProzor::otvoriSkoroOtvaraniFajl()
{
    if (nastaviti())
    {
        QAction *akcija = qobject_cast<QAction *>(sender());
        if (akcija != nullptr)
            qDebug() << "Otvoriti fajl";
    }
}
void GlavniProzor::promeniJezikE()
{
    if(ui->aEngleski->isChecked()){

             bool ok=translator->load("ProjectAlmond_en.qm");
             qDebug("translation %d", ok);
              qApp->installTranslator(translator);
                ui->retranslateUi(this);
                //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
                //retranslate();
                //DialogNovaOsoba *d=new DialogNovaOsoba();
                //d->ui.retranslateUi(d);
                //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
                //d1->ui.retranslateUi(d1);
                qDebug() << "English";
                ui->aNemacki->setChecked(false);
                 ui->aSrpski->setChecked(false);
    }
    else if(ui->aNemacki->isChecked()){
        bool ok=translator->load("ProjectAlmond_ge.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
           //retranslate();
           //DialogNovaOsoba *d=new DialogNovaOsoba();
           //d->ui.retranslateUi(d);
           //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
           //d1->ui.retranslateUi(d1);
           ui->aEngleski->setChecked(false);
            ui->aSrpski->setChecked(false);
           qDebug() << "Deutsch";

    }
    else {
        ui->aSrpski->setChecked(true);
        translator= new QTranslator();//mozda ovo da resimo drugacije, jer ovako imam curenje memorije, a svejedno nece da vrati na pocetno stanje
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
           //retranslate();
           //DialogNovaOsoba *d=new DialogNovaOsoba();
           //d->ui.retranslateUi(d);
           //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
           //d1->ui.retranslateUi(d1);
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
          qDebug() << "Srpski";
    }

}

void GlavniProzor::promeniJezikN()
{
    if(ui->aNemacki->isChecked()){
            bool ok=translator->load("ProjectAlmond_ge.qm");
            qDebug("translation %d", ok);
             qApp->installTranslator(translator);
               ui->retranslateUi(this);
               //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
               //retranslate();
               //DialogNovaOsoba *d=new DialogNovaOsoba();
               //d->ui.retranslateUi(d);
               //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
               //d1->ui.retranslateUi(d1);
               ui->aEngleski->setChecked(false);
                ui->aSrpski->setChecked(false);
               qDebug() << "Deutsch";

        }

    else if(ui->aEngleski->isChecked()){

        bool ok=translator->load("ProjectAlmond_en.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
           //retranslate();
           //DialogNovaOsoba *d=new DialogNovaOsoba();
           //d->ui.retranslateUi(d);
           //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
           //d1->ui.retranslateUi(d1);
           qDebug() << "English";
           ui->aNemacki->setChecked(false);
            ui->aSrpski->setChecked(false);
}
    else {
        ui->aSrpski->setChecked(true);
        translator= new QTranslator();//mozda ovo da resimo drugacije, jer ovako imam curenje memorije, a svejedno nece da vrati na pocetno stanje
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
           //retranslate();
           //DialogNovaOsoba *d=new DialogNovaOsoba();
           //d->ui.retranslateUi(d);
           //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
           //d1->ui.retranslateUi(d1);
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
          qDebug() << "Srpski";
    }

}
void GlavniProzor::promeniJezikS()
{

    if(ui->aSrpski->isChecked())
    {
        translator= new QTranslator();//mozda ovo da resimo drugacije, jer ovako imam curenje memorije, a svejedno nece da vrati na pocetno stanje
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
           //retranslate();
           //DialogNovaOsoba *d=new DialogNovaOsoba();
           //d->ui.retranslateUi(d);
           //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
           //d1->ui.retranslateUi(d1);
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
          qDebug() << "Srpski";
    }
    else if(ui->aEngleski->isChecked()){

        bool ok=translator->load("ProjectAlmond_en.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
           //retranslate();
           //DialogNovaOsoba *d=new DialogNovaOsoba();
           //d->ui.retranslateUi(d);
           //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
           //d1->ui.retranslateUi(d1);
           qDebug() << "English";
           ui->aNemacki->setChecked(false);
            ui->aSrpski->setChecked(false);
}
    else if(ui->aNemacki->isChecked()){
            bool ok=translator->load("ProjectAlmond_ge.qm");
            qDebug("translation %d", ok);
             qApp->installTranslator(translator);
               ui->retranslateUi(this);
               //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
               //retranslate();
               //DialogNovaOsoba *d=new DialogNovaOsoba();
               //d->ui.retranslateUi(d);
               //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
               //d1->ui.retranslateUi(d1);
               ui->aEngleski->setChecked(false);
                ui->aSrpski->setChecked(false);
               qDebug() << "Deutsch";

        }
    else{
        ui->aSrpski->setChecked(true);
        translator= new QTranslator();//mozda ovo da resimo drugacije, jer ovako imam curenje memorije, a svejedno nece da vrati na pocetno stanje
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           //ovde pokrecemo da se i ostali dialozi prevedu i sve sto treba rucno
           //retranslate();
           //DialogNovaOsoba *d=new DialogNovaOsoba();
           //d->ui.retranslateUi(d);
           //DialogIzmenaOsobe *d1=new DialogIzmenaOsobe();
           //d1->ui.retranslateUi(d1);
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
          qDebug() << "Srpski";
    }
}

void GlavniProzor::osveziPrikazAlata(bool Vidljivost)
{
    ui->aAlati->setChecked(Vidljivost);
}

void GlavniProzor::osveziPrikazInformacija(bool Vidljivost)
{
    ui->aInformacije->setChecked(Vidljivost);
}

void GlavniProzor::kliknutoStablo(QPoint pozicija)
{
    if (tbDetalji->isChecked())
    {
        gOsoba *item = qgraphicsitem_cast<gOsoba*>(pogled->itemAt(pozicija));
        if (item == nullptr)
        {
            popuniInformacije(-1);
            return;
        }
        qDebug() << "opisati selektovano";
        popuniInformacije(item->Sifra());
    }
    else
        if  (tbBrisi->isChecked())
        {
            gOsoba *item = qgraphicsitem_cast<gOsoba*>(pogled->itemAt(pozicija));
            if (item == nullptr)
                return;
            qDebug() << "obrisati";
            if (ukloniOsobu(item->Sifra()) == item->Sifra())
            {
                scena->removeItem(item);
                setWindowModified(true);
            }
        }
        else
            if (tbMenjaj->isChecked())
            {
                gOsoba *item = qgraphicsitem_cast<gOsoba*>(pogled->itemAt(pozicija));
                if (item == nullptr)
                    return;
                qDebug() << "menjati podatke";
                if (izmeniOsobu(item->Sifra()) == item->Sifra())
                    setWindowModified(true);
            }
            else
                qDebug() << "nista";

    tbDetalji->setChecked(true);
}

void GlavniProzor::vucenoStablo(QPoint prva, QPoint druga)
{
    if (tbMuzZena->isChecked() || tbBratSestra->isChecked() || tbRoditeljDete->isChecked())
    {
        /*kada dodam relacije cu razdvojiti u tri slucaja*/
        qDebug() << "povezati";
        //gOsoba *prvi = qgraphicsitem_cast<gOsoba*>(pogled->itemAt(prva));
        gOsoba *prvi = qgraphicsitem_cast<gOsoba*>(scena->itemAt(pogled->mapToScene(prva), QTransform()));
        if (prvi == nullptr)
        {
            qDebug()<<"nesto ne valja";
            return;
        }

        /*novu "relaciju" crtamo na sredini i "ispod" ostalog*/
        QPoint poz((prva.x()+druga.x())/2, (prva.y()+druga.y())/2);
        QGraphicsRectItem
                *foo = new QGraphicsRectItem(QRect(0,0,30,60));
        foo->setPen(QPen(Qt::blue, 5));
        foo->setBrush(Qt::black);
        foo->setPos(pogled->mapToScene(poz));
        foo->setZValue(0);

    /*novu "osobu" crtamo na mestu gde je pusten mis, "iznad" */
        scena->addItem(foo);
        if (dodajNovuOsobu(druga, true) >= 0)
            setWindowModified(true);
    }
    else
        if (tbPomeranje->isChecked())
        {
            gOsoba *item = qgraphicsitem_cast<gOsoba*>(pogled->itemAt(prva));
            if (item == nullptr)
                return;
            qDebug() << "pomeriti";
            item->moveBy(druga.x()-prva.x(), druga.y()-prva.y());
            setWindowModified(true);
        }
        else
            {
                qDebug() << "nista";
            }
    tbDetalji->setChecked(true);
}

QStringList GlavniProzor::skoroOtvarani;

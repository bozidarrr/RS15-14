#include "GUI/glavniprozor.h"
#include "ui_glavniprozor.h"
#include <QToolBar>
#include <QDockWidget>
#include "dijalogizmenaosobe.h"
#include "dialognovaosoba.h"
#include "dijalogrelacija.h"
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <QPoint>
#include <QPointF>
#include <QAction>
#include <QSettings>
#include <QTranslator>
#include <QTransform>
#include <QTextBrowser>
#include "GUI/dijalogpretrage.h"
#include <QDebug>
#include "alati/uredjivanje.h"
#include <iostream>


GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    QIcon icon(":images/images/ProjectAlmond.ico");
    this->setWindowIcon(icon);
    this->setWindowTitle(tr("Project Almond[*]"));

    translator = new QTranslator();

    bool ok=translator->load(":/jezici/ProjectAlmond_sr.qm");
    qDebug("translation %d", ok);
    qApp->installTranslator(translator);
    ui->retranslateUi(this);


    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("Pera", "Detlic", "m",
                                 QDate::currentDate(), QDate::currentDate(), true);

    kreirajToolbar();
    kreirajMestoZaInfo();    
    kreirajPogledZaStablo();
    kreirajOpcije();
    obnoviSkoroOtvarane();
    //-------Pravi se stablo i korena osoba-------//
    GOsoba *korena = new GOsoba(stablo->KljucnaOsoba()->Sifra(),
                                (stablo->KljucnaOsoba()->ImePrezime()));//DOPUNITI
    QPointF centar(pogled->viewport()->rect().center());
    korena->setPos(pogled->mapToScene(centar.x(), centar.y()));
    korena->setZValue(2);
    scena->addItem(korena);
    _pozicijeOsoba[korena->Sifra()] = korena;
    connect(stablo, SIGNAL(obrisanaOsoba(short)), korena, SLOT(skloniSeSaScene(short)));
      retranslate();
    //-------Pravi se stablo i korena osoba-------//

    //readSettings();
}

GlavniProzor::~GlavniProzor()
{
    //if (stablo != nullptr)
    //    delete stablo;
    delete ui;

}

void GlavniProzor::popuniInformacije(short sifra, TipZaInfo tip)
{
    if (sifra == -1 || tip == NISTA)
    {
        ui->zaInformacije->setPlaceholderText("Informacije");
        return;
    }
    if (tip == INFO_OSOBA)
    {
        Osoba *osoba = stablo->NadjiOsobuSifrom(sifra);
        if (osoba)
        {
            ui->zaInformacije->clear();
            ui->zaInformacije->append(osoba->Ime());
            ui->zaInformacije->append(osoba->Prezime());
            QDate datum = osoba->DatumRodjenja();
            if (datum.isValid())
            {
                ui->zaInformacije->append(tr("Datum rodjenja:"));
                ui->zaInformacije->append(datum.toString("dd.MM.yyyy."));
            }
            datum = osoba->DatumSmrti();
            if (datum.isValid())
            {
                ui->zaInformacije->append(tr("Datum smrti: "));
                ui->zaInformacije->append(datum.toString("dd.MM.yyyy."));
            }
            //qDebug() << osoba->Nivo();
        }
    }
    if (tip == INFO_BRAK)
        ui->zaInformacije->append(stablo->NadjiBrakSifrom(sifra)->Trivija());
    if (tip == INFO_DETE)
        ui->zaInformacije->append(stablo->NadjiDeteSifrom(sifra)->Trivija());
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

    connect(ui->aNovoStablo, SIGNAL(triggered()), this, SLOT(novoStablo()));
    connect(ui->aOtvori, SIGNAL(triggered()), this, SLOT(otvoriPostojeceStablo()));
    connect(ui->aZatvori, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->aUgasi, SIGNAL(triggered()),qApp, SLOT(closeAllWindows()));
    connect(ui->aSacuvaj, SIGNAL(triggered()), this, SLOT(sacuvaj()));
    connect(ui->aIzvezi, SIGNAL(triggered()), this, SLOT(sacuvajKao()));//?
    connect(ui->aEngleski,SIGNAL(triggered()),this,SLOT(promeniJezikE()));
    connect(ui->aNemacki,SIGNAL(triggered()),this,SLOT(promeniJezikN()));
    connect(ui->aSrpski,SIGNAL(triggered()),this,SLOT(promeniJezikS()));
    connect(ui->aSpanski,SIGNAL(triggered()),this,SLOT(promeniJezikSpanski()));//--------------------ZA SPANSKIIIIII
    connect(ui->aSamoKrv, SIGNAL(triggered()), this, SLOT(prikaziSakrijTudje()));
    connect(ui->actionPretraga, SIGNAL(triggered()), this, SLOT(izvrsiPretragu()));

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

    tbUredi->setCheckable(false);
    connect(tbUredi, SIGNAL(clicked()), this, SLOT(urediStablo()));

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
    /** bilo bi lepo da je malo uzi :) **/
    info->setWidget(ui->zaInformacije);
    ui->zaInformacije->setPlaceholderText("Informacije");
    info->setAllowedAreas(Qt::RightDockWidgetArea
                          | Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, info);
    connect(info,SIGNAL(visibilityChanged(bool)),this,SLOT(osveziPrikazInformacija(bool)));
}

GOsoba *GlavniProzor::dodajNovuOsobu(QPoint pozicija, bool krvniSrodnik)
{
    short int novaSifra = -1;
    GOsoba *novaOsoba = nullptr;
    DialogNovaOsoba *d = new DialogNovaOsoba(this);
    if (d->exec())
    {
        QString ime, prezime;
        QDate rodjenje, smrt;
        QString pol;

        if (d->popuniPodatke(ime, prezime, pol, rodjenje, smrt))
            novaSifra = stablo->DodajOsobu(ime, prezime, pol, rodjenje, smrt, krvniSrodnik);
        else
            novaSifra = stablo->DodajNNLice(krvniSrodnik);
        if (novaSifra >= 0)
        {          
            novaOsoba = new GOsoba(novaSifra, (stablo->NadjiOsobuSifrom(novaSifra)->ImePrezime()));
            novaOsoba->setPos(pogled->mapToScene(pozicija));
            novaOsoba->setZValue(2);
            _pozicijeOsoba[novaSifra] = novaOsoba;
            connect(stablo, SIGNAL(obrisanaOsoba(short)), novaOsoba, SLOT(skloniSeSaScene(short)));
        }   
    }
    delete d;
    return novaOsoba;
}

short GlavniProzor::ukloniOsobu(short sifra)
{
    QString upozorenje;
    if (sifra == stablo->KljucnaOsoba()->Sifra())
        upozorenje = tr("Jeste li sigurni da zelite da uklonite korenu osobu?"
                        " To ce prouzrokovati brisanje celog stabla!");
    else
        if (stablo->NadjiOsobuSifrom(sifra)->JeKrvniSrodnik())
            upozorenje = tr("Jeste li sigurni da zelite da uklonite selektovanu osobu,"
                            "a time i sve njene supruznike i potomke?");
        else
            upozorenje = tr("Jeste li sigurni da zelite da uklonite selektovanu osobu i njene potomke?");

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
        uredjeno = false;
        return sifra;
    }
    else
        ui->statusBar->showMessage(tr("Osoba nije uklonjena."), 2000);
    return -1;
}

short GlavniProzor::dodajNovoDete(GRelacija *brak, GOsoba *dete)
{
    DijalogRelacija *d = new DijalogRelacija(this);
    short int novaSifra = -1;
    GRelacija *novaRelacija;
    QString trivija;

    if (d->exec())
    {
        d->popuniPodatke(trivija);
        novaSifra = stablo->DodajDete(brak->Sifra(), dete->Sifra(), trivija);
        if (novaSifra >= 0)
        {
            novaRelacija = new GRelacija(novaSifra, brak->pos(), dete->pos(), false);
        }
        if (novaRelacija != nullptr)
        {
            novaRelacija->setZValue(1);
            scena->addItem(novaRelacija);
            connect(brak, SIGNAL(pomerilaSe(QPointF)), novaRelacija, SLOT(pomeriPrvu(QPointF)));
            connect(dete, SIGNAL(pomerilaSe(QPointF)), novaRelacija, SLOT(pomeriDrugu(QPointF)));
            connect(stablo, SIGNAL(obrisanaVezaDete(short)), novaRelacija, SLOT(ukloniSeSaScene(short)));
        }
    }
    delete d;
    return novaSifra;
}

short GlavniProzor::dodajNoviBrak(GOsoba *prva, GOsoba *druga)
{
    DijalogRelacija *d = new DijalogRelacija(this);
    short int novaSifra = -1;
    GRelacija *novaRelacija;
    QString trivija;
    if (d->exec())
    {
        d->popuniPodatke(trivija);
        novaSifra = stablo->DodajBrak(prva->Sifra(), druga->Sifra(), trivija);
        if (novaSifra >= 0)
        {
            novaRelacija = new GRelacija(novaSifra, prva->pos(), druga->pos(), true);
            _pozicijeBrakova[novaSifra] = novaRelacija->pos();
        }

        if (novaRelacija != nullptr)
        {
            novaRelacija->setZValue(1);
            scena->addItem(novaRelacija);
            connect(prva, SIGNAL(pomerilaSe(QPointF)), novaRelacija, SLOT(pomeriPrvu(QPointF)));
            connect(druga, SIGNAL(pomerilaSe(QPointF)), novaRelacija, SLOT(pomeriDrugu(QPointF)));
            connect(stablo, SIGNAL(obrisanaVezaBrak(short)), novaRelacija, SLOT(ukloniSeSaScene(short)));
        }
    }
    delete d;
    return novaSifra;
}


short GlavniProzor::izmeniOsobu(short sifra)
{
    DijalogIzmenaOsobe *d = new DijalogIzmenaOsobe(stablo->NadjiOsobuSifrom(sifra), this);
    connect(d, SIGNAL(azurirajRodjenje(QDate,QDate,short)), stablo, SLOT(azurirajIndeksRodj(QDate,QDate,short)));
    if (d->exec())
    {
        ui->statusBar->showMessage(tr("Uspesno unete izmene."), 2000);
        delete d;
        return sifra;
    }
    delete d;
    return -1;
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
    //RekonstruisiStablo();
    return true;
}

//Jos ne radi sve sto treba, ali se cini da je na dobrom putu
void GlavniProzor::RekonstruisiStablo()
{
    _pozicijeOsoba.clear();
    _pozicijeBrakova.clear();
    int x = 100, y = 100;
    for (auto a : stablo->Osobe())
    {
        GOsoba *g = new GOsoba(a.first, a.second->ImePrezime());
        scena->addItem(g);
        g->setPos(x,y);
        x+=100; y+=100;
        _pozicijeOsoba[a.first] = g;
    }
    for (auto b : stablo->Brakovi())
    {
        Brak *brak  = b.second;
        QPointF prva(_pozicijeOsoba.at(brak->SifraNase())->pos());
        QPointF druga(_pozicijeOsoba.at(brak->SifraTudje())->pos());
        GRelacija *g = new GRelacija(b.first, prva, druga ,true);
        _pozicijeBrakova[b.first] = g->pos();
        scena->addItem(g);
    }
    for (auto d : stablo->Deca())
    {
        Dete * dete  = d.second;
        dete->SifraRoditeljskogOdnosa();
        QPointF prva(_pozicijeBrakova.at(dete->SifraRoditeljskogOdnosa()));
        QPointF druga(_pozicijeOsoba.at(dete->SifraOsobe())->pos());
        GRelacija *g = new GRelacija(d.first, prva, druga ,false);
        scena->addItem(g);
    }
}

void GlavniProzor::postaviTrenutniFajl(const QString &imeFajla)
{
    otvoreniFajl = imeFajla;
    setWindowModified(false);
    if (!otvoreniFajl.isEmpty())
    {
        skoroOtvarani.removeAll(otvoreniFajl);
        skoroOtvarani.prepend(otvoreniFajl);
        //qDebug() << "uneo fajl u skoroOtvarane";
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
    scena = new QGraphicsScene(0, 0, pogled->width(), pogled->height());
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
        //qDebug() << "treba otvoriti postojeci fajl";
        QString imeFajla = QFileDialog::getOpenFileName(this,
                                                        tr("Otvorite postojece stablo."),
                                                        tr("ProjectAlmond (*.alm)")); //sta su nam ekstenzije?
        if (!imeFajla.isEmpty())
        {
            //qDebug() << "nasli fajl i treba  ga otvoriti";
            otvoriFajl(imeFajla);
        }
    }
}

void GlavniProzor::closeEvent(QCloseEvent *event)
{
    if (nastaviti())
    {
        writeSettings();
        //qDebug() << "Zatvaramo fajl";
        event->accept();
    }
    else
    {
        //qDebug() << "Otkazano izlazenje";
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
        if (akcija)
        {
            otvoriFajl(akcija->data().toString());
            //qDebug() << "Otvoriti fajl";
        }
    }
}
void GlavniProzor::promeniJezikE()
{
    if(ui->aEngleski->isChecked()){

             bool ok=translator->load(":/jezici/ProjectAlmond_en.qm");
             qDebug("translation %d", ok);
              qApp->installTranslator(translator);
                ui->retranslateUi(this);
                 retranslate();
                qDebug() << "English";
                ui->aNemacki->setChecked(false);
                 ui->aSrpski->setChecked(false);
                  ui->aSpanski->setChecked(false);
    }
    else if(ui->aNemacki->isChecked()){
        bool ok=translator->load(":/jezici/ProjectAlmond_gr.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           retranslate();
           ui->aEngleski->setChecked(false);
            ui->aSrpski->setChecked(false);
             ui->aSpanski->setChecked(false);
           qDebug() << "Deutsch";

    }
    else if (ui->aSpanski->isChecked()){
        bool ok=translator->load(":/jezici/ProjectAlmond_es.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           retranslate();
           ui->aEngleski->setChecked(false);
           ui->aNemacki->setChecked(false);
            ui->aSrpski->setChecked(false);
           qDebug() << "Espanol";

    }
    else {
        ui->aSrpski->setChecked(true);
        bool ok=translator->load(":/jezici/ProjectAlmond_sr.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
          retranslate();
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
             ui->aSpanski->setChecked(false);
          qDebug() << "Srpski";
    }

}

void GlavniProzor::promeniJezikN()
{
    if(ui->aNemacki->isChecked()){
            bool ok=translator->load(":/jezici/ProjectAlmond_gr.qm");
            qDebug("translation %d", ok);
             qApp->installTranslator(translator);
               ui->retranslateUi(this);
                retranslate();
               ui->aEngleski->setChecked(false);
                ui->aSrpski->setChecked(false);
                 ui->aSpanski->setChecked(false);
               qDebug() << "Deutsch";

        }

    else if(ui->aEngleski->isChecked()){

        bool ok=translator->load(":/jezici/ProjectAlmond_en.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
            retranslate();
           qDebug() << "English";
           ui->aNemacki->setChecked(false);
            ui->aSrpski->setChecked(false);
             ui->aSpanski->setChecked(false);
    }
            else if (ui->aSpanski->isChecked()){
                bool ok=translator->load(":/jezici/ProjectAlmond_es.qm");
                qDebug("translation %d", ok);
                 qApp->installTranslator(translator);
                   ui->retranslateUi(this);
                   retranslate();
                   ui->aEngleski->setChecked(false);
                   ui->aNemacki->setChecked(false);
                    ui->aSrpski->setChecked(false);
                   qDebug() << "Espanol";

            }

    else {
        ui->aSrpski->setChecked(true);
        bool ok=translator->load(":/jezici/ProjectAlmond_sr.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           retranslate();
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
             ui->aSpanski->setChecked(false);
          qDebug() << "Srpski";
    }

}
void GlavniProzor::promeniJezikS()
{

    if(ui->aSrpski->isChecked())
    {
        bool ok=translator->load(":/jezici/ProjectAlmond_sr.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           retranslate();
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
             ui->aSpanski->setChecked(false);
          qDebug() << "Srpski";
    }
    else if(ui->aEngleski->isChecked()){

        bool ok=translator->load(":/jezici/ProjectAlmond_en.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           retranslate();
           qDebug() << "English";
           ui->aNemacki->setChecked(false);
            ui->aSrpski->setChecked(false);
             ui->aSpanski->setChecked(false);
}
    else if(ui->aNemacki->isChecked()){
            bool ok=translator->load(":/jezici/ProjectAlmond_gr.qm");
            qDebug("translation %d", ok);
             qApp->installTranslator(translator);
               ui->retranslateUi(this);
                retranslate();
               ui->aEngleski->setChecked(false);
                ui->aSrpski->setChecked(false);
                 ui->aSpanski->setChecked(false);
               qDebug() << "Deutsch";

        }
    else if (ui->aSpanski->isChecked()){
        bool ok=translator->load(":/jezici/ProjectAlmond_es.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           retranslate();
           ui->aEngleski->setChecked(false);
           ui->aNemacki->setChecked(false);
            ui->aSrpski->setChecked(false);
           qDebug() << "Espanol";

    }
    else{
        ui->aSrpski->setChecked(true);
        bool ok=translator->load(":/jezici/ProjectAlmond_sr.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
            retranslate();
           ui->aEngleski->setChecked(false);
            ui->aNemacki->setChecked(false);
          qDebug() << "Srpski";
    }
}
void GlavniProzor::promeniJezikSpanski(){
    if (ui->aSpanski->isChecked()){
               bool ok=translator->load(":/jezici/ProjectAlmond_es.qm");
               qDebug("translation %d", ok);
                qApp->installTranslator(translator);
                  ui->retranslateUi(this);
                  retranslate();
                  ui->aEngleski->setChecked(false);
                  ui->aNemacki->setChecked(false);
                   ui->aSrpski->setChecked(false);
                  qDebug() << "Espanol";

           }

       else if(ui->aNemacki->isChecked()){
               bool ok=translator->load(":/jezici/ProjectAlmond_gr.qm");
               qDebug("translation %d", ok);
                qApp->installTranslator(translator);
                  ui->retranslateUi(this);
                   retranslate();
                  ui->aEngleski->setChecked(false);
                   ui->aSrpski->setChecked(false);
                    ui->aSpanski->setChecked(false);
                  qDebug() << "Deutsch";

           }
       else if(ui->aEngleski->isChecked()){

        bool ok=translator->load(":/jezici/ProjectAlmond_en.qm");
        qDebug("translation %d", ok);
         qApp->installTranslator(translator);
           ui->retranslateUi(this);
           retranslate();
           qDebug() << "English";
           ui->aNemacki->setChecked(false);
            ui->aSrpski->setChecked(false);
             ui->aSpanski->setChecked(false);
}
       else{
           ui->aSrpski->setChecked(true);
           bool ok=translator->load(":/jezici/ProjectAlmond_sr.qm");
           qDebug("translation %d", ok);
            qApp->installTranslator(translator);
              ui->retranslateUi(this);
               retranslate();
              ui->aEngleski->setChecked(false);
               ui->aNemacki->setChecked(false);
                ui->aSpanski->setChecked(false);
             qDebug() << "Srpski";
       }
}

void GlavniProzor::retranslate()
{


   // toolbar->tr("Alati");
    //alati->tr("Alati");
    //info ->tr("Informacije");



  //  Labela->setText(tr("Informacije"));
    // Labela->setToolTip(tr("Ovde mozete pronaci informacije o trenutno aktivnoj osobi"));
       this->setWindowTitle(tr("Project Almond[*]"));

     tbMuzZena->setToolTip(tr("Dodajte u stablo supruznika nekoj od osoba"));
     tbRoditeljDete->setToolTip(tr("Dodajte u neku vezu novo dete"));
     tbBratSestra->setToolTip(tr("Dodajte u stablo brata ili sestru nekoj osobi"));
     tbPomeranje->setToolTip(tr("Pomerite rucicom odabranu osobu ili relaciju na crtezu"));
     tbDetalji->setToolTip(tr("Detalji o odabranoj osobi ili odnosu"));
     tbMenjaj->setToolTip(tr("Izmenite podatke o odabranoj osobi ili odnosu"));
     tbBrisi->setToolTip(tr("Obrisite osobu ili relaciju iz stabla"));
     tbUredi->setToolTip(tr("Rasporedite cvorove stabla automatski"));

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
    ui->zaInformacije->clear();
    ui->zaInformacije->setPlaceholderText("Informacije");
    if (tbDetalji->isChecked())
    {
        GOsoba *osoba = qgraphicsitem_cast<GOsoba*>(pogled->itemAt(pozicija));
        GRelacija *relacija = qgraphicsitem_cast<GRelacija*>(pogled->itemAt(pozicija));
        if (osoba == nullptr && relacija == nullptr)
        {
            popuniInformacije(-1, NISTA);
            return;
        }
        if (osoba)
            popuniInformacije(osoba->Sifra(), INFO_OSOBA);
        if (relacija)
        {
            if (relacija->BrakJe())
                popuniInformacije(relacija->Sifra(), INFO_BRAK);
            else
                popuniInformacije(relacija->Sifra(), INFO_DETE);
        }
    }
    if  (tbBrisi->isChecked())
    {
        GOsoba *item = qgraphicsitem_cast<GOsoba*>(pogled->itemAt(pozicija));
        if (item == nullptr)
        {
            tbDetalji->setChecked(true);
            return;
        }
        item->promeniStil(GOsoba::SELEKTOVANA);
        if (ukloniOsobu(item->Sifra()) == item->Sifra())
        {
            _pozicijeOsoba.erase(item->Sifra());
            setWindowModified(true);
        }
        else
            item->promeniStil(GOsoba::OBICNA);
    }
    if (tbMenjaj->isChecked())
    {
        GOsoba *item = qgraphicsitem_cast<GOsoba*>(pogled->itemAt(pozicija));
        if (item == nullptr)
        {
            tbDetalji->setChecked(true);
            return;
        }
        if (izmeniOsobu(item->Sifra()) == item->Sifra())
        {
            item->promeniIme((stablo->NadjiOsobuSifrom(item->Sifra())->ImePrezime()));
            setWindowModified(true);
        }
    }
    tbDetalji->setChecked(true);
}

void GlavniProzor::vucenoStablo(QPoint prva, QPoint druga)
{
    ui->zaInformacije->clear();
    ui->zaInformacije->setPlaceholderText("Informacije");
    if (tbMuzZena->isChecked())// || tbBratSestra->isChecked()
    {
        GOsoba *novaOsoba;
        GOsoba *staraOsoba = qgraphicsitem_cast<GOsoba*>(scena->itemAt(pogled->mapToScene(prva), QTransform()));
        if (staraOsoba == nullptr || stablo->NadjiOsobuSifrom(staraOsoba->Sifra()) == nullptr)//ovo drugo ne bi smelo...
        {
            tbDetalji->setChecked(true);
            return;
        }
        if (!stablo->NadjiOsobuSifrom(staraOsoba->Sifra())->JeKrvniSrodnik())
        {
            tbDetalji->setChecked(true);
            ui->statusBar->showMessage(tr("Moguce je dodati supruznika samo krvnim srodnicima."), 2000);//??!
            return;
        }
        if ((novaOsoba = dodajNovuOsobu(druga, false)) != nullptr)
        {
            short novaSifraBraka = dodajNoviBrak(staraOsoba, novaOsoba);
            if (novaSifraBraka >= 0)
            {
                scena->addItem(novaOsoba);
                //dodavanje je definitivno pa ni stablo vise ne mora biti uredjeno
                uredjeno = false;
                setWindowModified(true);
                ui->statusBar->showMessage(tr("Dodavanje nove osobe u stablo je proslo uspesno."), 2000);
            }
            else
            {
                /*! ako smo odustali od pravljenja braka, ne treba ni osobu dodati,
                 * tj, treba je obrisati iz stabla
                */
                stablo->UkloniOsobuSifrom(novaOsoba->Sifra());
                ui->statusBar->showMessage(tr("Dodavanje nove osobe i relacije otkazano."), 2000);
            }
        }
        else
            ui->statusBar->showMessage(tr("Dodavanje nove osobe i relacije otkazano."), 2000);
    }
    if (tbRoditeljDete->isChecked())
    {
        GOsoba *novoDete;
        GRelacija *brak = qgraphicsitem_cast<GRelacija*>(pogled->itemAt(prva));
        if (brak == nullptr || !brak->BrakJe() || stablo->NadjiBrakSifrom(brak->Sifra()) == nullptr)
        {
            tbDetalji->setChecked(true);
            return;
        }
        if ((novoDete = dodajNovuOsobu(druga, true)) != nullptr)
        {
            short novaSifra = dodajNovoDete(brak, novoDete);
            if (novaSifra >= 0)
            {
                scena->addItem(novoDete);
                //dodavanje je definitivno pa ni stablo vise ne mora biti uredjeno
                uredjeno = false;
                setWindowModified(true);
            }
            else
            {
                stablo->UkloniOsobuSifrom(novoDete->Sifra());
                ui->statusBar->showMessage(tr("Dodavanje novog deteta otkazano."), 2000);
            }
        }
        else
            ui->statusBar->showMessage(tr("Dodavanje novog deteta otkazano."), 2000);
    }
    if (tbPomeranje->isChecked())
    {
        GOsoba *item = qgraphicsitem_cast<GOsoba*>(pogled->itemAt(prva));
        if (item == nullptr)
        {
            tbDetalji->setChecked(true);
            return;
        }
        item->moveBy(druga.x()-prva.x(), druga.y()-prva.y());
        uredjeno = false;
        item->obavestiRelacije();
        setWindowModified(true);
    }
    tbDetalji->setChecked(true);
}

void GlavniProzor::urediStablo()
{
    if (uredjeno)//popravice se ovo
        return;
    //idemo po nivoima
    //osoba crta sebe i svoje supruznike (ZASTO smo dozvolili poligamiju!?)
    //
    //na osnovu toga im preracunavam koordinate
    //int dodajVisinu = 1;
    if (ui->aPreciGore->isChecked())
        qDebug() <<"uredi preci gore";
    else{
        qDebug() << "uredi preci dole";
        //dodajVisinu = -1;
    }
    std::vector<int> nivoi(stablo->Nivoi());
    uredjivanje u;
    sirine = u.IzracunajSirinuCelije(nivoi, stablo->maxBrakova()+1);

    QPointF centar = pogled->mapToScene(pogled->viewport()->rect().center());


    short sifraKljucne = stablo->KljucnaOsoba()->Sifra();
    QPointF pozicija(centar.x() - 85*stablo->osobaImaBrakova(sifraKljucne), centar.y());
    scena->setSceneRect(0,0,std::max(u.Sirina()+200, pogled->width()), std::max(pogled->height(), (int)nivoi.size()*200));

    pomeriOsobu(sifraKljucne, pozicija, 0);

    pogled->centerOn(_pozicijeOsoba[sifraKljucne]);
}

//osoba te sifre se smesta sa svojim supruznicima u svoj pravougaounik
void GlavniProzor::pomeriOsobu(short sifra, QPointF pocetak, int nivo)
{
    /** TO DO **/
    //ona i supruznici se rasporedjuju u pravougaonik koji pocinje na x, sirine koju imamo u vektoru
    //for svako dete i
    //pomeriOsobu (sifraDeteta, x + i*sirina[j+1])
    int smer = -1;
    if (ui->aPreciGore->isChecked())
        smer = 1;
    _pozicijeOsoba[sifra]->setPos(pocetak);
    _pozicijeOsoba[sifra]->obavestiRelacije();
    std::vector<short> *supruznici = stablo->ListaSupruznika(sifra);
    int broj = supruznici->size();
    for (int i = 0; i < broj; i++)
    {
        _pozicijeOsoba[(*supruznici)[i]]->setPos(pocetak.x() + (i+1)*(*sirine)[nivo]/(broj+1), pocetak.y());
        _pozicijeOsoba[supruznici->at(i)]->obavestiRelacije();
    }
    delete supruznici;

    std::vector<short> *deca = stablo->ListaDece(sifra);
    broj = deca->size();
    for (int i = 0; i < broj; i++)
    {
        pomeriOsobu(deca->at(i), QPointF(pocetak.x() + i*sirine->at(nivo+1), pocetak.y() + smer*140), nivo+1);
    }
    delete deca;
}


void GlavniProzor::prikaziSlavljenike(const QDate &datum)
{
    //ovde sam mislila da uvedemo korisniku mogucnost da izabere datum, ne samo danasnji datum da bude
    std::vector<short> *v = stablo->KomeJeSveRodjendan(datum);
    for (short sifra : *v)
        qDebug() << sifra;
    //idemo po sifri i postavljamo im poseban stil
    delete v;
}

void GlavniProzor::prikaziSakrijTudje()
{
    std::vector<short> *zaSakrivanje = stablo->NisuKrvniSrodnici();
    for (short sifra: *zaSakrivanje)
        _pozicijeOsoba[sifra]->setVisible(!ui->aSamoKrv->isChecked());
//koliko ovo ima smisla ja ne znam

//    if (ui->aSamoKrv->isChecked())
//        qDebug() << "sakriti tudje";
//    else
//        qDebug() << "vratiti tudje";

}

void GlavniProzor::izvrsiPretragu()
{
    DijalogPretrage *d = new DijalogPretrage(this);
    if (d->exec())
    {//0 ime, 1 prezime, 2 datum rodjenja, 3 datum smrti, 4 pol
        int kriterijum;
        int opcija;
        QString podatak;
        d->procitajPodatke(opcija, kriterijum, podatak);
//        qDebug() << "pretrazi";
//        qDebug() << opcija;
//        qDebug() << kriterijum;
//        qDebug() << podatak;
        std::vector<short> *trazene;
        switch(opcija)
        {
        case 0:
            trazene = stablo->PretragaPoImenu(podatak, kriterijum);
            break;
        case 1:
            trazene = stablo->PretragaPoPrezimenu(podatak, kriterijum);
            break;
        case 2:
            trazene = stablo->PretragaPoDatumuRodjenja(QDate::fromString(podatak, "dd.MM.yyyy."), kriterijum);
            break;
        case 3:
            trazene = stablo->PretragaPoDatumuSmrti(QDate::fromString(podatak, "dd.MM.yyyy."), kriterijum);
            break;
        case 4:
            trazene = stablo->PretragaPoPolu(podatak.at(0), kriterijum);
            break;
        default:
            trazene = nullptr;
        }
        if (trazene == nullptr)
            ui->statusBar->showMessage(tr("Pretraga nije uradjena, pokusajte ponovo"));
        else
        {
            if(trazene->size() == 0)
                ui->zaInformacije->setText(tr("Nema osoba koje ispunjavaju uslove pretrage"));
            else
            {

                ui->zaInformacije->setText(tr("Ima ih"));//ovo zavrsiti, tj oznaciti te osobe itd
                //napravicu metod ispisi sve trazene, oznaci ih...
            }
            delete trazene;
        }
    }
    delete d;
}

QStringList GlavniProzor::skoroOtvarani;

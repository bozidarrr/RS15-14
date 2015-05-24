#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H
#include "GUI/stablo.h"
#include <QApplication>
#include <QMainWindow>
#include "engine/porodicnostablo.h"
#include <QButtonGroup>
#include <QToolBar>
#include <QLabel>
#include <QPushButton>
#include <QDockWidget>
#include "dijalogizmenaosobe.h"
#include "dialognovaosoba.h"
#include "dijalogrelacija.h"
#include <string>
#include "ui_glavniprozor.h"
#include <map>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QPoint>
#include <QPointF>
#include <QAction>
#include <QSettings>
#include <QTranslator>
#include <QTransform>
#include <QGraphicsScene>
#include <QTextBrowser>
#include "gosoba.h"
#include "grelacija.h"

class WidgetOsoba;
namespace Ui {
class GlavniProzor;
}

class GlavniProzor : public QMainWindow, private Ui::GlavniProzor
{
    Q_OBJECT

public:
    enum TipZaInfo {NISTA, INFO_OSOBA, INFO_BRAK, INFO_DETE};

    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();

    void popuniInformacije(short sifra, TipZaInfo tip);
    void retranslate();

private:
    Ui::GlavniProzor *ui;

    QButtonGroup *grpToolBar;
    QPushButton *tbOsoba, *tbMuzZena, *tbBratSestra, *tbRoditeljDete, *tbPomeranje, *tbDetalji, *tbBrisi, *tbMenjaj, *tbUredi;
    QToolBar *toolbar;
    QLabel *Labela;
    PorodicnoStablo *stablo;

    QDockWidget *alati, *info;

    enum {maxSkoroOtvaranih = 5};
    static QStringList skoroOtvarani;
    QAction *skoroOtvaraniAkcije[maxSkoroOtvaranih];
    QString otvoreniFajl;
    QTranslator *translator;

    //DODATI!!!
    std::map<short int, QPointF> _pozicijeOsoba;//<sifra_osobe, njena_pozicija>
    std::map<short int, QPointF> _pozicijeBrakova;//<sifra_braka, pozicija>

    QPushButton *kreirajJedanAlat(QPushButton *alat, const char *ime, const char *info);

    void kreirajOpcije();
    void kreirajToolbar();
    void kreirajMestoZaInfo();
    bool nastaviti();//provera da li je sve sacuvano pre izlaska i sl.
    bool snimiIzmene(const QString &imeFajla);//cuvamo u fajl
    void obnoviSkoroOtvarane();//recentFileList
    bool otvoriFajl(const QString &imeFajla);//otvaranje fajla
    void postaviTrenutniFajl(const QString &imeFajla);
    void writeSettings();//cuva pozicije widgeta, recent files, itd... Smisliti prevod imena :)
    void readSettings();//cita ovo gore pri konstrukciji

    /** menjanje stabla **/
    short izmeniOsobu(short sifra);
    GOsoba* dodajNovuOsobu(QPoint pozicija, bool krvniSrodnik);
    short ukloniOsobu(short sifra);
    short dodajNovoDete(GRelacija *brak, GOsoba *dete);
    short dodajNoviBrak(GOsoba *prva, GOsoba *druga);
    //GRelacija* dodajNovoDete(GRelacija *brak, GOsoba *dete);
    //GRelacija* dodajNoviBrak(GOsoba *prva, GOsoba *druga);

    Stablo *pogled;
    QGraphicsScene *scena;
    void kreirajPogledZaStablo();

    //void oznaciSlavljenike();

public Q_SLOTS:
    void prikaziToolbar();
    void novoStablo();//File|New
    void otvoriPostojeceStablo();//File|Open
    void closeEvent(QCloseEvent *event);//File|Exit
    bool sacuvaj();//File|Save
    bool sacuvajKao();//File|SaveAs
    void otvoriSkoroOtvaraniFajl();//File|RecentFiles...
    void promeniJezikE();//za Promenu jezika na engleski
    void promeniJezikN();//za promenu jezika na nemacki
    void promeniJezikS();//za promenu jezika na srpski
    void osveziPrikazAlata(bool Vidljivost);
    void osveziPrikazInformacija(bool Vidljivost);

    void kliknutoStablo(QPoint pozicija);
    void vucenoStablo(QPoint prva, QPoint druga);

    void urediStablo();
};

#endif // GLAVNIPROZOR_H

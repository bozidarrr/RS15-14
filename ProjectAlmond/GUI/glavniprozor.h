#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H
#include "GUI/stablo.h"

#include <QApplication>
#include <QMainWindow>
#include <engine/porodicnostablo.h>
#include <QButtonGroup>
#include <QToolBar>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPainter>
#include "GUI/widgetosoba.h"
#include "GUI/widgetrelacija.h"
#include "GUI/dialognovaosoba.h"
#include <string>
#include <iostream>
#include "ui_glavniprozor.h"
#include "okvirstabla.h"
#include <vector>
#include <map>
#include <QDebug>
#include "alati/filterobject.h"
#include <QMessageBox>
#include <QFileDialog>
#include <GUI/dijalogizmenaosobe.h>
#include <QPoint>
#include <QPointF>
#include <QAction>
#include <QSettings>
#include <QTranslator>

#include <QGraphicsScene>
#include <GUI/gosoba.h>

class WidgetOsoba;
namespace Ui {
class GlavniProzor;
}

class GlavniProzor : public QMainWindow, private Ui::GlavniProzor
{
    Q_OBJECT

public:
    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();

    void popuniInformacije(short sifra);

private:
    Ui::GlavniProzor *ui;

    QButtonGroup *grpToolBar;
    QPushButton *tbOsoba, *tbMuzZena, *tbBratSestra, *tbRoditeljDete, *tbPomeranje, *tbDetalji, *tbBrisi, *tbMenjaj, *tbUredi;
    QToolBar *toolbar;
    QLabel *Labela;
    PorodicnoStablo *stablo;
    //QPainter * cetka;

    QDockWidget *alati, *info;
    //okvirStabla *stabloOkvir;

    enum {maxSkoroOtvaranih = 5};
    static QStringList skoroOtvarani;
    QAction *skoroOtvaraniAkcije[maxSkoroOtvaranih];
    QString otvoreniFajl;
    QTranslator *translator;

    //DODATI!!!
    std::map<short int, QPointF> _pozicijeOsoba;//<sifra_osobe, njena_pozicija>

    QPushButton *kreirajJedanAlat(QPushButton *alat, const char *ime, const char *info);

    void kreirajOpcije();
    void kreirajToolbar();
    void kreirajMestoZaInfo();
    void kreirajStatusBar();
    bool nastaviti();//provera da li je sve sacuvano pre izlaska i sl.
    bool snimiIzmene(const QString &imeFajla);//cuvamo u fajl
    void obnoviSkoroOtvarane();//recentFileList
    bool otvoriFajl(const QString &imeFajla);//otvaranje fajla
    void postaviTrenutniFajl(const QString &imeFajla);
    void writeSettings();//cuva pozicije widgeta, recent files, itd... Smisliti prevod imena :)
    void readSettings();//cita ovo gore pri konstrukciji

    /*menjanje stabla*/
    short izmeniOsobu(short sifra);
    short dodajNovuOsobu(QPoint pozicija, bool krvniSrodnik);
    short ukloniOsobu(short sifra);

    Stablo *pogled;
    QGraphicsScene *scena;
    void kreirajPogledZaStablo();

public Q_SLOTS:
    void prikaziToolbar();
    void promeniKursor();//mozda...
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
};

#endif // GLAVNIPROZOR_H

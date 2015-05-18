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
#include <QAction>
#include <QSettings>
#include <QTranslator>

#include <QGraphicsScene>

class WidgetOsoba;
namespace Ui {
class GlavniProzor;
}

class GlavniProzor : public QMainWindow, private Ui::GlavniProzor
{
    Q_OBJECT

public:
    okvirStabla *stabloOkvir;//privremeno

    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();

    void promeniSelektovanu(short int novaSifra);

    void popuniInformacije(short sifra);

    void ispisiStatus(const QString &poruka);

private:
    Ui::GlavniProzor *ui;

    QButtonGroup *grpToolBar;
    QPushButton *tbOsoba, *tbMuzZena, *tbBratSestra, *tbRoditeljDete, *tbPomeranje, *tbDetalji, *tbBrisi, *tbMenjaj, *tbUredi;
    QToolBar *toolbar;
    QLabel *Labela, *labelaStatus;
    PorodicnoStablo *stablo;
    QPainter * cetka;

    QDockWidget *alati, *info;
    //okvirStabla *stabloOkvir;
    FilterObject *filter;

    static short int _selektovanaSifra;
    enum {maxSkoroOtvaranih = 5};
    static QStringList skoroOtvarani;
    QAction *skoroOtvaraniAkcije[maxSkoroOtvaranih];
    QString otvoreniFajl;
    QTranslator *translator;

    //DODATI!!!
    //vector<sifra_osobe, pozicija_osobe>
    std::map<short int, QPoint> _pozicijeOsoba;//<sifra_osobe, njena_pozicija>
    //std::vector< WidgetOsoba* > _osobe;//necemo cuvati ovako, ovo sluzi za test

    QPushButton *kreirajJedanAlat(QPushButton *alat, const char *ime, const char *info);

    void kreirajOpcije();
    void kreirajToolbar();
    void kreirajMestoZaInfo();
    void kreirajPlatnoZaCrtanje();
    void kreirajStatusBar();
    bool nastaviti();
    bool snimiIzmene(const QString &imeFajla);//cuvamo u fajl
    void obnoviSkoroOtvarane();//recentFileList
    bool otvoriFajl(const QString &imeFajla);//otvaranje fajla
    void postaviTrenutniFajl(const QString &imeFajla);
    void writeSettings();//cuva pozicije widgeta, recent files, itd... Smisliti prevod imena :)
    void readSettings();//cita ovo gore pri konstrukciji

    Stablo *pogled;
    QGraphicsScene *scena;
    void kreirajPogledZaStablo();

public Q_SLOTS:
    short dodajNovuOsobu(int x, int y, bool krvniSrodnik);
    void kliknutoPlatno();
    void prikaziToolbar();
    void kliknutaRelacija();
    void promeniKursor();//mozda...
    void novoStablo();//File|New
    void otvoriPostojeceStablo();//File|Open
    void closeEvent(QCloseEvent *event);//File|Exit
    bool sacuvaj();//File|Save
    bool sacuvajKao();//File|SaveAs
    void otvoriSkoroOtvaraniFajl();//File|RecentFiles...
    void promeniJezik();//za Promenu jezika kad se cekira drugi jezik
    void osveziPrikazAlata(bool Vidljivost);
    void osveziPrikazInformacija(bool Vidljivost);

    void kliknutoStablo(QPoint pozicija);
    void vucenoStablo(QPoint prva, QPoint druga);
};

#endif // GLAVNIPROZOR_H

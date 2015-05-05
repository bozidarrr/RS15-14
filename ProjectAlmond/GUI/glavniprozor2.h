#ifndef GLAVNIPROZOR2_H
#define GLAVNIPROZOR2_H

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
#include "ui_glavniprozor2.h"
#include "okvirstabla.h"
#include <vector>
#include <qdebug.h>
#include "alati/filterobject.h"
class WidgetOsoba;
namespace Ui {
class GlavniProzor2;
}

class GlavniProzor2 : public QMainWindow, private Ui::GlavniProzor2
{
    Q_OBJECT

public:
    okvirStabla *stabloOkvir;//privremeno

    explicit GlavniProzor2(QWidget *parent = 0);
    ~GlavniProzor2();

    void promeniSelektovanu(short int novaSifra);

    void popuniInformacije(short sifra);

    void poveziOsobe(short int sifra1, short int sifra2, Odnos odnos, int x1, int y1, int x2, int y2);
    /**
     * @brief kreirajOpcije
     * treba dodati sve opcije, tipa save, cancel, open, recently opened, bla bla
     * sto ce ici u meni
     * pocetak knjige :)
     */
    void kreirajOpcije();
    void kreirajToolbar();
    void krerajMestoZaInfo();
    void kreirajPlatnoZaCrtanje();
    void otpustenaOsoba();

    //void ukloniOsobu(WidgetOsoba* o);


private:
    Ui::GlavniProzor2 *ui;

    QButtonGroup *grpToolBar;
    QPushButton *tbOsoba;
    QPushButton *tbMuzZena, *tbBratSestra, *tbRoditeljDete;
    QPushButton *tbPomeranje, *tbDetalji;
    QPushButton *tbBrisi, *tbMenjaj;
    QPushButton *tbUredi;
    QToolBar *toolbar;
    QLabel *Labela;
    PorodicnoStablo *stablo;
    QPainter * cetka;

    //okvirStabla *stabloOkvir;

    static short int _selektovanaSifra;

    FilterObject *filter;

    //DODATI!!!
    //vector<sifra_osobe, pozicija_osobe>
    //vector<sifra_relacije, pozicija_relacije>
    std::vector< WidgetOsoba* > _osobe;//necemo cuvati ovako, ovo sluzi za test

    QPushButton *kreirajJedanAlat(QPushButton *alat, const char *ime, const char *info);



public Q_SLOTS:
    void dodajNovuOsobu(int x, int y);
    void kliknutoPlatno();

    void kliknutaRelacija();
};

#endif // GLAVNIPROZOR2_H

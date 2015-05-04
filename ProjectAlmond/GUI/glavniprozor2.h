#ifndef GLAVNIPROZOR2_H
#define GLAVNIPROZOR2_H

#include <QMainWindow>
#include <engine/porodicnostablo.h>
#include <QButtonGroup>
#include <QToolBar>
#include <QToolButton>
#include <QRadioButton>
#include <QDockWidget>
#include "GUI/widgetosoba.h"
#include "GUI/dialognovaosoba.h"
#include <string>
#include <iostream>
#include "ui_glavniprozor2.h"
#include "okvirstabla.h"
#include <vector>

#include "alati/filterobject.h"
class WidgetOsoba;
namespace Ui {
class GlavniProzor2;
}

class GlavniProzor2 : public QMainWindow, private Ui::GlavniProzor2
{
    Q_OBJECT

public:
    explicit GlavniProzor2(QWidget *parent = 0);
    ~GlavniProzor2();

    void promeniSelektovanu(short int novaSifra);

    void popuniInformacije();

    void postaviSifru1(short int nova);
    void postaviSifru2(short int nova);

    short Sifra1() const;
    short Sifra2() const;

    bool Povezivati() const;

    void poveziOsobe();
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
    QToolButton *tbOsoba;
    QToolButton *tbMuzZena, *tbBratSestra, *tbRoditeljDete;
    QToolButton *tbPomeranje, *tbDetalji;
    QToolButton *tbBrisi, *tbMenjaj;
    QToolButton *tbUredi;
    QToolBar *toolbar;

    PorodicnoStablo *stablo;

    okvirStabla *stabloOkvir;

    static short int _sifra1, _sifra2;
    static short int _selektovanaSifra;

    FilterObject *filter;

    //DODATI!!!
    //vector<sifra_osobe, pozicija_osobe>
    //vector<sifra_relacije, pozicija_relacije>
    std::vector< WidgetOsoba* > _osobe;//necemo cuvati ovako, ovo sluzi za test

    QToolButton *kreirajJedanAlat(QToolButton *alat, const char *ime, const char *info);

public Q_SLOTS:
    void dodajNovuOsobu(int x, int y);
    void kliknutoPlatno();
 //   void stisnutaOsoba(int sifra);

    void kliknutaRelacija();
};

#endif // GLAVNIPROZOR2_H

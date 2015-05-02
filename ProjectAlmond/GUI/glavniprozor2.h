#ifndef GLAVNIPROZOR2_H
#define GLAVNIPROZOR2_H

#include <QMainWindow>
#include <engine/porodicnostablo.h>
#include <QButtonGroup>
#include <QToolBar>
#include <QToolButton>
#include <QRadioButton>
#include <QDockWidget>
#include "widgetosoba.h"
#include "GUI/dialognovaosoba.h"
#include <string>
#include <iostream>
#include "ui_glavniprozor2.h"
#include "okvirstabla.h"
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


private:
    Ui::GlavniProzor2 *ui;

    QButtonGroup *grpToolBar;
    QToolButton *tbOsoba;
    QToolButton *tbMuzZena, *tbBratSestra, *tbRoditeljDete;
    QToolButton *tbPomeranje, *tbDetalji;
    QToolBar *toolbar;

    PorodicnoStablo *stablo;

    okvirStabla *stabloOkvir;

    short int _sifra1, _sifra2;
    static short int _selektovanaSifra;


    //DODATI!!!
    //vector<sifra_osobe, pozicija_osobe>
    //vector<sifra_relacije, pozicija_relacije>
public slots:
    void dodajNovuOsobu(int x, int y);
    void izvrsiAkciju();
};

#endif // GLAVNIPROZOR2_H

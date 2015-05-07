#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H

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
#include <qdebug.h>
#include "alati/filterobject.h"
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

    void otpustenaOsoba();

    void ukloniOsobu(WidgetOsoba* o);


private:
    Ui::GlavniProzor *ui;

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

    QLabel *labelaStatus;

    //DODATI!!!
    //vector<sifra_osobe, pozicija_osobe>
    //vector<sifra_relacije, pozicija_relacije>
    std::vector< WidgetOsoba* > _osobe;//necemo cuvati ovako, ovo sluzi za test

    QPushButton *kreirajJedanAlat(QPushButton *alat, const char *ime, const char *info);

    void kreirajOpcije();
    void kreirajToolbar();
    void kreirajMestoZaInfo();
    void kreirajPlatnoZaCrtanje();
    void kreirajStatusBar();



public Q_SLOTS:
    short dodajNovuOsobu(int x, int y);
    void kliknutoPlatno();

    void kliknutaRelacija();
};

#endif // GLAVNIPROZOR2_H

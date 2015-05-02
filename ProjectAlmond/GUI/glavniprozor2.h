#ifndef GLAVNIPROZOR2_H
#define GLAVNIPROZOR2_H

#include <QMainWindow>
#include <engine/porodicnostablo.h>
#include <QButtonGroup>
#include <QToolBar>
#include <QToolButton>
#include <QRadioButton>
#include <QDockWidget>

namespace Ui {
class GlavniProzor2;
}

class GlavniProzor2 : public QMainWindow
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

    void kreirajOpcije();
    void kreirajToolbar();
    void krerajMestoZaInfo();



private:
    Ui::GlavniProzor2 *ui;

    QToolButton *tbOsoba;
    QButtonGroup *grpRelacije;
    QRadioButton *rbMuzZena, *rbBratSestra, *rbRoditelj, *rbDete;
    QToolButton *tbPomeranje, *tbDetalji;
    QToolBar *toolbar;


    PorodicnoStablo *stablo;

    short int sifra1, sifra2;
    static short int selektovana_sifra;

    //DODATI!!!
    //vector<sifra_osobe, pozicija_osobe>
    //vector<sifra_relacije, pozicija_relacije>
};

#endif // GLAVNIPROZOR2_H

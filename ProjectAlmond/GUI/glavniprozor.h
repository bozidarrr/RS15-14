#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H 1

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QToolButton>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPixmap>
#include <QRadioButton>
#include <QButtonGroup>
#include "WidgetDrag.h"
#include <QTextBrowser>
#include "unetiosobu.h"
#include "widgetosoba.h"
#include <vector>
#include <iostream>


namespace Ui {
class GlavniProzor;
}

class GlavniProzor : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();

    void promeniSelektovanu(short int novaSifra);

    void popuniInformacije();

    void postaviSifru1(short int nova);
    void postaviSifru2(short int nova);
    void povezi();


private:
    QPoint m_ptDragPos;
    QPoint m_pomocna;

    Ui::GlavniProzor *ui;

    QToolButton * tbOsoba;
    QToolButton * tbBS;
    QToolButton * tbMZ;
    QToolButton * tbRD;

    QButtonGroup *grpRelacije;
    QRadioButton *rbMuzZena, *rbBratSestra, *rbRoditeljDete;

    QGraphicsScene* scena;
    QDrag *drag;
    int ind=-1;
    bool postavi=0;
    QPixmap osobapix;
    QPixmap mzpix;
    QPixmap bspix;
    QPixmap rdpix;

    Unetiosobu u;

    short int sifra1, sifra2;

    static short int selektovana_sifra;

    void startDrag();
    void napravi_Osobu();
    void poveziMZ();
    void poveziBS();
    void poveziRD();
           //vector <QPoint,QPushButton*> m_osobePoz;

private Q_SLOTS:
       void postavi_na_0(){ind=0;}
       void postavi_na_1(){ind=1;}
       void postavi_na_2(){ind=2;}
       void postavi_na_3(){ind=3;}

       void dodajNovuOsobu();

protected:
    virtual void mouseMoveEvent(QMouseEvent* pe);
    virtual void dragEnterEvent(QDragEnterEvent* pe);
    virtual void dropEvent(QDropEvent* pe);
    virtual void mousePressEvent(QMouseEvent *pe);
};

#endif // GLAVNIPROZOR_H

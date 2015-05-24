#ifndef DIJALOGIZMENAOSOBE_H
#define DIJALOGIZMENAOSOBE_H

#include <QDialog>
#include <QPushButton>
#include <engine/porodicnostablo.h>
#include <engine/osoba.h>
#include <iostream>

class Osoba;

namespace Ui {
class DijalogIzmenaOsobe;
}

class DijalogIzmenaOsobe : public QDialog
{
    Q_OBJECT

public:
    explicit DijalogIzmenaOsobe(Osoba *osoba, QWidget *parent = 0);
    ~DijalogIzmenaOsobe();
    void retranslate();

private:
    Ui::DijalogIzmenaOsobe *ui;
    QPushButton *ok, *cancel;

    Osoba *_osoba;

    void popuniDugmice();
    void popuniPolja();
    void postaviProvere();

public Q_SLOTS:
    void primeniIzmene();
private slots:
    void on_chkRodjenje_stateChanged(int arg1);
    void on_chkSmrt_stateChanged(int arg1);
};

#endif // DIJALOGIZMENAOSOBE_H

#ifndef DIJALOGIZMENAOSOBE_H
#define DIJALOGIZMENAOSOBE_H

#include <QDialog>
#include <QPushButton>
#include <engine/porodicnostablo.h>
#include <engine/osoba.h>
#include <iostream>

namespace Ui {
class DijalogIzmenaOsobe;
}

class DijalogIzmenaOsobe : public QDialog
{
    Q_OBJECT

public:
    explicit DijalogIzmenaOsobe(short int sifra, QWidget *parent = 0);
    ~DijalogIzmenaOsobe();

private:
    Ui::DijalogIzmenaOsobe *ui;
    QPushButton *ok, *cancel;

    short int _sifra;

    void popuniDugmice();
    void popuniPolja();

public Q_SLOTS:
    void primeniIzmene();
};

#endif // DIJALOGIZMENAOSOBE_H

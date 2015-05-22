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

public Q_SLOTS:
    void primeniIzmene();
};

#endif // DIJALOGIZMENAOSOBE_H

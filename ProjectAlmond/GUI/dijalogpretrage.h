#ifndef DIJALOGPRETRAGE_H
#define DIJALOGPRETRAGE_H

#include <QDialog>

namespace Ui {
class DijalogPretrage;
}

class DijalogPretrage : public QDialog
{
    Q_OBJECT

public:
    //0 ime, 1 prezime, 2 datum rodjenja, 3 datum smrti, 4 pol
    enum Opcija {IME, PREZIME, RODJENJE, SMRT, POL};

    explicit DijalogPretrage(QWidget *parent = 0);
    ~DijalogPretrage();
        void procitajPodatke(int &opcija, int &kriterijum, QString &podatak);

public Q_SLOTS:

    void tekstIliDatum();

private:
    Ui::DijalogPretrage *ui;

    QPushButton *ok, *cancel;

    void popuniDugmice();
};

#endif // DIJALOGPRETRAGE_H

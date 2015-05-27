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

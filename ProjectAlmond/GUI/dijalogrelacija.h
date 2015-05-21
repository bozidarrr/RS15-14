#ifndef DIJALOGRELACIJA_H
#define DIJALOGRELACIJA_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class DijalogRelacija;
}

class DijalogRelacija : public QDialog
{
    Q_OBJECT

public:
    explicit DijalogRelacija(QWidget *parent = 0);
    ~DijalogRelacija();

    void popuniPodatke(std::string &trivija);

private:
    Ui::DijalogRelacija *ui;

    QPushButton *ok, *cancel;

    void popuniDugmice();
    void postaviProvere();
};

#endif // DIJALOGRELACIJA_H

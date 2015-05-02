#ifndef DIALOGNOVAOSOBA_H
#define DIALOGNOVAOSOBA_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class DialogNovaOsoba;
}

class DialogNovaOsoba : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNovaOsoba(QWidget *parent = 0);
    ~DialogNovaOsoba();

private slots:
    void promenaUnosa();

    void on_chkSmrt_stateChanged(int arg1);

private:
    Ui::DialogNovaOsoba *ui;

    QPushButton *ok, *cancel;


    void popuniDugmice();
    void postaviProvere();
};

#endif // DIALOGNOVAOSOBA_H

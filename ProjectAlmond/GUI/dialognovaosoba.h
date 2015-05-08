#ifndef DIALOGNOVAOSOBA_H
#define DIALOGNOVAOSOBA_H

#include <QDialog>
#include <QPushButton>
#include <QDate>
#include <QString>
#include <QChar>
#include <string>
#include <QTextEdit>
#include <QLabel>
#include <QRegExp>
#include <QRegExpValidator>

namespace Ui {
class DialogNovaOsoba;
}

class DialogNovaOsoba : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNovaOsoba(bool saRelacijom = false, QWidget *parent = 0);
    ~DialogNovaOsoba();

    void popuniPodatke(QString &ime, QString &prezime, QString &pol, QDate &rodjenje, QDate &smrt, QString &trivija);

    void popuniPodatke(std::string &ime, std::string &prezime, char &pol, std::string &rodjenje, std::string &smrt);
private Q_SLOTS:
    void promenaUnosa();

    void on_chkSmrt_stateChanged(int arg1);
    void on_chkNepoznatDR_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::DialogNovaOsoba *ui;

    QPushButton *ok, *cancel;


    bool _saRelacijom;
    QLabel *labelaTrivija;
    QTextEdit *trivija;

    void popuniDugmice();
    void postaviProvere();
};

#endif // DIALOGNOVAOSOBA_H

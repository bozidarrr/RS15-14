#ifndef DIALOGPRETRAGE_H
#define DIALOGPRETRAGE_H

#include <QDialog>
#include <QString>
#include <QDate>
#include <QChar>
#include <QPushButton>

namespace Ui {
class DialogPretrage;
}

class DialogPretrage : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogPretrage(QWidget *parent = 0);
    ~DialogPretrage();
    QString _ime;
    QString _prezime;
    QDate _datumRodj;
    QDate _datumSmr;
    QChar _pol;
    int _kriterijum;

public Q_SLOTS:
    bool procitajPodatke();

    
private:
    Ui::DialogPretrage *ui;
    QPushButton *ok, *ponisti;
};

#endif // DIALOGPRETRAGE_H

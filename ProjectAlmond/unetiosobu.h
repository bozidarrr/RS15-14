#ifndef UNETIOSOBU_H
#define UNETIOSOBU_H

#include <QDialog>

namespace Ui {
class Unetiosobu;
}

class Unetiosobu : public QDialog
{
    Q_OBJECT
    
public:
    explicit Unetiosobu(QWidget *parent = 0);
   QString m_ime;
   QString m_prezime;
   QString m_datRdoj;
   QString m_datSmrti;
   void Ponisti();
   bool pol;
    ~Unetiosobu();
private Q_SLOTS:
  void Procitaj();
  void Odustani();
private:
    Ui::Unetiosobu *ui;
    //Osoba novaO;
};

#endif // UNETIOSOBU_H

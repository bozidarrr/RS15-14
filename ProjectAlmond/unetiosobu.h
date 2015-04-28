#ifndef UNETIOSOBU_H
#define UNETIOSOBU_H

#include <QDialog>
#include "osoba.h"

namespace Ui {
class Unetiosobu;
}

class Unetiosobu : public QDialog
{
    Q_OBJECT
    
public:
    explicit Unetiosobu(QWidget *parent = 0);
    ~Unetiosobu();
private Q_SLOTS:
  void NapraviOsobu();
  void Odustani();
private:
    Ui::Unetiosobu *ui;
    //Osoba novaO;
};

#endif // UNETIOSOBU_H

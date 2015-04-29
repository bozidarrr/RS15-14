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
    ~Unetiosobu();
  //  void NapraviOsobu(Osoba & novaO);
private:
    Ui::Unetiosobu *ui;
};

#endif // UNETIOSOBU_H

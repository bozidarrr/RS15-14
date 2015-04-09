#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QIcon>

namespace Ui {
class GlavniProzor;
}

class GlavniProzor : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();


private:
    Ui::GlavniProzor *ui;
};

#endif // GLAVNIPROZOR_H

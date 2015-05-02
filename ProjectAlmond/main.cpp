#include "GUI/glavniprozor.h"
#include "GUI/glavniprozor2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GlavniProzor w;
    GlavniProzor2 w;
    w.show();

    return a.exec();
}

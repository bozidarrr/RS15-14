#include "GUI/glavniprozor.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QSplashScreen *splash = new QSplashScreen;
//    splash->setPixmap(QPixmap(":/images/splash.png"));
//    splash->show();

    GlavniProzor *w = new GlavniProzor();
    w->show();



    return a.exec();
}

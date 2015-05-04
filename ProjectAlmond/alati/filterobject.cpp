#include "alati/filterobject.h"

FilterObject::FilterObject(okvirStabla *okvir, QObject *parent) : QObject(parent), _okvir(okvir)
{
    //_okvir = okvir;
}

FilterObject::~FilterObject()
{

}

bool FilterObject::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouse =(QMouseEvent*)e;
        if (mouse->button() == Qt::LeftButton)
        {
//            qDebug() << "pritisnuto levo dugme";
//            qDebug() <<mouse->pos().x();
//            qDebug() << mouse->pos().y();

            QWidget *w = dynamic_cast<QWidget*>(o);
            if (w == nullptr)
                return false;
            QPoint p = w->mapToParent(mouse->pos());

//            WidgetOsoba *osoba = dynamic_cast<WidgetOsoba*>(o);
//            if (osoba == nullptr)
//                qDebug() << "nije tipa widget osoba";
//            else
//                qDebug() << "uspeo cast";
//            qDebug() <<p.x();
//            qDebug() << p.y();
           // _okvir->X1(p.x());
           // _okvir->Y1(p.y());
        }
        //return true;

    }
    if (e->type() == QEvent::MouseButtonRelease)
    {

        QMouseEvent *mouse =(QMouseEvent*)e;
        if (mouse->button() == Qt::LeftButton)
        {
            qDebug() << "pusteno levo dugme";
           qDebug() <<mouse->pos().x();
            qDebug() << mouse->pos().y();

            QWidget *w = dynamic_cast<QWidget*>(o);
            if (w == nullptr)
                return false;
            QPoint p = w->mapToParent(mouse->pos());

            qDebug() << p.x();
            qDebug() << p.y();

            _okvir->X2(p.x());
            _okvir->Y2(p.y());
            //_okvir->kliknutIndirektno();
        }
        //return true;
    }

    return false;
}


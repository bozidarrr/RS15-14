#include "alati/filterobject.h"

FilterObject::FilterObject(okvirStabla *okvir, QObject *parent) : QObject(parent), _okvir(okvir)
{}

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
            qDebug() << "pritisnuto levo dugme";
//            qDebug() <<mouse->pos().x();
//            qDebug() << mouse->pos().y();

//            QWidget *w = dynamic_cast<QWidget*>(o);
            //QPoint p = w->mapToParent(mouse->pos());

//            qDebug() <<p.x();
//            qDebug() << p.y();
        }

    }
    if (e->type() == QEvent::MouseButtonRelease)
    {

        QMouseEvent *mouse =(QMouseEvent*)e;
        if (mouse->button() == Qt::LeftButton)
        {
            qDebug() << "pusteno levo dugme";
//            qDebug() <<mouse->pos().x();
//            qDebug() << mouse->pos().y();

//            QWidget *w = dynamic_cast<QWidget*>(o);
//            if (w == nullptr)
//                return false;
//            QPoint p = w->mapToParent(mouse->pos());

//            qDebug() << p.x();
//            qDebug() << p.y();
        }
    }

    return false;
}


#include "alati/filterobject.h"

FilterObject::FilterObject(okvirStabla *okvir, QObject *parent) : QObject(parent)
{
    _okvir = okvir;
}

FilterObject::~FilterObject()
{

}

bool FilterObject::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "pritisnuto";
        QMouseEvent *mouse =(QMouseEvent*)e;
        if (mouse->button() == Qt::LeftButton)
        {
            qDebug() << "levo dugme";
            qDebug() <<mouse->pos().x();
            qDebug() << mouse->pos().y();
            _okvir->X1(mouse->pos().x());
            _okvir->Y1(mouse->pos().y());
        }

    }
    if (e->type() == QEvent::MouseButtonRelease)
        //
    {
        qDebug() << "pusteno";
        QMouseEvent *mouse =(QMouseEvent*)e;
        if (mouse->button() == Qt::LeftButton)
        {
            qDebug() << "levo dugme";
            qDebug() <<mouse->pos().x();
            qDebug() << mouse->pos().y();
            _okvir->X2(mouse->pos().x());
            _okvir->Y2(mouse->pos().y());
            _okvir->kliknut();
        }
    }
}


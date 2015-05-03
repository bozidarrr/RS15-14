#include "alati/filterobject.h"

FilterObject::FilterObject(QObject *parent) : QObject(parent)
{

}

FilterObject::~FilterObject()
{

}

bool FilterObject::eventFilter(QObject *o, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress)
        qDebug() << "pritisnuto";
    if (e->type() == QEvent::MouseButtonRelease)
        qDebug() << "pusteno";
}


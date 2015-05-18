#include "GUI/stablo.h"

Stablo::Stablo()
{

}

Stablo::~Stablo()
{

}

void Stablo::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //qDebug() << "pressed";
        _prva = event->pos();
    }
}

void Stablo::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //qDebug() << "released";
        _druga = event->pos();
        if (_prva == _druga)
            emit kliknut(_prva);
        else
            emit vucen(_prva, _druga);
    }
}


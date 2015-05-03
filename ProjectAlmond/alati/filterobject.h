#ifndef FILTEROBJECT_H
#define FILTEROBJECT_H

#include <QObject>
#include <QEvent>
#include <QDebug>
/**
 * @brief The FilterObject class
 * Mozda bi ovo resilo problem kliktanja :)
 * implementiramo ovde sta se radi na koji event
 * instaliramo na koliko god widget-a da treba
 * Osoba, Relacija itd...
 * I ponasace se u stvari isto
 *
 *
 */
class FilterObject : public QObject
{
    Q_OBJECT
public:
    explicit FilterObject(QObject *parent = 0);
    ~FilterObject();

    bool eventFilter(QObject *o, QEvent *e);

signals:

public slots:
};

#endif // FILTEROBJECT_H

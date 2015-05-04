#ifndef FILTERZALABELU_H
#define FILTERZALABELU_H

#include <QObject>

class filterZaLabelu : public QObject
{
    Q_OBJECT
public:
    explicit filterZaLabelu(QObject *parent = 0);
    ~filterZaLabelu();
    bool eventFilter(QObject *o, QEvent *e);
signals:

public slots:
};

#endif // FILTERZALABELU_H

#include "alati/filterzalabelu.h"

filterZaLabelu::filterZaLabelu(QObject *parent) : QObject(parent)
{

}

filterZaLabelu::~filterZaLabelu()
{

}

bool filterZaLabelu::eventFilter(QObject *o, QEvent *e)
{
    return false;
}

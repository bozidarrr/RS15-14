#include "linija.h"

linija::linija(int x1, int y1, int x2, int y2)
    :_x1(x1),_y1(y1),_x2(x2),_y2(y2)
{
}

int linija::X1()
{
    return _x1;
}

int linija::Y1()
{
    return _y1;
}

int linija::X2()
{
    return _x2;
}

int linija::Y2()
{
    return _y2;
}

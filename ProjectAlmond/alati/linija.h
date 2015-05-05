#ifndef LINIJA_H
#define LINIJA_H

class linija
{
public:
    linija(int x1,int y1,int x2, int y2);

    int X1();
    int Y1();
    int X2();
    int Y2();

private:
    int _x1,_y1,_x2,_y2;
};

#endif // LINIJA_H

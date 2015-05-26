#ifndef TRAZENJEPUTA_H
#define TRAZENJEPUTA_H
#include <vector>
#include <map>
#include <QString>
#include "engine/porodicnostablo.h"
class TrazenjePuta
{
public:
    TrazenjePuta(PorodicnoStablo *stablo);

    ~TrazenjePuta();
    std::vector<short> operator()(short sifraPocetne,short sifraTrazene);

private:
    PorodicnoStablo *_stablo;
    short **_putevi;
    short **_duzine;
    short *_sifre;
    void InicijalizujMatricu(short **m,int n);
    int rBr(const short sifra)const;

};

#endif // TRAZENJEPUTA_H

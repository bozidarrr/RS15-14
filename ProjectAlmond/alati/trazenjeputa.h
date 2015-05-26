#ifndef TRAZENJEPUTA_H
#define TRAZENJEPUTA_H
#include <vector>
#include <map>
#include <QString>
#include "engine/porodicnostablo.h"
class TrazenjePuta
{
public:
    TrazenjePuta(PorodicnoStablo *stablo, int sifraKorena, int sifraTrazene);
    std::vector<int> operator()(void);

private:
    PorodicnoStablo *_stablo;
    int _sifraKorena;
    int _sifraTrazene;
    std::vector<int> _put;
    std::vector<Osoba*> _redCekanja;
    std::vector<int> _obradjeneSifre;


};

#endif // TRAZENJEPUTA_H

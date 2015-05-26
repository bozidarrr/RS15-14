#include "trazenjeputa.h"


TrazenjePuta::TrazenjePuta(PorodicnoStablo* stablo,int sifraKorena, int sifraTrazene)
    :_stablo(stablo),_sifraKorena(sifraKorena),_sifraTrazene(sifraTrazene)
{
}

std::vector<int> TrazenjePuta::operator()(void)
{
    _put.clear();
    if(_sifraKorena==_sifraTrazene)
    {
        _put.push_back(-1);
        return _put;
    }
    _redCekanja.clear();
    _obradjeneSifre.clear();
    _obradjeneSifre.push_back(_sifraKorena);
    _put.push_back(0);
    if(_stablo->osobaImaBrakove(_sifraKorena))
    {
      //  _redCekanja.push_back(_stablo->_indeksOsobaBrak[_sifraKorena]);
    }


    return _put;
}

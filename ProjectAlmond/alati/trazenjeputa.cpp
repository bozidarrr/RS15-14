#include "trazenjeputa.h"


TrazenjePuta::TrazenjePuta(PorodicnoStablo* stablo)
    :_stablo(stablo)
{
    int n=stablo->Osobe().size(),i,j;
    InicijalizujMatricu(_duzine,n);
    InicijalizujMatricu(_putevi,n);
    _sifre=new short[n];

    auto it=stablo->Osobe().cbegin();

    for(int i=0;i<n;i++,++it)
    {
        _sifre[i]=(*it).first;
    }


    for(i=0;i<n;i++){
        for(j=0;j<n;j++){

            _duzine[i][i]=0;
            _putevi[i][i]=_sifre[i];

        }
    }

    auto brak=stablo->Brakovi().cbegin();
    auto krajBraka=stablo->Brakovi().cend();
    //postavljanje direktnih veza
    for(;brak!=krajBraka;++brak){

        int rb1=rBr((*brak).second->SifraNase());
        int rb2=rBr((*brak).second->SifraTudje());
        int rbd=-1;
        _duzine[rb1][rb2]=1;
        _duzine[rb2][rb1]=1;
        _putevi[rb1][rb2]=rb1;
        _putevi[rb2][rb1]=rb2;

        auto decaBraka=stablo->BrakDeca().equal_range((*brak).first);
        std::multimap<short,short>::const_iterator i;
        for(i=decaBraka.first;i!=decaBraka.second;++i){
            rbd=rBr((stablo->NadjiDeteSifrom((*i).second))->SifraOsobe());
            _duzine[rb1][rbd]=1;
            _duzine[rb2][rbd]=1;
            _duzine[rbd][rb1]=1;
            _duzine[rbd][rb2]=1;
            _putevi[rb1][rbd]=rb1;
            _putevi[rb2][rbd]=rb2;
            _putevi[rbd][rb1]=rbd;
            _putevi[rbd][rb2]=rbd;
        }

    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(_duzine[i][k]!=-1 && _duzine[k][j]!=-1 &&(_duzine[i][j]==-1 || _duzine[i][j]>_duzine[i][k]+_duzine[k][j]))
                {
                    _duzine[i][j]=_duzine[i][k]+_duzine[k][j];
                    _putevi[i][j]=k;
                }
            }
        }
    }
    //ovime sam popunio matricu duzina i putanja, sada mogu da je koristim pozivima funkcija

    /*
    let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
    2 for each vertex v
    3    dist[v][v] ← 0
    4 for each edge (u,v)
    5    dist[u][v] ← w(u,v)  // the weight of the edge (u,v)
    6 for k from 1 to |V|
    7    for i from 1 to |V|
    8       for j from 1 to |V|
    9          if dist[i][j] > dist[i][k] + dist[k][j]
    10             dist[i][j] ← dist[i][k] + dist[k][j]
    11         end if

*/

}
TrazenjePuta::~TrazenjePuta()
{
    delete []_duzine;
    delete []_putevi;
    delete []_sifre;
}



std::vector<short> TrazenjePuta::operator()(short sifraPocetne,short sifraTrazene)
{

    std::vector<short> _put;
    int tren=rBr(sifraTrazene),kraj=rBr(sifraPocetne);
    while(tren!=kraj)
    {
        _put.push_back(_sifre[tren]);
        tren=_putevi[tren][kraj];
    }
    _put.push_back(_sifre[kraj]);


    return _put;
}

void TrazenjePuta::InicijalizujMatricu(short **m, int n)
{
    m=new short*[n];
    for(int i=0;i<n;++i)
    {
        m[i]=new short[n];
        for(int j=0;j<n;j++)
        {
            m[i][j]=-1;
        }
    }
}

int TrazenjePuta::rBr(const short sifra) const
{
    int n=_stablo->Osobe().size();
    for(int i=0;i<n;i++)
    {
        if(_sifre[i]==sifra)return i;

    }
    return -1;
}

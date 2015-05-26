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



std::vector<int> TrazenjePuta::operator()(short sifraPocetne,short sifraTrazene)
{

    std::vector<int> _put;

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

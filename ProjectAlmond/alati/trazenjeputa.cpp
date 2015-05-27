#include "trazenjeputa.h"

TrazenjePuta::TrazenjePuta(PorodicnoStablo* stablo)
    :_stablo(stablo),_putevi(nullptr),_duzine(nullptr),_sifre(nullptr)
{}
TrazenjePuta::~TrazenjePuta()
{
    if(_duzine!=nullptr)
        delete []_duzine;
    if(_putevi!=nullptr)
        delete []_putevi;
    if(_sifre!=nullptr)
        delete []_sifre;
}

std::vector<short> TrazenjePuta::operator()(short sifraPocetne,short sifraTrazene)const
{

    std::vector<short> _put;
    int tren=rBr(sifraTrazene),kraj=rBr(sifraPocetne);
    while(tren!=kraj)
    {
        _put.push_back(_sifre[tren]);
        tren=_putevi[kraj][tren];
    }
    _put.push_back(_sifre[kraj]);

    std::reverse(_put.begin(),_put.end());
    return _put;
}

QString TrazenjePuta::tipSrodstva(short sifraPocetne, short sifraTrazene) const
{
    std::vector<short> osobeIzmedju(operator()(sifraPocetne,sifraTrazene));
    int duzinaPuta=osobeIzmedju.size();
    if(duzinaPuta<2)return QString("greska");
    bool trazenaJeZensko=_stablo->NadjiOsobuSifrom(sifraTrazene)->Pol()=='Z';

    std::vector<short>::const_iterator prva=osobeIzmedju.cbegin();
    std::vector<short>::const_iterator druga=osobeIzmedju.cbegin();
    std::vector<short>::const_iterator kraj=osobeIzmedju.cend();
    druga++;
    int razlika=0;

    for(;druga!=kraj;++prva,++druga)
    {
        if(_stablo->jeDeteOd(*prva,*druga))razlika++;
        else if(_stablo->jeRoditeljOd(*prva,*druga))razlika--;
    }

    switch(duzinaPuta)
    {
    case 2:
        if(_stablo->jeDeteOd(sifraPocetne,sifraTrazene))
            if(trazenaJeZensko)
                return QString("cerka");
            else
                return QString("sin");
        else if(_stablo->jeRoditeljOd(sifraPocetne,sifraTrazene))
            if(trazenaJeZensko)
                return QString("majka");
            else
                return QString("otac");
        else
            if(trazenaJeZensko)
                return QString("zena");
            else
                return QString("muz");
        break;
    case 3:
        if(_stablo->jeBratSestraOd(sifraPocetne,sifraTrazene))
            if(trazenaJeZensko)
                return QString("sestra");
            else
                return QString("brat");
        else if(razlika<0)
        {
            if(trazenaJeZensko)
                return QString("baba");
            else
                return QString("deda");
        }
        else
        {
            if(trazenaJeZensko)
                return QString("unuka");
            else
                return QString("unuk");
        }
        break;
    case 4:
        if(razlika==3){
            if(trazenaJeZensko)
                return QString("prababa");
            else
                return QString("pradeda");
        }
        else if(razlika==-3){
            if(trazenaJeZensko)
                return QString("praunuka");
            else
                return QString("praunuk");
        }
        else if(razlika==1)
        {
            if(_stablo->NadjiOsobuSifrom(osobeIzmedju[1])->Pol()=='Z')
            {
                if(trazenaJeZensko)
                    return QString("tetka");
                else
                    return QString("ujak");
            }
            else
            {
                if(trazenaJeZensko)
                    return QString("tetka");
                else
                    return QString("stric");
            }

        }
        else if(razlika==-1)
        {
            if(_stablo->NadjiOsobuSifrom(osobeIzmedju[2])->Pol()=='Z')
            {
                if(trazenaJeZensko)
                    return QString("sestricina");
                else
                    return QString("sestric");
            }
            else
            {
                if(trazenaJeZensko)
                    return QString("bratanica");
                else
                    return QString("bratanac");
            }

        }


        break;
    default:
        if(trazenaJeZensko)
            return QString("daleka rodjaka");
        else
            return QString("daleki rodjak");
        break;

    }



    return QString("daleki rodjak");
}

void TrazenjePuta::OsveziMatricuPuteva()
{
    int n=_stablo->Osobe().size(),i,j;

    InicijalizujMatricu(&_duzine,n);
    InicijalizujMatricu(&_putevi,n);
    _sifre=new short[n];

    auto it=_stablo->Osobe().cbegin();

    for(i=0;i<n;++i,++it)
    {
        _sifre[i]=(*it).first;

    }


    for( i=0;i<n;i++){
        for( j=0;j<n;j++){

            _duzine[i][i]=0;
            _putevi[i][i]=_sifre[i];

        }
    }
    std::cout<<_stablo->Brakovi().size()<<std::endl;
    std::map<short, Brak*>::iterator brak=_stablo->Brakovi().begin();
    std::map<short, Brak*>::iterator krajBraka=_stablo->Brakovi().end();
    //postavljanje direktnih veza
    for(;brak!=krajBraka;++brak){
        short sNase=(*brak).second->SifraNase();
        short sTudje=(*brak).second->SifraTudje();


        int rb1=rBr(sNase);
        int rb2=rBr(sTudje);

        int rbd=-1;
        _duzine[rb1][rb2]=1;
        _duzine[rb2][rb1]=1;
        _putevi[rb1][rb2]=rb1;
        _putevi[rb2][rb1]=rb2;

        auto decaBraka=_stablo->BrakDeca().equal_range((*brak).first);
        std::multimap<short,short>::const_iterator i;
        for(i=decaBraka.first;i!=decaBraka.second;++i){
            rbd=rBr((_stablo->NadjiDeteSifrom((*i).second))->SifraOsobe());
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


    for(int i=0;i<n;i++){

        for(int j=0;j<n;j++)
        {
            std::cout<<_putevi[i][j]<<",";
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
    std::cout<<std::endl;
    for(int i=0;i<n;i++){

        for(int j=0;j<n;j++)
        {
            std::cout<<_duzine[i][j]<<",";
        }
        std::cout<<std::endl;
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

void TrazenjePuta::InicijalizujMatricu(short ***m, int n)
{
    if(*m!=nullptr){
        delete[] *m;
    }
    *m=new short*[n];
    for(int i=0;i<n;++i)
    {
        (*m)[i]=new short[n];
        for(int j=0;j<n;j++)
        {
            (*m)[i][j]=-1;
        }
    }
}

int TrazenjePuta::rBr( short sifra) const
{
    int n=_stablo->Osobe().size();
    for(int i=0;i<n;i++)
    {
        if(_sifre[i]==sifra)return i;

    }
    return -1;
}

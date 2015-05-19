#include "brak.h"

short int Brak::_sledecaSifra=0;

Brak::Brak()
{}

Brak::Brak(Osoba *nasa, Osoba *tudja, std::string &trivija)
    :_sifra(++_sledecaSifra),_nasaOsoba(nasa),_tudjaOsoba(tudja),_spisakDece(2),_trivija(trivija)
{
}

Brak::Brak(const Brak &drugi)
    :_sifra(drugi._sifra),_nasaOsoba(nullptr),_tudjaOsoba(nullptr),_spisakDece(drugi._spisakDece.size()),_trivija(drugi._trivija)
{
}

Brak::~Brak()
{
    _vecSeBrisem=true;
    if(!_preskociRazvezivanje){
        _tudjaOsoba->Raskini(this);//molim osobu koja nije u rodbinskoj liniji da ukloni brak, ne bih li mogao da je obrisem bez beskonacne rekurzije
        if(!_tudjaOsoba->VecSeBrisem())delete _tudjaOsoba;

        _nasaOsoba->Raskini(this);//molim osobu koja jeste u rodbinskoj linija da ukloni brak, ali nju ne brisem, ona ostaje

        std::vector<Dete*>::iterator b=_spisakDece.begin();
        std::vector<Dete*>::iterator e=_spisakDece.end();
        for(;b!=e;b++)//brisem svako dete-relaciju iz spiska, koje dalje pokrece brisanje svih osoba potomaka
        {
            if(!(*b)->VecSeBrisem())
            delete *b;
        }
    }
}

short int Brak::Sifra()
{
    return _sifra;
}
Osoba* Brak::NasaOsoba()
{
    return _nasaOsoba;
}
Osoba* Brak::TudjaOsoba()
{
    return _tudjaOsoba;
}
std::vector<Dete*>& Brak::SpisakDece()
{
    return _spisakDece;
}
std::string& Brak::Trivija()
{
    return _trivija;
}

void Brak::PostaviNasuOsobu(Osoba *nasa)
{
    _nasaOsoba=nasa;
}

void Brak::PostaviTudjuOsobu(Osoba* tudja)
{
    _tudjaOsoba=tudja;
}

/*
QDate& Brak::DatumUpoznavanja()
{
    return _datumUpoznavanja;
}
QDate& Brak::DatumVeze()
{
    return _datumVeze;
}
QDate& Brak::DatumVeridbe()
{
    return _datumVeridbe;
}
QDate& Brak::DatumVencanja()
{
    return _datumVencanja;
}
QDate& Brak::DatumRaskida()
{
    return _datumRaskida;
}
*/

void Brak::postaviSledecuSifru(int sifra)
{
    _sledecaSifra=sifra;
}

void Brak::DodajDete(Dete* beba)
{
    _spisakDece.push_back(beba);

}

bool Brak::UVezi()
{
    return false;
}
bool Brak::Vereni()
{
    return false;
}
bool Brak::Vencani()
{
    return false;
}
bool Brak::Rastavljeni()
{
    return false;
}

bool Brak::DeteSeUklanja(Dete *obrisiMe)
{
    _spisakDece.erase(std::remove(_spisakDece.begin(), _spisakDece.end(), obrisiMe), _spisakDece.end());
    return true;
}

bool Brak::RaskiniSupruznike(Osoba* inicijator)
{
    if(_nasaOsoba==inicijator)
        _tudjaOsoba->Raskini(this);
    else
        _nasaOsoba->Raskini(this);

    return true;
}

bool Brak::RaskiniSveVeze()
{
    _tudjaOsoba=nullptr;
    _nasaOsoba=nullptr;
    _spisakDece.clear();
    return true;

}

bool Brak::VecSeBrisem()
{
    return _vecSeBrisem;
}

void Brak::PreskociRazvezivanje()
{
    _preskociRazvezivanje=true;
}

QDataStream& operator<<(QDataStream &out,Brak& brak)
{
    out << qint32(brak._sifra);
    out << qint32(brak._spisakDece.size());
    out << QString::fromStdString(brak._trivija);

    return out;
}


QDataStream& operator>>(QDataStream &in,Brak& brak)
{

    in >> brak._sifra;
    int broj;
    in >> broj;
    brak._spisakDece.resize(broj);
    QString tren;
    in >> tren;
    brak._trivija=tren.toStdString();

    return in;
}





#include "brak.h"

short int Brak::_sledecaSifra=0;

Brak::Brak(Osoba *nasa, Osoba *tudja, std::string &trivija, QDate &datumUpoznavanja, QDate &datumVeze, QDate &datumRaskida, QDate &datumVeridbe, QDate &datumVencanja)
    :_sifra(++_sledecaSifra),_nasaOsoba(nasa),_tudjaOsoba(tudja),_spisakDece(2),_trivija(trivija),_datumUpoznavanja(datumUpoznavanja),_datumVeze(datumVeze),_datumVeridbe(datumVeridbe),_datumVencanja(datumVencanja),_datumRaskida(datumRaskida)
{
}

Brak::~Brak()
{
    _tudjaOsoba->Raskini(this);//molim osobu koja nije u rodbinskoj liniji da ukloni brak, ne bih li mogao da je obrisem bez beskonacne rekurzije
    delete _tudjaOsoba;

    _nasaOsoba->Raskini(this);//molim osobu koja jeste u rodbinskoj linija da ukloni brak, ali nju ne brisem, ona ostaje

    std::vector<Dete*>::iterator b=_spisakDece.begin();
    std::vector<Dete*>::iterator e=_spisakDece.end();
    for(;b!=e;b++)//brisem svako dete-relaciju iz spiska, koje dalje pokrece brisanje svih osoba potomaka
    {
        delete *b;
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

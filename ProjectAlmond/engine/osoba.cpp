#include"engine/osoba.h"
#include<algorithm>
short int Osoba::_MinSifra=0;

Osoba::Osoba(const std::string ime, const std::string prezime, const char pol,
             const std::string datum_rodjenja, const std::string datum_smrti)
    : _ime(ime), _prezime(prezime),_pol(pol),
      _datum_rodjenja(datum_rodjenja),
      _datum_smrti(datum_smrti),
      _supruznici(2)

{
    _sifra=_MinSifra++;
}

//kada osobu uklanjamo iz stabla, sve njene veze moraju biti pobrisane, ali moraju obavestiti i objekte sa kojima su vezane da vise ne postoje
Osoba::~Osoba()
{
    //Obavestavamo:
    //muzeve i zene
    std::vector<Supruznik*>::iterator sp=_supruznici.begin();
    std::vector<Supruznik*>::iterator sk=_supruznici.end();
    for(;sp!=sk;sp++){
        (*sp)->UkloniSe(this);
        delete *sp;
    }

    //decu

    //bracu i sestre

    //roditelje

}

//konstruktori kopije i dodele kreiraju osobu sa istim karakteristikama, ali nepovezanu!!! Veze se ne kopiraju!!!
Osoba::Osoba(const Osoba& nova):
    _ime(nova.Ime()),
    _prezime(nova.Prezime()),_pol(nova.Pol()),
    _datum_rodjenja(nova.DatumRodjenja()),
    _datum_smrti(nova.DatumSmrti()),

    _supruznici(2)
{_sifra=_MinSifra++;
}


Osoba& Osoba::operator=(Osoba& nova){
    if(&nova!=this){
        Osoba tmp(nova);
        std::swap(this->_ime,nova._ime);
        std::swap(this->_prezime,nova._prezime);
        std::swap(this->_datum_rodjenja,nova._datum_rodjenja);
        std::swap(this->_datum_smrti,nova._datum_smrti);
        std::swap(this->_pol,nova._pol);
    }
    return *this;
}

/* provera ispravnosti podataka? reg.exp? */

short int Osoba::Sifra()const
{
    return _sifra;
}

const std::string& Osoba::Ime() const
{
    return _ime;
}

const std::string& Osoba::Prezime() const
{
    return _prezime;
}

const Datum& Osoba::DatumRodjenja() const
{
    return _datum_rodjenja;
}

const Datum& Osoba::DatumSmrti() const
{
    return _datum_smrti;
}

char Osoba::Pol() const
{
    return _pol;
}

bool Osoba::ProveriPodatke()const
{
    //todo
    return true;
}

std::vector<Supruznik*>& Osoba::Supruznici()
{
    return _supruznici;
}


//ovde koristim neko zlo, takozvani erase-remove idiom: procitajte na netu
void Osoba::UkloniSupruznika(Supruznik* inicijator){    
    _supruznici.erase(std::remove(_supruznici.begin(), _supruznici.end(), inicijator), _supruznici.end());
}



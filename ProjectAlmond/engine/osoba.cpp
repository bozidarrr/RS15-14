#include"engine/osoba.h"

short int Osoba::_MinSifra=0;

Osoba::Osoba(std::string ime, std::string prezime,
             std::string datum_rodjenja, std::string datum_smrti)
    : _ime(ime), _prezime(prezime),
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
/*
Osoba::Osoba(const Osoba& nova){

//todo
}


Osoba& Osoba::operator=(const Osoba& nova){

}*/

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


//ovde koristim neko zlo, takozvani erase-remove idiom: procitajte na netu
void Osoba::UkloniSupruznika(Supruznik* inicijator){    
    _supruznici.erase(std::remove(_supruznici.begin(), _supruznici.end(), inicijator), _supruznici.end());
}



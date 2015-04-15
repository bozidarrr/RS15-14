#include "osoba.h"

Osoba::Osoba(std::string ime, std::string prezime,
        std::string datum_rodjenja, std::string datum_smrti)
    : _ime(ime), _prezime(prezime),
    _datum_rodjenja(datum_rodjenja), _datum_smrti(datum_smrti)
    {
        /* inicijalizacija listi veza */
    }


/* provera ispravnosti podataka? reg.exp? */

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

/*
string& Osoba::PronadjiVezu(const Osoba & o)
{


}
*/



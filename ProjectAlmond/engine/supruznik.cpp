#include "engine/supruznik.h"

Supruznik::Supruznik(const std::string& datumVencanja, const std::string& datumUpoznavanja, const std::string& datumRazvoda, const std::string &trivija)
    :Relacija(trivija),_datumVencanja(datumVencanja),_datumUpoznavanja(datumUpoznavanja),_datumRazvoda(datumRazvoda)
{
}

Supruznik::~Supruznik()
{
    Zena().UkloniSupruznika(this);
    Muz().UkloniSupruznika(this);
}

Datum Supruznik::DatumVencanja() const
{
    return _datumVencanja;
}

Datum Supruznik::DatumUpoznavanja() const
{
    return _datumUpoznavanja;
}

Datum Supruznik::DatumRazvoda() const
{
    return _datumRazvoda;
}

bool Supruznik::UVezi() const
{
    return DatumRazvoda().NepoznatDatum();
}

bool Supruznik::UBraku() const
{
    return !(DatumVencanja().NepoznatDatum()) && DatumRazvoda().NepoznatDatum();
}

bool Supruznik::Rastavljeni() const
{
    return !DatumRazvoda().NepoznatDatum();
}

//dva metoda koja samo sluze da bih lakse nazivao specificne operacije
Osoba& Supruznik::Muz() const
{
    return  (Osoba&)(*_prva);
}

Osoba& Supruznik::Zena() const
{
    return  (Osoba&)(*_druga);
}



//jer ako je muz inicijator, onda zena treba da ga obrise i obratno
void Supruznik::UkloniSe(const Osoba *inicijator=nullptr)
{
    (inicijator==&Muz())?Zena().UkloniSupruznika(this):Muz().UkloniSupruznika(this);//todo
}

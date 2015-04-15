#include "supruznik.h"

Supruznik::Supruznik(const std::string& datumVencanja, const std::string& datumUpoznavanja, const std::string& datumRazvoda, const std::string &trivija)
    :Relacija(trivija),_datumVencanja(datumVencanja),_datumUpoznavanja(datumUpoznavanja),_datumRazvoda(datumRazvoda)
{
}

Supruznik::~Supruznik()
{
    _zena->UkloniSupruznika(this);
    _muz->UkloniSupruznika(this);
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
//proveriti da li ovo ima smisla uopste u sledeca dva, nisam siguran da li se dobija ono sto hocu
const Osoba& Supruznik::Muz() const
{
    return  (Osoba&)(*_muz);
}

const Osoba& Supruznik::Zena() const
{
    return  (Osoba&)(*_zena);
}





std::string Supruznik::UpisiUString()const
{
    return "";
}

void Supruznik::UcitajIzStringa(const std::string& unos)
{
    std::cout<<std::endl<<unos<<std::endl;
    return;
}
//jer ako je muz inicijator, onda zena treba da ga obrise i obratno
void Supruznik::UkloniSe(const Osoba *inicijator=nullptr)
{
    inicijator==_muz?_zena->UkloniSupruznika(this):_muz->UkloniSupruznika(this);//todo
}

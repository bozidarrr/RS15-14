#include "brak.h"
#include <iostream>
#include <QDataStream>

short int Brak::_sledecaSifra=0;

Brak::Brak()
{}

Brak::Brak(const short sifraNase, const short sifraTudje, const QString &trivija)
    : _sifra(++_sledecaSifra), _sifraNase(sifraNase), _sifraTudje(sifraTudje), _trivija(trivija)
{}

Brak::Brak(const Brak &drugi)
    :_sifra(drugi._sifra),_sifraNase(),_sifraTudje(),_trivija(drugi._trivija)
{
}

Brak::~Brak()
{
    //std::cout << "brise se brak " << Sifra() << std::endl;
    _vecSeBrisem=true;
}

short int Brak::Sifra()
{
    return _sifra;
}

short Brak::SifraNase()
{
    return _sifraNase;
}
short Brak::SifraTudje()
{
    return _sifraTudje;
}

const QString &Brak::Trivija() const
{
    return _trivija;
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
    out << qint32(brak.SifraNase());
    out << qint32(brak.SifraTudje());
    out << brak._trivija;
    return out;
}


QDataStream& operator>>(QDataStream &in,Brak& brak)
{
    qint32 broj;
    in >> broj;
    brak._sifra=(short)broj;
    in >> broj;
    brak._sifraNase=(short)broj;
    in >> broj;
    brak._sifraTudje=(short)broj;
    in >> brak._trivija;
    return in;
}


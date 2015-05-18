#include "dete.h"

short int Dete::_sledecaSifra=0;

Dete::Dete()
{}

Dete::Dete(Osoba* osoba, Brak* roditeljskaVeza, std::string trivija)
    :_sifra(++_sledecaSifra),_osoba(osoba),_roditeljskiOdnos(roditeljskaVeza),_trivija(trivija)
{}

Dete::Dete(const Dete &drugo)
    :_sifra(drugo._sifra),_osoba(nullptr),_roditeljskiOdnos(nullptr),_trivija(drugo._trivija)
{}

Dete::~Dete()
{
    if(_roditeljskiOdnos!=nullptr)
        _roditeljskiOdnos->DeteSeUklanja(this);//u roditeljskom odnosu brisem podatke o tom detetu
    if(_osoba!=nullptr){
        _osoba->ObrisiPoreklo();//osobi brisem poreklo, da ne bi doslo do beskonacne rekurzije
        delete _osoba;//brisem osobu, sto dalje pokrece rekurzivno brisanje ostalih podataka
    }
}

short int Dete::Sifra()
{
    return _sifra;
}
Osoba* Dete::Potomak()
{
    return _osoba;
}
Brak* Dete::RoditeljskiOdnos()
{
    return _roditeljskiOdnos;
}
std::string& Dete::Trivija()
{
    return _trivija;
}/*
QDate& Dete::DatumUsvajanja()
{
    return _datumUsvajanja;
}
*/
bool Dete::BrisanjeOdOsobe()
{
    _roditeljskiOdnos->DeteSeUklanja(this);
    return true;
}

bool Dete::RaskiniSveVeze()
{
    _roditeljskiOdnos=nullptr;
    _osoba=nullptr;
    return true;
}
QDataStream& operator<<(QDataStream &out,Dete& dete)
{
    out << qint32(dete._sifra);
    out << QString::fromStdString(dete._trivija);
    return out;
}


QDataStream& operator>>(QDataStream &in,Dete& dete)
{

    in >> dete._sifra;
    QString tren;
    in >> tren;
    dete._trivija=tren.toStdString();
    return in;
}


#include "brak.h"
#include <iostream>
#include <QDataStream>

short int Brak::_sledecaSifra=0;

Brak::Brak()
{}

//Brak::Brak(Osoba *nasa, Osoba *tudja, std::string &trivija)
//    :_sifra(++_sledecaSifra),_nasaOsoba(nasa),_tudjaOsoba(tudja),_spisakDece(),_trivija(trivija)
//{
//    //std::cout << "kreira se brak " << _sifra << std::endl;
//}

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
//    if(!_preskociRazvezivanje){
//        //std::cout << "i razvezuje" << Sifra() << std::endl;
//        _tudjaOsoba->Raskini(this);//molim osobu koja nije u rodbinskoj liniji da ukloni brak, ne bih li mogao da je obrisem bez beskonacne rekurzije
//        if(!_tudjaOsoba->VecSeBrisem())delete _tudjaOsoba;

//        _nasaOsoba->Raskini(this);//molim osobu koja jeste u rodbinskoj linija da ukloni brak, ali nju ne brisem, ona ostaje

//        std::vector<Dete*>::iterator b=_spisakDece.begin();
//        std::vector<Dete*>::iterator e=_spisakDece.end();
//        for(;b!=e;b++)//brisem svako dete-relaciju iz spiska, koje dalje pokrece brisanje svih osoba potomaka
//        {
//            std::cout << "brise se dete iz braka " << Sifra() << std::endl;
//            if(!(*b)->VecSeBrisem())
//            delete *b;
//        }
//    }
}

short int Brak::Sifra()
{
    return _sifra;
}
//Osoba* Brak::NasaOsoba()
//{
//    return _nasaOsoba;
//}
//Osoba* Brak::TudjaOsoba()
//{
//    return _tudjaOsoba;
//}
short Brak::SifraNase()
{
    return _sifraNase;
}
short Brak::SifraTudje()
{
    return _sifraTudje;
}
//std::vector<Dete*>& Brak::SpisakDece()
//{
//    return _spisakDece;
//}
const QString &Brak::Trivija() const
{
    return _trivija;
}

//void Brak::PostaviNasuOsobu(Osoba *nasa)
//{
//    _nasaOsoba=nasa;
//}

//void Brak::PostaviTudjuOsobu(Osoba* tudja)
//{
//    _tudjaOsoba=tudja;
//}

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

//void Brak::DodajDete(Dete* beba)
//{
//    _spisakDece.push_back(beba);

//}

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

//bool Brak::DeteSeUklanja(Dete *obrisiMe)
//{
//    _spisakDece.erase(std::remove(_spisakDece.begin(), _spisakDece.end(), obrisiMe), _spisakDece.end());
//    return true;
//}

//bool Brak::RaskiniSupruznike(Osoba* inicijator)
//{
////    if(_nasaOsoba==inicijator)
////        _tudjaOsoba->Raskini(this);
////    else
////        _nasaOsoba->Raskini(this);

//    return true;
//}

//bool Brak::RaskiniSveVeze()
//{
//    //_tudjaOsoba=nullptr;
//    //_nasaOsoba=nullptr;
//    //_spisakDece.clear();
//    return true;

//}

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
    //out << qint32(brak._spisakDece.size());
    out << qint32(brak.SifraNase());
    out << qint32(brak.SifraTudje());
    out << brak._trivija;

    return out;
}


QDataStream& operator>>(QDataStream &in,Brak& brak)
{

    in >> brak._sifra;
    int broj;
    in >> broj;
    //brak._spisakDece.resize(broj);
    QString tren;
    in >> tren;
    //brak._trivija=tren.toStdString();

    return in;
}





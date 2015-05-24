#include"engine/osoba.h"
#include <vector>
#include <string>
#include <QDate>
#include<QDataStream>
#include <QString>
#include <iostream>
short int Osoba::_sledecaSifra=0;


Osoba::Osoba(bool krvniSrodnik)
    :_sifra(_sledecaSifra++),_nepoznata(true),_ime("N."),_prezime("N."),
      _pol('?'),_datumRodjenja(),_datumSmrti(),_krvniSrodnik(krvniSrodnik)
{}

Osoba::Osoba(const QString &ime, const QString &prezime, const QChar &pol, const QDate &rodjenje, const QDate &smrt, bool krvniSrodnik)
    :_sifra(_sledecaSifra++),_nepoznata(false),_ime(ime),_prezime(prezime),
      _pol(pol), _datumRodjenja(), _datumSmrti(), _krvniSrodnik(krvniSrodnik)
{
    if (rodjenje.isValid())
        _datumRodjenja.setDate(rodjenje.year(), rodjenje.month(), rodjenje.day());
    if (smrt.isValid())
        _datumSmrti.setDate(smrt.year(), smrt.month(), smrt.day());
}

Osoba::Osoba(const Osoba& druga)
    :_sifra(druga._sifra),_nepoznata(druga._nepoznata),_ime(druga._ime),_prezime(druga._prezime),
      _pol(druga._pol),_krvniSrodnik(druga._krvniSrodnik)
{}

Osoba::~Osoba()
{
    //std::cout << "brise se osoba " << _ime << std::endl;
    _vecSeBrisem=true;
//        if(!_preskociRazvezivanje){
//        //std::cout << "osoba razvezuje " << Sifra() << std::endl;
//            //brisem podatke o sebi kao detetu
//            if(_deteOd!=nullptr)
//            {
//                //std::cout << "osoba se brise kao dete " << Sifra() << std::endl;
//                _deteOd->BrisanjeOdOsobe();
//                if (!_deteOd->VecSeBrisem())
//                delete _deteOd;
//            }

//            //za svaku vezu iz spiska
//            if(!_spisakVeza.empty()){
//                std::vector<Brak*>::iterator b=_spisakVeza.begin();
//                std::vector<Brak*>::iterator e=_spisakVeza.end();

//                if(!_krvniSrodnik){
//                    for(;b!=e;b++)
//                    {
//                        //std::cout << "osoba nije k.s. i raskida brakove " << Sifra() << std::endl;
//                        (*b)->RaskiniSupruznike(this);//necu brisati i supruznika iz spiska, nego ga treba zamoliti da ukloni brak jer ostaje u porodici tj. ne brise se
//                        if (!(*b)->VecSeBrisem())
//                        delete *b;//brisanje braka ce automatski obrisati svu decu i sve njihove potomke
//                    }
//                }
//                else//ako jeste krvni srodnik, onda treba pokrenuti samo brisanje druge osobe, koja ce zatim pokrenuti i ostatak brisanja kao u prethodnom
//                {
//                    for(;b!=e;b++)
//                    {
//                        //std::cout << "osoba jeste k.s. i brise supruznike " << Sifra() << std::endl;
//                        if(!(*b)->VecSeBrisem())
//                            delete ((*b)->TudjaOsoba());
//                    }
//                }
//            }
//        }
}


short int Osoba::Sifra()const
{
    return _sifra;
}

const QString& Osoba::Ime() const
{
    return _ime;
}

const QString &Osoba::Prezime() const
{
    return _prezime;
}

const QString *Osoba::ImePrezime() const
{
    QString* novi = new QString(_ime);
    novi->append(" ");
    novi->append(_prezime);
    return novi;
}

const QChar& Osoba::Pol() const
{
    return _pol;
}

const QDate& Osoba::DatumRodjenja() const
{
    return _datumRodjenja;
}

const QDate& Osoba::DatumSmrti() const
{
    return _datumSmrti;
}

bool Osoba::JeKrvniSrodnik() const
{
    return _krvniSrodnik;
}

void Osoba::PromeniIme(const QString &ime)
{
    _ime = ime;
}

void Osoba::PromeniPrezime(const QString &prezime)
{
    _prezime = prezime;
}
void Osoba::PromeniPol(const QChar &pol)
{
    _pol = pol;
}

void Osoba::PromeniDatumRodjenja(const QDate &datum)
{
    if (datum.isValid())
        _datumRodjenja.setDate(datum.year(), datum.month(), datum.day());
}

void Osoba::PromeniDatumSmrti(const QDate &datum)
{
    if (datum.isValid())
        _datumSmrti.setDate(datum.year(), datum.month(), datum.day());
}

void Osoba::postaviSledecuSifru(int sifra)
{
    _sledecaSifra=sifra;
}

//void Osoba::DodajVezu(Brak* veza)
//{
//    _spisakVeza.push_back(veza);
//}


//std::vector<Brak*>& Osoba::SpisakVeza()
//{
//    return _spisakVeza;
//}

void Osoba::PretvoriUNepoznatu()
{
    _ime="N.";
    _prezime="N.";
    _pol='?';
    _nepoznata=true;
}

//bool Osoba::Raskini(Brak* razvod)
//{
//    _spisakVeza.erase(std::remove(_spisakVeza.begin(), _spisakVeza.end(), razvod), _spisakVeza.end());
//    return true;
//}

//bool Osoba::ObrisiPoreklo()
//{
//    _deteOd=nullptr;
//    return true;
//}

//bool Osoba::RaskiniSveVeze()
//{
//    //_deteOd=nullptr;
//   // _spisakVeza.clear();
//    return true;
//}

bool Osoba::VecSeBrisem()
{
    return _vecSeBrisem;
}
//void Osoba::PreskociRazvezivanje()
//{
//    _preskociRazvezivanje=true;
//}


QDataStream& operator<<(QDataStream &out,Osoba& osoba)
{

    out << qint32(osoba.Sifra());
    out << osoba._nepoznata;
    out <<  osoba.Ime().toStdString().c_str();
    out << osoba.Prezime().toStdString().c_str();
    char  pom[1];
    pom[0]=osoba.Pol().toLatin1();
    out << pom;
    out << osoba._datumRodjenja.toString().toStdString().c_str();
    out << osoba._datumSmrti.toString().toStdString().c_str();
    out << osoba._krvniSrodnik;
    return out;
}

QDataStream& operator>>(QDataStream &out,Osoba& osoba)
{
    qint32 a;
    out >> a;
    osoba._sifra=(short)a;
    out >> osoba._nepoznata;
    char* tren;
    out >> tren;
    osoba._ime=QString(tren);
    out >> tren;
    osoba._prezime=QString(tren);
    char *pom;
    out >> pom;
    osoba._pol=QChar(pom[0]);
    out >> tren;
    osoba._datumRodjenja=QDate::fromString(QString(tren));
    out >> tren;
    osoba._datumSmrti=QDate::fromString(QString(tren));
    out >> osoba._krvniSrodnik;
    //std::cout << tren.toStdString() << std::endl;
    return out;
}


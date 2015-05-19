#include"engine/osoba.h"
#include <QString>
short int Osoba::_sledecaSifra=0;


Osoba::Osoba()
    :_sifra(_sledecaSifra++),_nepoznata(true),_ime("N."),_prezime("N."),_pol('?'),_spisakVeza(2)
{}

Osoba::Osoba(std::string ime, std::string prezime, char pol, bool krvniSrodnik)
    :_sifra(_sledecaSifra++),_nepoznata(false),_ime(ime),_prezime(prezime),_pol(pol),_krvniSrodnik(krvniSrodnik),_spisakVeza(2)
{
    _deteOd=nullptr;
    _spisakVeza.clear();
}

Osoba::Osoba(const Osoba& druga)
    :_sifra(druga._sifra),_nepoznata(druga._nepoznata),_ime(druga._ime),_prezime(druga._prezime),_pol(druga._pol),_krvniSrodnik(druga._krvniSrodnik),_spisakVeza(druga._spisakVeza.size())
{
    _deteOd=nullptr;
    _spisakVeza.clear();
}


Osoba::~Osoba()
{
    _vecSeBrise=true;
    //brisem podatke o sebi kao detetu
    if(_deteOd!=nullptr)
    {
        _deteOd->BrisanjeOdOsobe();
        delete _deteOd;
    }

    //za svaku vezu iz spiska
    if(!_spisakVeza.empty()){
        std::vector<Brak*>::iterator b=_spisakVeza.begin();
        std::vector<Brak*>::iterator e=_spisakVeza.end();

        if(!_krvniSrodnik){
            for(;b!=e;b++)
            {
                (*b)->RaskiniSupruznike(this);//necu brisati i supruznika iz spiska, nego ga treba zamoliti da ukloni brak jer ostaje u porodici tj. ne brise se
                delete *b;//brisanje braka ce automatski obrisati svu decu i sve njihove potomke
            }
        }
        else//ako jeste krvni srodnik, onda treba pokrenuti samo brisanje druge osobe, koja ce zatim pokrenuti i ostatak brisanja kao u prethodnom
        {
            for(;b!=e;b++)
            {
                delete ((*b)->TudjaOsoba());
            }
        }
    }

}


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
/*
const char& Osoba::Pol() const
{
    return _pol;
}*/
/*
QDate& Osoba::DatumRodjenja()
{
    return _datumRodjenja;
}

QDate& Osoba::DatumSmrti()
{
    return _datumSmrti;
}
*/
bool Osoba::JeKrvniSrodnik()
{
    return _krvniSrodnik;
}

Dete* Osoba::Poreklo()
{
    return _deteOd;
}

void Osoba::PostaviPoreklo(Dete* poreklo)
{
    _deteOd=poreklo;
}

void Osoba::postaviSledecuSifru(int sifra)
{
    _sledecaSifra=sifra;
}

void Osoba::DodajVezu(Brak* veza)
{
    _spisakVeza.push_back(veza);
}


std::vector<Brak*>& Osoba::SpisakVeza()
{
    return _spisakVeza;
}

void Osoba::PretvoriUNepoznatu()
{
    _ime="N.";
    _prezime="N.";
    _pol='?';
    _nepoznata=true;
}

bool Osoba::Raskini(Brak* razvod)
{
    _spisakVeza.erase(std::remove(_spisakVeza.begin(), _spisakVeza.end(), razvod), _spisakVeza.end());
    return true;
}

bool Osoba::ObrisiPoreklo()
{
    _deteOd=nullptr;
    return true;
}

bool Osoba::RaskiniSveVeze()
{
    _deteOd=nullptr;
    _spisakVeza.clear();
    return true;
}

bool Osoba::VecSeBrisem()
{
    return _vecSeBrise;
}


QDataStream& operator<<(QDataStream &out,Osoba& osoba)
{
    out << qint32(osoba.Sifra());
    out << osoba._nepoznata;
    out << QString::fromStdString(osoba.Ime());
    out << QString::fromStdString(osoba.Prezime());
    out << QChar::fromLatin1(osoba._pol);
    out << osoba._datumRodjenja;
    out << osoba._datumSmrti;
    out << osoba._krvniSrodnik;
    out<<qint32(osoba._spisakVeza.size());


    return out;
}


QDataStream& operator>>(QDataStream &out,Osoba& osoba)
{
    out >> osoba._sifra;
    out >> osoba._nepoznata;
    QString tren;
    out >> tren;
    osoba._ime=tren.toStdString();
    out >> tren;
    osoba._prezime=tren.toStdString();
    QChar trenChar;
    out >> trenChar;
    osoba._pol=trenChar.toLatin1();
    out >> osoba._datumRodjenja;
    out >> osoba._datumSmrti;
    out >> osoba._krvniSrodnik;
    int velicinaSpiskaVeza;
    out >> velicinaSpiskaVeza;
    osoba._spisakVeza.resize(velicinaSpiskaVeza);
    osoba._deteOd=nullptr;

    return out;
}


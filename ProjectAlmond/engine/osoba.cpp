#include"engine/osoba.h"
#include <QString>
#include <iostream>
short int Osoba::_sledecaSifra=0;


Osoba::Osoba()
    :_sifra(_sledecaSifra++),_nepoznata(true),_ime("N."),_prezime("N."),_pol('?'),_spisakVeza()
{
    //std::cout << "kreira se NN osoba " << _sifra << std::endl;
    _deteOd = nullptr;
    _krvniSrodnik = false;
}

Osoba::Osoba(std::string ime, std::string prezime, char pol, bool krvniSrodnik)
    :_sifra(_sledecaSifra++),_nepoznata(false),_ime(ime),_prezime(prezime),_pol(pol),_krvniSrodnik(krvniSrodnik),_spisakVeza()
{
    _deteOd=nullptr;
    _spisakVeza.clear();

        //std::cout << "kreira se osoba " << _sifra << std::endl;
}

Osoba::Osoba(const Osoba& druga)
    :_sifra(druga._sifra),_nepoznata(druga._nepoznata),_ime(druga._ime),_prezime(druga._prezime),_pol(druga._pol),_krvniSrodnik(druga._krvniSrodnik),_spisakVeza(druga._spisakVeza.size())
{
    _deteOd=nullptr;
    _spisakVeza.clear();
}


Osoba::~Osoba()
{
    //std::cout << "brise se osoba " << Sifra() << std::endl;
    _vecSeBrisem=true;
    if(!_preskociRazvezivanje){
    //std::cout << "osoba razvezuje " << Sifra() << std::endl;
        //brisem podatke o sebi kao detetu
        if(_deteOd!=nullptr)
        {
            //std::cout << "osoba se brise kao dete " << Sifra() << std::endl;
            _deteOd->BrisanjeOdOsobe();
            if (!_deteOd->VecSeBrisem())
            delete _deteOd;
        }

        //za svaku vezu iz spiska
        if(!_spisakVeza.empty()){
            std::vector<Brak*>::iterator b=_spisakVeza.begin();
            std::vector<Brak*>::iterator e=_spisakVeza.end();

            if(!_krvniSrodnik){
                for(;b!=e;b++)
                {
                    //std::cout << "osoba nije k.s. i raskida brakove " << Sifra() << std::endl;
                    (*b)->RaskiniSupruznike(this);//necu brisati i supruznika iz spiska, nego ga treba zamoliti da ukloni brak jer ostaje u porodici tj. ne brise se
                    if (!(*b)->VecSeBrisem())
                    delete *b;//brisanje braka ce automatski obrisati svu decu i sve njihove potomke
                }
            }
            else//ako jeste krvni srodnik, onda treba pokrenuti samo brisanje druge osobe, koja ce zatim pokrenuti i ostatak brisanja kao u prethodnom
            {
                for(;b!=e;b++)
                {
                    //std::cout << "osoba jeste k.s. i brise supruznike " << Sifra() << std::endl;
                    if(!(*b)->VecSeBrisem())
                            ;
                        //izgleda je ovde greska...
                    delete ((*b)->TudjaOsoba());
                }
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
    return _vecSeBrisem;
}
void Osoba::PreskociRazvezivanje()
{
    _preskociRazvezivanje=true;
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


#include "porodicnostablo.h"



/*
Osoba _kljucnaOsoba;//osoba cije se porodicno stablo kreira
std::vector<Osoba*> _sveOsobe;//vektor sa pokazivacima na sve osobe u stablu
std::vector<Dete *> _svaDeca;//vektor sa pokazivacima na sve deca relacije u stablu
std::vector<Brak*> _sveVeze;//vektor sa pokazivacima na sve brak relacije u stablu
std::map<std::string, std::vector<Osoba*> > _indeksIme;//mapa koja vezuje parove ime, vektor svih osoba sa tim imenom
std::map<QDate, std::vector<Osoba*> > _indeksRodjenje;//mapa koja vezuje parove datum rodjenja, vektor svih osoba sa tim datumom rodjenja
std::map<int, std::vector<Osoba*> > _indeksRodjendan;//mapa koja vezuje dan [1,366] u godini, sa osobom kojoj je tog rednog dana u godini rodjendan
std::map<short int, Osoba* > _indeksSifraOsobe;//mapa koja vezuje sifru osobe za tu osobu
std::map<short int, Brak* > _indeksSifraVeza;//mapa koja vezuje sifru braka za taj brak
std::map<short int, Dete* > _indeksSifraDete;//mapa koja vezuje sifru deteta za konkretan relacioni objekat dete
*/


PorodicnoStablo::PorodicnoStablo()
    :_kljucnaOsoba()
{
    InicijalizujSveStrukture();
    _sveOsobe.push_back(&_kljucnaOsoba);

   (_indeksSifraOsobe[_kljucnaOsoba.Sifra()])=&_kljucnaOsoba;


}

PorodicnoStablo::PorodicnoStablo(std::string& ime, std::string& prezime,char pol,QDate datumRodjenja,QDate datumsmrti,bool krvniSrodnik)
    :_kljucnaOsoba(ime,prezime,pol,datumRodjenja,datumsmrti,krvniSrodnik)
{
    InicijalizujSveStrukture();
    _sveOsobe.push_back(&_kljucnaOsoba);
    _indeksIme[_kljucnaOsoba.Ime()]=std::vector<Osoba*>();
    _indeksIme[_kljucnaOsoba.Ime()].push_back(&_kljucnaOsoba);
    _indeksRodjenje[_kljucnaOsoba.DatumRodjenja()]=std::vector<Osoba*>();
    _indeksRodjenje[_kljucnaOsoba.DatumRodjenja()].push_back(&_kljucnaOsoba);
    _indeksRodjendan[_kljucnaOsoba.DatumRodjenja().daysInYear()]=std::vector<Osoba*>();
    _indeksRodjendan[_kljucnaOsoba.DatumRodjenja().daysInYear()].push_back(&_kljucnaOsoba);
    _indeksSifraOsobe[_kljucnaOsoba.Sifra()]=&_kljucnaOsoba;
}

PorodicnoStablo::~PorodicnoStablo()
{
    std::vector<Osoba*>::iterator b=_sveOsobe.begin();

    std::vector<Osoba*>::iterator e=_sveOsobe.end();

    for(;b!=e;b++)
    {
        (*b)->RaskiniSveVeze();
        delete *b;
    }


    std::vector<Dete*>::iterator b1=_svaDeca.begin();

    std::vector<Dete*>::iterator e1=_svaDeca.end();

    for(;b1!=e1;b1++)
    {
        (*b1)->RaskiniSveVeze();
        delete *b1;
    }


    std::vector<Brak*>::iterator b2=_sveVeze.begin();

    std::vector<Brak*>::iterator e2=_sveVeze.end();

    for(;b2!=e2;b2++)
    {
        (*b2)->RaskiniSveVeze();
        delete *b2;
    }



}

Osoba * PorodicnoStablo::KljucnaOsoba()
{
    return &_kljucnaOsoba;
}


//dodaje novu osobu u stablo,ocekuje se da posle poziva sledi i poziv za dodavanje deteta ili braka, da bi stablo bilo povezano u svakom momentu!!!
short int PorodicnoStablo::DodajOsobu(std::string ime, std::string prezime, char pol, QDate datumRodjenja, QDate datum_smrti, bool krvniSrodnik)
{
return 0;
}

//dodaje relaciju dete, od braka do osobe
short int PorodicnoStablo::DodajDete(short int sifraBraka,short int sifraOsobe,std::string trivija,QDate* datumUsvajanja)
{
    return 0;
}

//dodaje relaciju brak izmedju dve osobe date siframa
short int PorodicnoStablo::DodajBrak(short int sifraNaseOsobe, short int sifraTudjeOsobe, std::string trivija, QDate* datumUpoznavanja,QDate* datumVeze, QDate* datumRaskida, QDate* datumVeridbe, QDate* datumVencanja)
{
    return 0;
}


Osoba* PorodicnoStablo::NadjiOsobuSifrom(const short sifra)
{
    if(_indeksSifraOsobe.find(sifra)!=_indeksSifraOsobe.end())
        return _indeksSifraOsobe[sifra];
    return nullptr;
}

Dete* PorodicnoStablo::NadjiDeteSifrom(const short sifra)
{
    if(_indeksSifraDete.find(sifra)!=_indeksSifraDete.end())
        return _indeksSifraDete[sifra];
    return nullptr;
}

Brak* PorodicnoStablo::NadjiBrakSifrom(const short sifra)
{
    if(_indeksSifraVeza.find(sifra)!=_indeksSifraVeza.end())
        return _indeksSifraVeza[sifra];
    return nullptr;
}

void PorodicnoStablo::InicijalizujSveStrukture()
{
    _sveOsobe.clear();
    _svaDeca.clear();
    _sveVeze.clear();
    _indeksIme.clear();
    _indeksRodjenje.clear();
    _indeksRodjendan.clear();
    _indeksSifraDete.clear();
    _indeksSifraOsobe.clear();
    _indeksSifraVeza.clear();
}



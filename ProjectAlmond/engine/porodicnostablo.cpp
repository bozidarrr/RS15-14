#include "porodicnostablo.h"

PorodicnoStablo::PorodicnoStablo(std::string ime,std::string prezime,char pol,std::string datum_rodjenja,std::string datum_smrti)
    :_kljucnaOsoba(ime,prezime,pol,datum_rodjenja,datum_smrti),_sveOsobe(8),_nepovezane(),
      _sveRelacije(),_indeksPoImenu(),_indeksPoDatumu(),_indeksPoRodjendanu(),_indeksPoSifriOsoba(),_indeksPoSifriRelacija()
{
    _sveOsobe.push_back(&_kljucnaOsoba);
    _indeksPoImenu[_kljucnaOsoba.Ime()]=std::vector<Osoba *>();
    _indeksPoImenu[_kljucnaOsoba.Ime()].push_back(&_kljucnaOsoba);
    _indeksPoDatumu[_kljucnaOsoba.DatumRodjenja()]=std::vector<Osoba *>();
    _indeksPoDatumu[_kljucnaOsoba.DatumRodjenja()].push_back(&_kljucnaOsoba);
    _indeksPoRodjendanu[_kljucnaOsoba.DatumRodjenja().redniBroj()]=std::vector<Osoba *>();
    _indeksPoRodjendanu[_kljucnaOsoba.DatumRodjenja().redniBroj()].push_back(&_kljucnaOsoba);
    _indeksPoSifriOsoba[_kljucnaOsoba.Sifra()]=&_kljucnaOsoba;

}


PorodicnoStablo::~PorodicnoStablo()
{
    _sveRelacije.clear();
    _indeksPoRodjendanu.clear();
    _indeksPoDatumu.clear();
    _indeksPoImenu.clear();
    _indeksPoSifriOsoba.clear();
    _indeksPoSifriRelacija.clear();
    std::vector<Osoba*>::iterator b=_nepovezane.begin();
    std::vector<Osoba*>::iterator e=_nepovezane.end();
    for(;b!=e;b++)delete *b;
    b=_sveOsobe.begin();
    e=_sveOsobe.end();
    for(;b!=e;b++)delete *b;
}


short int PorodicnoStablo::DodajOsobu(std::string ime, std::string prezime,char pol,std::string datum_rodjenja, std::string datum_smrti)
{
    Osoba* tren=new Osoba(ime,prezime,pol,datum_rodjenja,datum_smrti);
    _nepovezane.push_back(tren);
    if(_indeksPoImenu.find(tren->Ime())==_indeksPoImenu.end())
        _indeksPoImenu[tren->Ime()]=std::vector<Osoba*>();
    _indeksPoImenu[tren->Ime()].push_back(tren);
    if(_indeksPoDatumu.find(tren->DatumRodjenja())==_indeksPoDatumu.end())
        _indeksPoDatumu[tren->DatumRodjenja()]=std::vector<Osoba*>();
    _indeksPoDatumu[tren->DatumRodjenja()].push_back(tren);
    int rbroj=tren->DatumRodjenja().redniBroj();
    if(_indeksPoRodjendanu.find(rbroj)==_indeksPoRodjendanu.end())
        _indeksPoRodjendanu[rbroj]=std::vector<Osoba*>();
    _indeksPoRodjendanu[rbroj].push_back(tren);

    if(_indeksPoSifriOsoba.find(tren->Sifra())==_indeksPoSifriOsoba.end())
        _indeksPoSifriOsoba[tren->Sifra()]=tren;
    else
    {
        delete tren;
        return -1;
    }//jer je neki problem nastao, dodajemo dve osobe sa istom sifrom!

    return tren->Sifra();
}


short int PorodicnoStablo::PoveziOsobe(const short sifra1,const short sifra2,Odnos srodstvo)
{
    Osoba* prva=nadjiOsobuPoSifri(sifra1);
    Osoba* druga=nadjiOsobuPoSifri(sifra2);
    return PorodicnoStablo::PoveziOsobe(prva,druga,srodstvo);

}

short int PorodicnoStablo::PoveziOsobe(Osoba *prva,  Osoba *druga, Odnos srodstvo)
{

    if(prva==nullptr || druga==nullptr)
        throw "Jedna osoba ne postoji";

    //refaktorisi----------------------
    if(osobaJeNepovezana(prva->Sifra())){
        _nepovezane.erase(std::remove(_nepovezane.begin(), _nepovezane.end(), prva), _nepovezane.end());
        _sveOsobe.push_back(prva);
    }
    if(osobaJeNepovezana(druga->Sifra())){
        _nepovezane.erase(std::remove(_nepovezane.begin(), _nepovezane.end(), druga), _nepovezane.end());
        _sveOsobe.push_back(druga);
    }
    //---------------------------------

    switch(srodstvo){
    case BRAT_SESTRA:
    case RODITELJ:
    case DETE:
    case SUPRUZNIK:
        Supruznik *nov=new Supruznik;
        prva->Supruznici().push_back(nov);
        druga->Supruznici().push_back(nov);
        if(_indeksPoSifriRelacija.find(nov->Sifra())==_indeksPoSifriRelacija.end())
            _indeksPoSifriRelacija[nov->Sifra()]=nov;
        else
        {
            delete nov;
            return -1;
        }
        std::cout<<"Uspesno povezao"<<std::endl;
        return nov->Sifra();
        break;
    }
    return -1;

}




Osoba* PorodicnoStablo::nadjiOsobuPoSifri(const short sifra)
{
    /*    std::vector<Osoba *>::iterator nadjena=std::find_if(_nepovezane.begin(),_nepovezane.end(),[sifra](Osoba* ova){return (ova->Sifra())==sifra;});
    if(nadjena!=_nepovezane.end())return *nadjena;

    nadjena=std::find_if(_sveOsobe.begin(),_sveOsobe.end(),[sifra](Osoba* ova){return (ova->Sifra())==sifra;});
    if(nadjena!=_sveOsobe.end())return *nadjena;
*/
    if(_indeksPoSifriOsoba.find(sifra)==_indeksPoSifriOsoba.end())
        return nullptr;//onda nema te osobe
    else
        return _indeksPoSifriOsoba[sifra];

}


bool PorodicnoStablo::osobaJeNepovezana(short sifra) const
{
    return std::find_if(_nepovezane.begin(),_nepovezane.end(),[sifra](Osoba* ova){return (ova->Sifra())==sifra;})!=_nepovezane.end();
}


/*
std::string PronadjiOdnos(const short sifra1,const short sifra2)
{
    return "rodjak";
}

std::string PronadjiOdnos(const Osoba* prva,const Osoba* druga)
{

}
*/
bool PorodicnoStablo::stabloJePovezano()const
{
    return _nepovezane.size()==0;
}



Osoba * PorodicnoStablo::KljucnaOsoba(){
    return &_kljucnaOsoba;
}



bool PorodicnoStablo::UkloniOsobuPoSifri(const short sifra)
{
    Osoba *obrisiMe=nadjiOsobuPoSifri(sifra);
    if(obrisiMe==nullptr)return false;

    std::vector<Supruznik*>::iterator b=obrisiMe->Supruznici().begin();
    std::vector<Supruznik*>::iterator e=obrisiMe->Supruznici().end();
    for(;b!=e;b++){

        _sveRelacije.erase(std::remove(_sveRelacije.begin(), _sveRelacije.end(), *b), _sveRelacije.end());
        _indeksPoSifriRelacija.erase((*b)->Sifra());

    }

    _sveOsobe.erase(std::remove(_sveOsobe.begin(), _sveOsobe.end(), obrisiMe), _sveOsobe.end());
    _nepovezane.erase(std::remove(_nepovezane.begin(), _nepovezane.end(), obrisiMe), _nepovezane.end());

    _indeksPoImenu[obrisiMe->Ime()].erase(std::remove(_indeksPoImenu[obrisiMe->Ime()].begin(), _indeksPoImenu[obrisiMe->Ime()].end(), obrisiMe), _indeksPoImenu[obrisiMe->Ime()].end());
    _indeksPoDatumu[obrisiMe->DatumRodjenja()].erase(std::remove(_indeksPoDatumu[obrisiMe->DatumRodjenja()].begin(),_indeksPoDatumu[obrisiMe->DatumRodjenja()].end(), obrisiMe),_indeksPoDatumu[obrisiMe->DatumRodjenja()].end());
    _indeksPoRodjendanu[obrisiMe->DatumRodjenja().redniBroj()].erase(std::remove(_indeksPoRodjendanu[obrisiMe->DatumRodjenja().redniBroj()].begin(),_indeksPoDatumu[obrisiMe->DatumRodjenja()].end(), obrisiMe),_indeksPoRodjendanu[obrisiMe->DatumRodjenja().redniBroj()].end());
    _indeksPoSifriOsoba.erase(obrisiMe->Sifra());

    //ovo ce pozvati destruktor za osobu, koji ce potom pozvati destruktore svih relacija koje su vezane sa tom osobom, kao i izvrisiti uklanjanje internih veza iz osobe
    delete obrisiMe;

    return true;
}

bool PorodicnoStablo::UkloniRelacijuPoSifri(const short sifra)
{
    Relacija* obrisiMe=nadjiRelacijuPoSifri(sifra);
    if(obrisiMe==nullptr)
        return false;
    _sveRelacije.erase(std::remove(_sveRelacije.begin(), _sveRelacije.end(), obrisiMe), _sveRelacije.end());
    _indeksPoSifriRelacija.erase(obrisiMe->Sifra());
    delete obrisiMe;
    return true;
}

Relacija* PorodicnoStablo::nadjiRelacijuPoSifri(const short sifra){

    if(_indeksPoSifriRelacija.find(sifra)==_indeksPoSifriRelacija.end())
        return nullptr;//onda nema te relacije
    else
        return _indeksPoSifriRelacija[sifra];
}

/*
Osoba* _kljucnaOsoba;//osoba koja je okosnica ovog porodicnog stabla tj na kojoj je fokus naseg stabla (svi njeni rodjaci i supruznici su prikazani, ostali su redukovani do na prvi stepen)
std::vector<Osoba*> _sveOsobe;//vektor sa pokazivacima na sve osobe
std::vector<Osoba*> _nepovezane;//vektor koji sadrzi pokazivace na novokreirane, jos nepovezane osobe
std::vector<Relacija*> _sveRelacije;//vektor koji sadrzi pokazivace na objekte relacije
std::map<std::string, std::vector<Osoba*> > _indeksPoImenu;//mapa koja vezuje parove ime, vektor svih osoba sa tim imenom
std::map<Datum, std::vector<Osoba*> > _indeksPoDatumu;//mapa koja vezuje parove datum rodjenja, vektor svih osoba sa tim datumom rodjenja
std::map<int, std::vector<Osoba*> > _indeksPoRodjendanu;//mapa koja vezuje dan [1,366] u godini, sa osobom kojoj je tog rednog dana u godini rodjendan
std::map<short int,Osoba*> _indeksPoSifriOsobe
std::map<short int, Relacija*> _indeksPoSifriRelacije
*/

































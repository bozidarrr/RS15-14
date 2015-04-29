#include "porodicnostablo.h"
/*
Osoba* _kljucnaOsoba;//osoba koja je okosnica ovog porodicnog stabla tj na kojoj je fokus naseg stabla (svi njeni rodjaci i supruznici su prikazani, ostali su redukovani do na prvi stepen)
std::vector<Osoba*> _sveOsobe;//vektor sa pokazivacima na sve osobe
std::vector<Osoba*> _nepovezane;//vektor koji sadrzi pokazivace na novokreirane, jos nepovezane osobe
std::vector<Relacija*> _sveRelacije;//vektor koji sadrzi pokazivace na objekte relacije
std::map<std::string, std::vector<Osoba*> > _indeksPoImenu;//mapa koja vezuje parove ime, vektor svih osoba sa tim imenom
std::map<Datum, std::vector<Osoba*> > _indeksPoDatumu;//mapa koja vezuje parove datum rodjenja, vektor svih osoba sa tim datumom rodjenja
std::map<int, std::vector<Osoba*> > _indeksPoRodjendanu;//mapa koja vezuje dan [1,366] u godini, sa osobom kojoj je tog rednog dana u godini rodjendan
*/
PorodicnoStablo::PorodicnoStablo(std::string ime,std::string prezime,std::string datum_rodjenja,std::string datum_smrti)
    :_kljucnaOsoba(ime,prezime,datum_rodjenja,datum_smrti),_sveOsobe(8),_nepovezane(),_sveRelacije(),_indeksPoImenu(),_indeksPoDatumu(),_indeksPoRodjendanu()
{
    _sveOsobe.push_back(&_kljucnaOsoba);
    _indeksPoImenu[_kljucnaOsoba.Ime()]=std::vector<Osoba *>();
    _indeksPoImenu[_kljucnaOsoba.Ime()].push_back(&_kljucnaOsoba);
    _indeksPoDatumu[_kljucnaOsoba.DatumRodjenja()]=std::vector<Osoba *>();
    _indeksPoDatumu[_kljucnaOsoba.DatumRodjenja()].push_back(&_kljucnaOsoba);
    _indeksPoRodjendanu[_kljucnaOsoba.DatumRodjenja().redniBroj()]=std::vector<Osoba *>();
    _indeksPoRodjendanu[_kljucnaOsoba.DatumRodjenja().redniBroj()].push_back(&_kljucnaOsoba);

}


PorodicnoStablo::~PorodicnoStablo()
{
    //todo
}


short int PorodicnoStablo::DodajOsobu(std::string ime, std::string prezime,std::string datum_rodjenja, std::string datum_smrti)
{
    Osoba* tren=new Osoba(ime,prezime,datum_rodjenja,datum_smrti);
    _nepovezane.push_back(tren);
    if(_indeksPoImenu.find(tren->Ime())==_indeksPoImenu.end())_indeksPoImenu[tren->Ime()]=std::vector<Osoba*>();
    _indeksPoImenu[tren->Ime()].push_back(tren);
    if(_indeksPoDatumu.find(tren->DatumRodjenja())==_indeksPoDatumu.end())_indeksPoDatumu[tren->DatumRodjenja()]=std::vector<Osoba*>();
    _indeksPoDatumu[tren->DatumRodjenja()].push_back(tren);
    int rbroj=tren->DatumRodjenja().redniBroj();
    if(_indeksPoRodjendanu.find(rbroj)==_indeksPoRodjendanu.end())_indeksPoRodjendanu[rbroj]=std::vector<Osoba*>();
    _indeksPoRodjendanu[rbroj].push_back(tren);

    return tren->Sifra();
}

/*
short int PoveziOsobe(const short sifra1,const short sifra2,Odnos srodstvo)
{


}
short int PoveziOsobe(const Osoba* prva,const Osoba * druga,Odnos srodstvo)
{


}

Osoba* nadjiOsobuPoSifri(const short sifra)
{

}

std::string PronadjiOdnos(const short sifra1,const short sifra2)
{
    return "rodjak";
}

std::string PronadjiOdnos(const Osoba* prva,const Osoba* druga)
{

}
*/
bool PorodicnoStablo::stabloJePovezano()
{
return _nepovezane.size()==0;
}




#ifndef PORODICNOSTABLO_H
#define PORODICNOSTABLO_H
#include<vector>
#include<map>
#include"engine/osoba.h"
#include"engine/supruznik.h"

enum Odnos{RODITELJ,DETE,BRAT_SESTRA,SUPRUZNIK};

/**
 * @brief The PorodicnoStablo class sluzi za pamcenje podataka o povezanosti clanova stabla, kao i njihovo indeksiranje.
 */
class PorodicnoStablo
{
public:
    PorodicnoStablo(std::string ime, std::string prezime, std::string datum_rodjenja, std::string datum_smrti="");
    ~PorodicnoStablo();
  //  PorodicnoStablo(const PorodicnoStablo& drugo);
  //  PorodicnoStablo& operator=(const PorodicnoStablo& drugo);

//vraca sifru novokreirane osobe, ili -1 ako operacija nije uspesna iz nekog razloga
    short int DodajOsobu(std::string ime, std::string prezime,std::string datum_rodjenja, std::string datum_smrti = "");

//povezuje dve odabrane osobe, u srodstvo koje se kreira, a vraca sifru kreirane relacije ili -1 u slucaju neuspeha
    short int PoveziOsobe(const short sifra1,const short sifra2,Odnos srodstvo);
    short int PoveziOsobe(const Osoba* prva,const Osoba * druga,Odnos srodstvo);

//vraca pokazivac na osobu, na osnovu njene sifre
    Osoba* nadjiOsobuPoSifri(const short sifra);


//vraca odnos u porodicnom stablu izmedju dve date osobe
    std::string PronadjiOdnos(const short sifra1,const short sifra2);
    std::string PronadjiOdnos(const Osoba* prva,const Osoba* druga);

//ispituje da li je stablo povezano, radi omogucenja/onemogucenja odredjenih operacija
    bool stabloJePovezano();


private:
    Osoba _kljucnaOsoba;//osoba koja je okosnica ovog porodicnog stabla tj na kojoj je fokus naseg stabla (svi njeni rodjaci i supruznici su prikazani, ostali su redukovani do na prvi stepen)
    std::vector<Osoba*> _sveOsobe;//vektor sa pokazivacima na sve osobe
    std::vector<Osoba*> _nepovezane;//vektor koji sadrzi pokazivace na novokreirane, jos nepovezane osobe
    std::vector<Relacija*> _sveRelacije;//vektor koji sadrzi pokazivace na objekte relacije
    std::map<std::string, std::vector<Osoba*> > _indeksPoImenu;//mapa koja vezuje parove ime, vektor svih osoba sa tim imenom
    std::map<Datum, std::vector<Osoba*> > _indeksPoDatumu;//mapa koja vezuje parove datum rodjenja, vektor svih osoba sa tim datumom rodjenja
    std::map<int, std::vector<Osoba*> > _indeksPoRodjendanu;//mapa koja vezuje dan [1,366] u godini, sa osobom kojoj je tog rednog dana u godini rodjendan




};

#endif // PORODICNOSTABLO_H

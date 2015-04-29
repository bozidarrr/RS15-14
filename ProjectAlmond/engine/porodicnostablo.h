#ifndef PORODICNOSTABLO_H
#define PORODICNOSTABLO_H
#include<vector>
#include<list>
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
    PorodicnoStablo();
    ~PorodicnoStablo();
    PorodicnoStablo(const PorodicnoStablo& drugo);
    PorodicnoStablo& operator=(const PorodicnoStablo& drugo);

    /**
     * @brief DodajOsobu dodaje osobu u memorijsku strukturu i podesava parametar _povezano na false
     * @param ime ime osobe koja se dodaje
     * @param prezime prezime osobe koja se dodaje
     * @param datum_rodjenja datum rodjenja osobe koja se dodaje
     * @param datum_smrti datum smrti, ako postoji
     */
    void DodajOsobu(std::string ime, std::string prezime,std::string datum_rodjenja, std::string datum_smrti = "");

    /**
     * @brief PoveziOsobe Povezuje dve osobe po njihovoj sifri
     * @param sifra1
     * @param sifra2
     * @param srodstvo povezuje dve osobe odredjenim tipom srodstva, time sugerisuci koji relacioni objekat treba kreirati
     */
    void PoveziOsobe(short sifra1,short sifra2,Odnos srodstvo);
    void PoveziOsobe(const Osoba* prva,const Osoba * druga,Odnos srodstvo);


    std::string PronadjiOdnos(short sifra1,short sifra2)const;
    std::string PronadjiOdnos(const Osoba* prva,const Osoba* druga)const;

    bool stabloJePovezano()const;

private:
    bool _povezano;
    std::vector<Osoba*> _sveOsobe;
    std::vector<Relacija*> _sveRelacije;
    std::map<std::string, std::list<Osoba*> > _indeksPoImenu;
    std::map<Datum, std::list<Osoba*> > _indeksPoDatumu;
    std::map<int, std::list<Osoba*> > _indeksPoRodjendanu;



};

#endif // PORODICNOSTABLO_H

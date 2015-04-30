#ifndef _OSOBA_H_
#define _OSOBA_H_ 1

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "alati/datum.h"
#include "engine/supruznik.h"
class Supruznik;

/**
 * @brief The Osoba class Sluzi za cuvanje podatka o jednoj Osobi u porodicnom stablu
 */
class Osoba
{
public:

    Osoba(const std::string ime, const std::string prezime,const char pol,
          const std::string datum_rodjenja, const std::string datum_smrti = "");//pri kreiranju, osoba dobija jedinstvenu sifru. Prepostavljamo da nece biti u okviru stabla kreirano previse osoba


    ~Osoba();//ovo sam nekada znao sta radi

    Osoba(const Osoba& nova);
    Osoba& operator=(Osoba& nova);

    short int Sifra()const;//vraca sifru

    const std::string& Ime() const;//vraca ime

    const std::string& Prezime() const;//vraca prezime

    const Datum& DatumRodjenja() const;//vraca datum rodjenja

    const Datum& DatumSmrti() const;//vraca datum smrti

    char Pol() const;//vraca pol

    /**
     * @brief UkloniSupruznika uklanja dati element iz liste supruznika, jer je njegova dealokacija u toku (te stoga ni ne zahteva njegovu dealokaciju)
     * @param inicijator element liste supruznici kojeg treba obrisati sa spiska supruznika
     */
    void UkloniSupruznika(Supruznik* inicijator);

    /**
     * @brief ProveriPodatke proverava validnost licnih podataka regularnim izrazima
     * @return true ako je u redu false inace
     */
    bool ProveriPodatke()const;


    std::vector<Supruznik*> &Supruznici();

private:

    static short int _MinSifra;//staticko polje koje zapravo odredjuje sledecu sifru koja ce biti dodeljena
    std::string _ime;
    std::string _prezime;
    char _pol;
    Datum _datum_rodjenja;
    Datum _datum_smrti;

    //list<Relacija> roditelji;
    //list<Relacija> deca;
    //list<Relacija> bracaIsestre;
    std::vector<Supruznik*> _supruznici;//lista koja sadrzi pokazivace na objekte relacije tipa supruznik
    short int _sifra;

};

#endif

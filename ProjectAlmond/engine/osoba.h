#ifndef _OSOBA_H_
#define _OSOBA_H_ 1
class Supruznik;
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "alati/datum.h"
#include "engine/supruznik.h"
/**
 * @brief The Osoba class Sluzi za cuvanje podatka o jednoj Osobi u porodicnom stablu
 */
class Osoba
{
public:

    Osoba(std::string ime, std::string prezime,
          std::string datum_rodjenja, std::string datum_smrti = "");

    //vidi destruktor sto je lep, dok jos znam da objasnim sta radi
    ~Osoba();

    short Sifra()const;

    const std::string& Ime() const;

    const std::string& Prezime() const;

    const Datum& DatumRodjenja() const;

    const Datum& DatumSmrti() const;

    char Pol() const;

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

    /**
     * @brief PronadjiVezu pronalazi tip srodstva izmedju aktivne osobe i neke druge prosledjene po referenci
     * @param o Osoba sa kojom se trazi stepen srodstva
     * @return string sa (lokalizovanim) nazivom srodstva ako je moguce ili "rodjak"
     */
    std::string PronadjiVezu(const Osoba & o)const;


private:

    static short int _MinSifra;
    std::string _ime;
    std::string _prezime;
    Datum _datum_rodjenja;
    Datum _datum_smrti;
    char _pol;

    //list<Relacija> roditelji;
    //list<Relacija> deca;
    //list<Relacija> bracaIsestre;
    std::vector<Supruznik*> _supruznici;
    short int _sifra;

};

#endif

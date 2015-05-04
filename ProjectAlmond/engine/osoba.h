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


    //destruktor osobe uklanja i osobu, kao i sve veze koje je ona imala, pritom obavestavajuci drugu osobu u vezi da mora
    //azurirati svoj spisak veza, odnosno ukloniti nepostojece pokazivace
    ~Osoba();

    Osoba(const Osoba& nova);
    Osoba& operator=(Osoba& nova);

    short int Sifra()const;//vraca sifru

    const std::string& Ime() const;//vraca ime

    const std::string& Prezime() const;//vraca prezime

    const Datum& DatumRodjenja() const;//vraca datum rodjenja

    const Datum& DatumSmrti() const;//vraca datum smrti

    char Pol() const;//vraca pol

    std::vector<Supruznik*>& Supruznici();//vraca listu svih supruznika

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

    std::string toString()const;

private:

    static short int _MinSifra;//staticko polje koje zapravo odredjuje sledecu sifru koja ce biti dodeljena
    short int _sifra;
    std::string _ime;
    std::string _prezime;
    char _pol;//Moze biti samo 'm' ili 'z', za sada to kontrolise samo GUI, ubaciti i ovde kontrolu
    Datum _datum_rodjenja;
    Datum _datum_smrti;

    std::vector<Supruznik*> _supruznici;//lista koja sadrzi pokazivace na objekte relacije tipa supruznik



};

#endif

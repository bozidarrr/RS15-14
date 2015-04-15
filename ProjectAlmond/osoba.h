#ifndef _OSOBA_H_
#define _OSOBA_H_ 1

#include <iostream>
#include <list>
#include <string>
#include "datum.h"
#include "relacija.h"
#include "supruznik.h"


class Osoba
{
public:
Osoba(std::string ime, std::string prezime,
        std::string datum_rodjenja, std::string datum_smrti = "");

/* provera ispravnosti podataka? reg.exp? */

const std::string& Ime() const;

const std::string& Prezime() const;

const Datum& DatumRodjenja() const;

const Datum& DatumSmrti() const;

char Pol() const;

/*
string& PronadjiVezu(const Osoba & o)const;
*/

private:
std::string _ime;
std::string _prezime;
Datum _datum_rodjenja;
Datum _datum_smrti;
char _pol;
/*
list<Relacija> roditelji;
list<Relacija> deca;
list<Relacija> sibling??;
list<Relacija> supruznici;
*/

};

#endif

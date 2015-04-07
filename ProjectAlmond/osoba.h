#ifndef _OSOBA_H_
#define _OSOBA_H_ 1

#include <iostream>
#include <list>
#include <string>
#include "datum.h"

using namespace std;

class Osoba
{
public:
Osoba(string ime, string prezime, 
        string datum_rodjenja, string datum_smrti = NULL)
	: _ime(ime), _prezime(prezime), 
	_datum_rodjenja(datum_rodjenja), _datum_smrti(datum_smrti)
	{
		/* inicijalizacija listi veza */
	}


/* provera ispravnosti podataka? reg.exp? */

const string& Ime() const
{
	return _ime;
} 

const string& Prezime() const
{
	return _prezime;
} 

const Datum& DatumRodjenja() const
{
	return _datum_rodjenja;
} 

const Datum& DatumSmrti() const
{
	return _datum_smrti;
} 

const char Pol() const
{
	return _pol;
} 

/*
string& PronadjiVezu(const Osoba & o)
{


}
*/

private:
string _ime;
string _prezime;
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

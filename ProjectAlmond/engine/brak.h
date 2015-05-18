#ifndef BRAK_H
#define BRAK_H

#include<vector>
#include<string>
#include<QDate>

#include"engine/osoba.h"
class Osoba;
class Dete;

class Brak
{
public:
    Brak(Osoba* nasa, Osoba* tudja, std::string& trivija);
    ~Brak();

    //----geteri i seteri------//
    short int Sifra();
    Osoba* NasaOsoba();
    Osoba* TudjaOsoba();
    std::vector<Dete*>& SpisakDece();
    std::string& Trivija();/*
    QDate& DatumUpoznavanja();
    QDate& DatumVeze();
    QDate& DatumRaskida();
    QDate& DatumVeridbe();
    QDate& DatumVencanja();

*/

    //----geteri i seteri------//

    //---metodi korisni u upotrebi---//
    void DodajDete(Dete* beba);

    //OVI JOS NE RADE!!!!
    bool UVezi();
    bool Vereni();
    bool Vencani();
    bool Rastavljeni();
    //---metodi korisni u upotrebi---//

    //----metodi potrebni za brisanje----//
    bool DeteSeUklanja(Dete *obrisiMe);//detetov destruktor ce biti pozvan, pa se zahteva uklanjanje deteta iz spiska dece
    bool RaskiniSupruznike(Osoba *inicijator);//jedna osoba se brise, pa se zahteva da druga osoba ukloni podatke o braku iz svoje evidencije brakova
    bool RaskiniSveVeze();
    //----metodi potrebni za brisanje----//

    //----metodi potrebni za citanje i pisanje----//
    friend QDataStream& operator<<(QDataStream &out,Brak& brak);
    friend QDataStream& operator>>(QDataStream &in,Brak& brak);
    //----metodi potrebni za citanje i pisanje----//

private:
    static short int _sledecaSifra;
    short int _sifra;
    Osoba* _nasaOsoba;
    Osoba* _tudjaOsoba;
    std::vector<Dete *> _spisakDece;
    std::string _trivija;
    /* QDate _datumUpoznavanja;
    QDate _datumVeze;
    QDate _datumVeridbe;
    QDate _datumVencanja;
    QDate _datumRaskida;*/
};

#endif // BRAK_H

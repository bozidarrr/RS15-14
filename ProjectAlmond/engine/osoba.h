#ifndef _OSOBA_H_
#define _OSOBA_H_ 1

#include <vector>
#include <string>

#include <QDate>
#include<QDataStream>
#include "engine/dete.h"
#include "engine/brak.h"
class Dete;
class Brak;

class Osoba
{
public:

    Osoba(bool krvniSrodnik = false); //kreira N.N lice
    Osoba(std::string ime, std::string prezime, char pol, bool krvniSrodnik); //kreira validnu osobu, ali bez pokazivaca za roditelje
    Osoba(const Osoba& druga);//samo podatke, ne i veze!!!

    ~Osoba(); //uklanja osobu, sve njene podatke i poziva uklanjanje sopstvenog pointera iz brakova, kao i unistavanje relacionog objekta Dete


    //----geteri i seteri------//
    short int Sifra()const;//vraca sifru

    const std::string& Ime() const;//vraca ime

    const std::string& Prezime() const;//vraca prezime

    //const& char Pol() const;

   // QDate& DatumRodjenja(); //vraca datum rodjenja

   // QDate& DatumSmrti(); //vraca datum smrti

    bool JeKrvniSrodnik(); //vraca da li je osoba u krvnom srodstvu sa kljucnom osobom

    //Dete* Poreklo(); //vraca adresu relacionog objekta dete, kojim se moze povezati sa brakom/vezom iz koje je nastala osoba

    //void PostaviPoreklo(Dete* poreklo);

    static void postaviSledecuSifru(int sifra);

    //void DodajVezu(Brak* veza);

    //std::vector<Brak*>& SpisakVeza(); //vraca referencu na spisak svih veza koje je osoba imala
    //----geteri i seteri------//

    //---metodi korisni u upotrebi---//
    void PretvoriUNepoznatu();//pretvara podatke date osobe u nepoznatu, ali cuva sve veze koje je ona imala

    //---metodi korisni u upotrebi---//

    //----metodi potrebni za brisanje----//
    //bool Raskini(Brak* razvod);//posto se brise podatak o braku, zahteva se od osobe da ukloni pokazivac za brak iz svog spiska

    //bool ObrisiPoreklo(); //brise podatke o relacionom objektu dete

    //bool RaskiniSveVeze(); //brise sve veze, zarad pripreme za brisanje na vecoj skali

    bool VecSeBrisem(); //proverava da li je vec pozvan destruktor, da ne bi dva puta oslobadjali
    //void PreskociRazvezivanje();
    //----metodi potrebni za brisanje----//

//----metodi za citanje i pisanje ----//

    friend QDataStream& operator<<(QDataStream& out,Osoba& osoba);
    friend QDataStream& operator>>(QDataStream& out,Osoba& osoba);

    //----metodi za citanje i pisanje ----//




private:

    //----osnovni podaci----//
    static short int _sledecaSifra;
    int _sifra;
    bool _nepoznata;
    std::string _ime;
    std::string _prezime;
    char _pol;
    QDate _datumRodjenja;
    QDate _datumSmrti;
    bool _krvniSrodnik;
    //Dete * _deteOd;
    //std::vector<Brak *> _spisakVeza;
    bool _vecSeBrisem=false;
    bool _preskociRazvezivanje=false;
    //----osnovni podaci----//
    //--------------------------------------------------------------//
    //----napredni podaci----//

    //----napredni podaci----//

};

#endif

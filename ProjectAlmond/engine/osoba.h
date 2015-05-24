#ifndef _OSOBA_H_
#define _OSOBA_H_ 1

#include <vector>
#include <string>
#include <QString>
#include <QDate>
#include<QDataStream>
//#include "engine/dete.h"
//#include "engine/brak.h"
//class Dete;
//class Brak;

/**
 *  static short int _sledecaSifra;
    int _sifra;
    bool _nepoznata;
    std::string _ime;
    std::string _prezime;
    char _pol;
    QDate _datumRodjenja;
    QDate _datumSmrti;
    bool _krvniSrodnik;
 *
 *
**/

class Osoba
{
public:

    Osoba(bool krvniSrodnik = false); //kreira N.N lice
    Osoba(const QString &ime, const QString &prezime, const QChar &pol, const QDate &rodjenje, const QDate &smrt, bool krvniSrodnik);
    //Osoba(std::string ime, std::string prezime, char pol, bool krvniSrodnik); //kreira validnu osobu, ali bez pokazivaca za roditelje
    Osoba(const Osoba& druga);//samo podatke, ne i veze!!!

    ~Osoba(); //uklanja osobu, sve njene podatke i poziva uklanjanje sopstvenog pointera iz brakova, kao i unistavanje relacionog objekta Dete


    //----geteri i seteri------//
    short int Sifra() const;//vraca sifru

    const QString &Ime() const;//vraca ime

    const QString& Prezime() const;//vraca prezime

    const QString* ImePrezime() const;//cini mi se da je korisno

    const QChar& Pol() const;

    const QDate& DatumRodjenja() const; //vraca datum rodjenja

    const QDate& DatumSmrti() const; //vraca datum smrti

    bool JeKrvniSrodnik() const; //vraca da li je osoba u krvnom srodstvu sa kljucnom osobom

    static void postaviSledecuSifru(int sifra);

    void PromeniIme(const QString &ime);
    void PromeniPrezime(const QString &prezime);
    void PromeniPol(const QChar &pol);
    void PromeniDatumRodjenja(const QDate &datum);
    void PromeniDatumSmrti(const QDate &datum);

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
    QString _ime;
    QString _prezime;
    QChar _pol;
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

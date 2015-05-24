#ifndef BRAK_H
#define BRAK_H

#include<vector>
#include<string>
#include<QDate>

//#include"engine/osoba.h"
//class Osoba;
//class Dete;

class Brak
{
public:
    Brak();
    //Brak(Osoba* nasa, Osoba* tudja, std::string& trivija);
    Brak(short sifraNase, short sifraTudje, std::string &trivija);
    Brak(const Brak& drugi);
    ~Brak();

    //----geteri i seteri------//
    short int Sifra();
    short SifraNase();
    short SifraTudje();
    //Osoba* NasaOsoba();
    //Osoba* TudjaOsoba();
    //std::vector<Dete*>& SpisakDece();
    std::string& Trivija();/*
    QDate& DatumUpoznavanja();
    QDate& DatumVeze();
    QDate& DatumRaskida();
    QDate& DatumVeridbe();
    QDate& DatumVencanja();
*/
    //void PostaviNasuOsobu(Osoba* nasa);
    //void PostaviTudjuOsobu(Osoba* tudja);


    //----geteri i seteri------//
    static void postaviSledecuSifru(int sifra);

    //---metodi korisni u upotrebi---//
    //void DodajDete(Dete* beba);

    //OVI JOS NE RADE!!!!
    bool UVezi();
    bool Vereni();
    bool Vencani();
    bool Rastavljeni();
    //---metodi korisni u upotrebi---//

    //----metodi potrebni za brisanje----//
    //bool DeteSeUklanja(Dete *obrisiMe);//detetov destruktor ce biti pozvan, pa se zahteva uklanjanje deteta iz spiska dece
    //bool RaskiniSupruznike(Osoba *inicijator);//jedna osoba se brise, pa se zahteva da druga osoba ukloni podatke o braku iz svoje evidencije brakova
    //bool RaskiniSveVeze();
    bool VecSeBrisem();
    void PreskociRazvezivanje();
    //----metodi potrebni za brisanje----//

    //----metodi potrebni za citanje i pisanje----//
    friend QDataStream& operator<<(QDataStream &out,Brak& brak);
    friend QDataStream& operator>>(QDataStream &in,Brak& brak);
    //----metodi potrebni za citanje i pisanje----//

private:
    static short int _sledecaSifra;
    short int _sifra;
    short _sifraNase;
    short _sifraTudje;
    //Osoba* _nasaOsoba;
    //Osoba* _tudjaOsoba;
    //std::vector<Dete *> _spisakDece;
    std::string _trivija;
    /* QDate _datumUpoznavanja;
    QDate _datumVeze;
    QDate _datumVeridbe;
    QDate _datumVencanja;
    QDate _datumRaskida;*/
    bool _vecSeBrisem=false;
    bool _preskociRazvezivanje=false;
};

#endif // BRAK_H

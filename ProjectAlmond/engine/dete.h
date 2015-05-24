#ifndef DETE_H
#define DETE_H
#include <string>
#include <QDate>

//#include "engine/brak.h"
//#include "engine/osoba.h"
//class Brak;
//class Osoba;

class Dete
{
public:
    Dete();
    //Dete(Osoba* osoba, Brak* roditeljskaVeza, std::string trivija="");
    Dete(short sifraOsobe, short sifraRoditeljskeVeze, std::string trivija="");
    Dete(const Dete& drugo);
    ~Dete();

    short int Sifra();
    short SifraOsobe();
    short SifraRoditeljskogOdnosa();
    //Osoba* Potomak();
    //Brak* RoditeljskiOdnos();
    std::string& Trivija();
    //  QDate& DatumUsvajanja();

    static void postaviSledecuSifru(int sifra);
    //void PostaviPotomka(Osoba* potomak);
    //void PostaviRoditeljskiOdnos(Brak* odnos);


    //bool BrisanjeOdOsobe(); // destruktor od Osobe je pozvan, pa dete mora obavestiti i brak, jer ce i ono biti uskoro uklonjeno
    //bool RaskiniSveVeze(); // brise podatke o svim vezama, priprema za brisanje na vecoj skali
    bool VecSeBrisem();
    void PreskociRazvezivanje();

    friend QDataStream& operator<<(QDataStream &out,Dete& dete);
    friend QDataStream& operator>>(QDataStream &in,Dete& dete);

private:
    static short int _sledecaSifra;
    short int _sifra, _sifraOsobe, _sifraRoditeljskeVeze;
    //Osoba* _osoba;
    //Brak * _roditeljskiOdnos;
    std::string _trivija;
    //   QDate _datumUsvajanja;
    bool _vecSeBrisem=false;
    bool _preskociRazvezivanje=false;
};

#endif // DETE_H

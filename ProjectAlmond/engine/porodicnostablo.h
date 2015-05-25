#ifndef PORODICNOSTABLO_H
#define PORODICNOSTABLO_H
#include <QObject>
#include <vector>
#include <map>
#include <string>
#include <QDate>
#include "engine/osoba.h"
#include "engine/brak.h"
#include "engine/dete.h"
#include <QString>
#include <QFile>
#include <iostream>

/**
 * @brief The PorodicnoStablo class sluzi za pamcenje podataka o povezanosti clanova stabla, kao i njihovo indeksiranje.
 */
class PorodicnoStablo : public QObject
{
    Q_OBJECT
public:
    PorodicnoStablo();
    PorodicnoStablo(const QString &ime, const QString &prezime, const QString &pol, const QDate &rodjenje, const QDate &smrt, bool krvniSrodnik=true);

    ~PorodicnoStablo();//brise apsolutno sve, tako sto prvo raskine sve veze u strukturama, a onda brise redom koristeci vektore sa pokazivacima

    Osoba * KljucnaOsoba();


    //dodaje novu osobu u stablo,ocekuje se da posle poziva sledi i poziv za dodavanje deteta ili braka, da bi stablo bilo povezano u svakom momentu!!!
    short int DodajOsobu(const QString &ime, const QString &prezime, const QString &pol, const QDate rodjenje, const QDate smrt, bool krvniSrodnik);
    //slicno, samo pravi NN lice
    short int DodajNNLice(bool krvniSrodnik);

    /*
    na ovo sam mislila
    short int DodajBS(short int sifraOsobe, std::string trivija="")
    {
        Osoba* osoba = NadjiOsobuSifrom(sifraOsobe);
        if (osoba->RoditeljskiOdnos() == nullptr)
            {
                ne znam,
                short int sifraBraka = DodajBrak(DodajNNLice(), DodajNNLice());
                DodajDete(sifraOsobe, sifraBraka); -- ova nasa kojoj dodajemo brata, ne ide ovako, ali nebitno
                return DodajDete(sifraBraka); -- onaj novi
            }
        return DodajDete(osoba->RoditeljskiOdnos().Sifra(), trivija);
    }
    Mislim da nije problem da ostavimo opciju brat sestra u GUI-u, nije tesko, a cini mi se da bi bilo zgodno imati
    */

    //dodaje relaciju dete, od braka do osobe
    short int DodajDete(const short sifraBraka, const short sifraOsobe, const QString &trivija="");

    //dodaje relaciju brak izmedju dve osobe date siframa
    short int DodajBrak(const short int sifraNaseOsobe, const short int sifraTudjeOsobe, const QString &trivija="");


    Osoba* NadjiOsobuSifrom(const short sifra);

    Dete* NadjiDeteSifrom(const short sifra);

    Brak* NadjiBrakSifrom(const short sifra);


    void UkloniOsobuSifrom(const short sifra);

    void UkloniBrakSifrom(const short sifra);

    void UkloniDeteSifrom(const short sifra);


    std::vector<short>* KomeJeSveRodjendan(const QDate& datum) const;

    /*ne rade!!!*/
    bool ProcitajFajl(const QString &imeFajla);//citanje fajla
    bool IspisiFajl(const QString &imeFajla);//upisivanje u fajl, tj. cuvanje


private:
    Osoba *_kljucnaOsoba;//osoba cije se porodicno stablo kreira

    //-------------------INDEKSI------------------------//
    std::multimap<QString, Osoba*> _indeksIme;

    //-----OVE STALNO AZURIRAMO------//
    //-----SAMO NJIH PISEMO/CITAMO---//
    std::map<short int, Osoba* > _indeksSifraOsobe;//mapa koja vezuje sifru osobe za tu osobu
    std::map<short int, Brak* > _indeksSifraVeza;//mapa koja vezuje sifru braka za taj brak
    std::map<short int, Dete* > _indeksSifraDete;//mapa koja vezuje sifru deteta za konkretan relacioni objekat dete
    //-----OVE STALNO AZURIRAMO------//
    //-----OVE DOLE NE!!!! zato uvek konsultovati prva tri------//
    //mozda da umesto brisanja iz ovih uvedemo ivalidaciju, tipa promenimo vrednost_sifru na -1... //
    //uvesti periodicno osvezavanje ovih indeksa?...//
    std::multimap<short int, short int> _indeksOsobaBrak;//mapa koja vezuje sifru osobe sa siframa njenih brakova
    std::multimap<short int, short int> _indeksBrakDeca;//mapa koja vezuje sifru braka sa siframa njegove dece(ali osoba!)
    std::multimap<QDate, short> _indeksRodjenje;//mapa koja vezuje datum i sve osobe rodjene tog dana
    std::multimap<int, short> _indeksRodjendan;//mapa vezuje dan [1,366] sa sifrom osobe rodjenom tog dana


    //--------------------INDEKSI------------------------//

    void InicijalizujSveStrukture();
    void SpaliCeloStablo();
    void ObrisiBrakove(short sifra, bool iSupruznike);
    void ObrisiDecu(short sifra);

signals:
    void obrisanaOsoba(short sifra);
    void obrisanaVezaDete(short sifra);
    void obrisanaVezaBrak(short sifra);

};

#endif // PORODICNOSTABLO_H

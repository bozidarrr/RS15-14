#ifndef SUPRUZNIK_H
#define SUPRUZNIK_H 1
class Osoba;
#include"relacija.h"
#include"datum.h"
#include"osoba.h"

/**
 * @brief The Supruznik class obezbedjuje pamcenje podataka o braku ili vezi izmedju dve osobe
 */
class Supruznik:public Relacija
{
public:

    Supruznik(const std::string& datumVencanja="", const std::string& datumUpoznavanja="", const std::string& datumRazvoda="",const std::string &trivija="");
    ~Supruznik();

    //ne znam jos sta da radimo sa copy i operator=, da li da ih uopste implementiramo?
    //U sustini, ove objekte ne bi trebalo da dodeljujemo nikom, radicemo stalno samo sa pokazivacima
    //jedino da kopija zadrzava opisne, ali ne i povezujuce elemente.???

    Datum DatumVencanja() const;
    Datum DatumUpoznavanja() const;
    Datum DatumRazvoda() const;

    bool UVezi() const;
    bool UBraku() const;
    bool Rastavljeni() const;

    const Osoba& Muz() const;
    const Osoba& Zena() const;

    //implementacije jos uvek beskorisnih metoda
    std::string UpisiUString()const override;
    void UcitajIzStringa(const std::string& unos)override;
//------------------------------------------------------------


    /**
     * @brief Ovaj metod, pozvan od strane neke osobe pri njenom uklanjanju, inicira brisanje podatka o vezi iz liste supruznika osobe sa kojom je u ovoj vezi
     */
    void UkloniSe(const Osoba* inicijator)override;


private:

    Datum _datumVencanja;
    Datum _datumUpoznavanja;
    Datum _datumRazvoda;
    Osoba *_muz;
    Osoba *_zena;


};

#endif // SUPRUZNIK_H

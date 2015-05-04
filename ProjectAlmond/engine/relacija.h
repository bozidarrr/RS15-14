#ifndef RELACIJA_H
#define RELACIJA_H 1
class Osoba;
#include<string>

class Relacija
{
public:

    Relacija(const std::string & trivija="");
    virtual ~Relacija();

    bool PoveziSe(Osoba * prva, Osoba * druga);

    /**
     * @brief UkloniSe obavestava drugu osobu u vezi, da ce biti obrisana, te da vezu treba ukloniti iz spiska veza, ali bez dealokacije
     * @param inicijator Osoba koja se trenutno brise sa spiska, tj koja je pozvala ovaj metod
     */
    virtual bool UkloniSe(const Osoba* inicijator)=0;

    short int Sifra()const;

protected:
    static short int _MinSifra;
    short int _sifra;
    Osoba *_prva;
    Osoba *_druga;
    std::string _trivija;
};

#endif // RELACIJA_H

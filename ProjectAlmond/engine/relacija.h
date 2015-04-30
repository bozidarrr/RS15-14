#ifndef RELACIJA_H
#define RELACIJA_H 1
class Osoba;
#include<string>

class Relacija
{
public:
    Relacija(const std::string & trivija="");
    virtual ~Relacija();

    void PoveziSe(Osoba * prva, Osoba * druga);

    /**
     * @brief UkloniSe obavestava drugu osobu u vezi, da ce biti obrisana, te da vezu treba ukloniti iz spiska veza, ali bez dealokacije
     * @param inicijator Osoba koja se trenutno brise sa spiska, tj koja je pozvala ovaj metod
     */
    virtual void UkloniSe(const Osoba* inicijator)=0;

    short int Sifra()const;

protected:
    std::string _trivija;
    Osoba *_prva;
    Osoba *_druga;
    static short int _MinSifra;
    short int _sifra;
};

#endif // RELACIJA_H

#ifndef RELACIJA_H
#define RELACIJA_H 1
#include<string>
#include"engine/osoba.h"
class Relacija
{
public:
    Relacija(const std::string & trivija=""):_trivija(trivija),_prva(nullptr),_druga(nullptr),_sifra(_MinSifra++){}
    virtual ~Relacija(){}

    void PoveziSe(Osoba * prva, Osoba * druga)
    {
        if(prva!=nullptr && druga!=nullptr){
            _prva=prva;
            _druga=druga;
        }
    }

    /**
     * @brief UkloniSe obavestava drugu osobu u vezi, da ce biti obrisana, te da vezu treba ukloniti iz spiska veza, ali bez dealokacije
     * @param inicijator Osoba koja se trenutno brise sa spiska, tj koja je pozvala ovaj metod
     */
    virtual void UkloniSe(const Osoba* inicijator)=0;
protected:
    std::string _trivija;
    Osoba *_prva;
    Osoba *_druga;
    static short int _MinSifra;
    short int _sifra;
};

short int Relacija::_MinSifra=0;

#endif // RELACIJA_H

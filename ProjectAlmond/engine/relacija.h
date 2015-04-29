#ifndef RELACIJA_H
#define RELACIJA_H 1
#include<string>
#include<sys/types.h>
#include"engine/osoba.h"
class Relacija
{
public:
    Relacija(const std::string & trivija=""):_trivija(trivija),_prva(nullptr),_druga(nullptr){}
    virtual ~Relacija(){}

    //za sad nista ne rade pametno, trebace nam za ispis, a mozda i ne, kao neki toString, mozda zatreba posle
    //----------------------------------------------------------------------------------------------
    virtual std::string UpisiUString()const=0;
    virtual void UcitajIzStringa(const std::string& unos)=0;
    //----------------------------------------------------------------------------------------------

    /**
     * @brief UkloniSe obavestava drugu osobu u vezi, da ce biti obrisana, te da vezu treba ukloniti iz spiska veza, ali bez dealokacije
     * @param inicijator Osoba koja se trenutno brise sa spiska, tj koja je pozvala ovaj metod
     */
    virtual void UkloniSe(const Osoba* inicijator)=0;
protected:
    std::string _trivija;
    Osoba *_prva;
    Osoba *_druga;
};

#endif // RELACIJA_H

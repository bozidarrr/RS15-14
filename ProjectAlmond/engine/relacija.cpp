#include"engine/relacija.h"

Relacija::Relacija(const std::string & trivija):_trivija(trivija),_prva(nullptr),_druga(nullptr),_sifra(Relacija::_MinSifra++){}

Relacija::~Relacija(){}

void Relacija::PoveziSe(Osoba * prva, Osoba * druga)
{
    if(prva!=nullptr && druga!=nullptr){
        _prva=prva;
        _druga=druga;
    }
}



short int Relacija::_MinSifra=0;

short int Relacija::Sifra()const{

    return _sifra;
}

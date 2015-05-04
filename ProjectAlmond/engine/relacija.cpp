#include"engine/relacija.h"

Relacija::Relacija(const std::string & trivija):_sifra(Relacija::_MinSifra++),_prva(nullptr),_druga(nullptr),_trivija(trivija){}

Relacija::~Relacija(){}

bool Relacija::PoveziSe(Osoba * prva, Osoba * druga)
{
    if(prva!=nullptr && druga!=nullptr){
        _prva=prva;
        _druga=druga;
        return true;
    }
    return false;
}

short int Relacija::_MinSifra=0;

short int Relacija::Sifra()const{

    return _sifra;
}

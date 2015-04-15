#ifndef RELACIJA_H
#define RELACIJA_H 1
#include<string>
class Relacija
{
public:

    virtual std::string UpisiUFajl(const std::string& imeFajla)const=0;
    virtual std::string UcitajIzFajla()=0;

};

#endif // RELACIJA_H

#include "datum.h"

Datum::Datum()
    :_dan(-1),_mesec(-1),_godina(-1)
{}

/**
    Konstruktor preko stringa.
    Racuna se da se u unosu preko GUI-a vrsi provera formata datuma!
    Ukoliko je uneti string prazan, datum se inicijalizuje vrednoscu koja ukazuje na njegovu "nepoznatost"
    **/
Datum::Datum(const std::string &s)
{
    if(s.empty()){PostaviNepoznat();}
    else{

        if (!KorektanDatum(s))
            throw "Nije korektan datum dat stringom, formiranje datuma neuspesno!";

        /* s = dd.mm.gggg. ili mm.gggg. ili gggg. */
        int dan,mesec,godina;
        if (s.size() == 11)
        {
            dan = atoi( s.substr(0, 2).c_str() );
            mesec = atoi( s.substr(3, 2).c_str() );
            godina = atoi( s.substr(6, 4).c_str() );
        }

        else if (s.size() == 8)
        {
            dan = 0;
            mesec = atoi( s.substr(0, 2).c_str() );
            godina = atoi( s.substr(3, 4).c_str() );
        }

        else    if (s.size() == 5)
        {
            dan = 0;
            mesec = 0;
            godina = atoi( s.substr(0, 4).c_str() );
        }
        else
            throw "Inicjalizacija datuma nije uspela!";
        _dan=dan;
        _mesec=mesec;
        _godina=godina;
    }
}
bool Datum::NepoznatDatum()const
{
    return _dan==-1&&_mesec==-1&&_godina==-1;
}


bool Datum::PrestupnaGodina(int godina)
{
    return (godina % 4 == 0 && godina % 100 != 0)
            || godina % 400 == 0;
}


bool Datum::KorektanDatum(const std::string & s)
{
    int dan, mesec, godina;

    if (s.size() == 11)
    {
        dan = atoi( s.substr(0, 2).c_str() );
        mesec = atoi( s.substr(3, 2).c_str() );
        godina = atoi( s.substr(6, 4).c_str() );
    }

    else if (s.size() == 8)
    {
        dan = 0;
        mesec = atoi( s.substr(0, 2).c_str() );
        godina = atoi( s.substr(3, 4).c_str() );
    }

    else    if (s.size() == 5)
    {
        dan = 0;
        mesec = 0;
        godina = atoi( s.substr(0, 4).c_str() );
    }
    else
        return false;


    if (dan < 0 || mesec < 0 || godina < 0)
        return false;

    switch (mesec)
    {
    case 0:
        return dan == 0;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return dan <= 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return dan <= 30;
    case 2:
        if (PrestupnaGodina(godina))
            return dan <= 29;
        else
            return dan <= 28;
    default:
        return false;
    }


}

bool Datum::Rodjendan(const Datum & danas) const
{
    if (_mesec == 0 || _dan == 0)
        return false;

    if (_mesec == danas._mesec && _dan == danas._dan)
        return true;
    if (_mesec == 2 && _dan == 29
            && !PrestupnaGodina(danas._godina)
            && danas._dan == 1 && danas._mesec == 3)
        return true;
    return false;
}


std::string Datum::toString()const
{
    if (NepoznatDatum())
    {
        return "--.--.----.";

    }

    std::string rezultat="";

    if (_dan > 0)
    {
        if (_dan < 10)
            rezultat.append("0");
        rezultat.append(_dan+"");
    }
    rezultat.append(".");
    if (_mesec > 0)
    {
        if (_mesec < 10)
            rezultat.append("0");
        rezultat.append(_mesec+"");
    }
    rezultat.append(".");
    rezultat.append(_godina+"");
    return rezultat;

}


std::ostream & operator<<(std::ostream & ostr, const Datum & d)
{
    if (d.NepoznatDatum())
    {
        ostr << "-1 -1 -1";
        return ostr;
    }

        ostr << d._dan << ' ' <<d._mesec<<' '<<d._godina<<std::endl;

    return ostr;
}

std::istream & operator>>(std::istream & istr, Datum & d)
{

/*

    if (d.NepoznatDatum())
    {
        d._dan=-1;
        d._mesec=-1;
        d._godina=-1;
        return istr;
    }
    */

      istr >> d._dan >> d._mesec >> d._godina;

    return istr;

}

void Datum::PostaviNepoznat()
{
    _dan=-1;
    _mesec=-1;
    _godina=-1;
}

bool Datum::operator <(const Datum& datum) const
{
    if(this->NepoznatDatum()||datum.NepoznatDatum())
        return false;
    if (_godina < datum._godina)
        return true;
    if (_godina > datum._godina)
        return false;
    if (_mesec < datum._mesec and _mesec!=0 and datum._mesec!=0)
        return true;
    if (_mesec > datum._mesec)
        return false;
    if (_dan < datum._dan and _dan!=0 and datum._dan!=0)
        return true;
    return false;
}

bool Datum::operator >(const Datum& datum) const
{
    return datum < *this;
}

bool Datum::operator ==(const Datum& datum) const
{
    if(this->NepoznatDatum()||datum.NepoznatDatum())
        return false;
    return datum._godina == _godina &&
            datum._mesec == _mesec && _mesec!=0 &&
            datum._dan == _dan && _dan!=0;
}

bool Datum::operator !=(const Datum& datum) const
{
    return !(*this == datum);
}

bool Datum::operator >=(const Datum& datum) const
{
    return !(*this < datum);
}

bool Datum::operator <=(const Datum& datum) const
{
    return !(*this > datum);
}

int Datum::redniBroj()const{
 int broj=_dan;
 if(_mesec>=2)broj+=31;//prosao ceo januar
 if(_mesec>=3)broj+=29;//prosao ceo februar (uvek numerisem kao da je prestupna)
 if(_mesec>=4)broj+=31;//prosao ceo mart
 if(_mesec>=5)broj+=30;//prosao ceo april
 if(_mesec>=6)broj+=31;//prosao ceo maj
 if(_mesec>=7)broj+=30;//prosao ceo jun
 if(_mesec>=8)broj+=31;//prosao ceo jul
 if(_mesec>=9)broj+=31;//prosao ceo avgust
 if(_mesec>=10)broj+=30;//prosao ceo septembar
 if(_mesec>=11)broj+=31;//prosao ceo oktobar
 if(_mesec==12)broj+=30;//prosao ceo novembar

 return broj;

}


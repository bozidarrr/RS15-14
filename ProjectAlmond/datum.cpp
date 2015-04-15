#include <string>
#include <iostream>
#include "datum.h"

using namespace std;



    /**
    Konstruktor preko stringa.
    Racuna se da se u unosu preko GUI-a vrsi provera formata datuma!
    **/
    Datum::Datum(const string &s)
    {
        if (!KorektanDatum(s))
            throw "Nije korektan datum dat stringom, formiranje datuma neuspesno!";

        /* s = dd.mm.gggg. ili mm.gggg. ili gggg. */

        if (s.size() == 11)
        {
            _dan = atoi( s.substr(0, 2).c_str() );
            _mesec = atoi( s.substr(3, 2).c_str() );
            _godina = atoi( s.substr(6, 4).c_str() );
        }

        else if (s.size() == 8)
            {
                _dan = 0;
                _mesec = atoi( s.substr(0, 2).c_str() );
                _godina = atoi( s.substr(3, 4).c_str() );
            }

            else    if (s.size() == 5)
                    {
                        _dan = 0;
                        _mesec = 0;
                        _godina = atoi( s.substr(0, 4).c_str() );
                    }
                    else
                        throw "Inicjalizacija datuma nije uspela!";
    }

    /**
      Ovo mozda trebalo da bude staticki?
    **/
    bool Datum::PrestupnaGodina(int godina)
    {
        return (godina % 4 == 0 && godina % 100 != 0)
                || godina % 400 == 0;
    }


    /**
        A i ovo
    **/
    bool Datum::KorektanDatum(const string & s)
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
                        //greska("Format stringa nije dobar!");
                        return false;


        if (dan < 0 || mesec < 0 || godina < 0)
            return false;

        switch (mesec)
        {
        case 0: return dan == 0;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: return dan <= 31;
        case 4:
        case 6:
        case 9:
        case 11: return dan <= 30;
        case 2: if (PrestupnaGodina(godina))
                    return dan <= 29;
                else
                    return dan <= 28;
        default: return false;
        }


    }

bool Datum::rodjendan(const Datum & danas) const
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


ostream & operator<<(ostream & ostr, const Datum & d)
{
    if (d._dan > 0)
    {
        if (d._dan < 10)
            ostr << 0;
        ostr << d._dan << '.';
    }
    if (d._mesec > 0)
    {
        if (d._mesec < 10)
            ostr << 0;
        ostr << d._mesec << '.';
    }
    ostr << d._godina << '.';
    return ostr;
}


/* testiranje...
int main(int argc, char ** argv)
{
    cout << Datum("11.04.2011.") << endl;
    Datum d = Datum("12.2015.");
    cout << d << endl;
    d = Datum("2013.");
        cout << d << endl;
    d = Datum("01.04.1999.");
    cout << d << endl;

    exit(EXIT_SUCCESS);
}
*/

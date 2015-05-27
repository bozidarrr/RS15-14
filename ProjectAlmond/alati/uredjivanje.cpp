#include "alati/uredjivanje.h"
#include <vector>
#include <algorithm>

uredjivanje::uredjivanje(int sirina)
    :_sirina(sirina)
{

}

uredjivanje::~uredjivanje()
{

}

int uredjivanje::IzracunajUkupnuSirinu(std::vector<int> &m, int maxPoCeliji)
{
    int n = m.size();
    if (n == 0)
        return _sirina;
    int max_po_nivou = 0;
    auto it = max_element(std::begin(m), std::end(m)); // c++11
    max_po_nivou = *it;
    _ukupnaSirina = max_po_nivou * maxPoCeliji * _sirina;
    return _ukupnaSirina;
}
//jedna celija sluzi da se u nju smeste osoba i njeni supruznici
std::vector<int> *uredjivanje::IzracunajSirinuCelije(std::vector<int> &m, int maxPoCeliji)
{
    std::vector<int> *sirine = new std::vector<int>();
    int w = IzracunajUkupnuSirinu(m, maxPoCeliji);

    for (short i : m)
    {
        sirine->push_back(w / i);//najsira potrebna duzina / broj osoba u nivou
    }
    return sirine;
}

int uredjivanje::Sirina()
{
    return _ukupnaSirina;
}


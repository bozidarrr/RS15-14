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

int uredjivanje::IzracunajUkupnuSirinu(const std::vector<int> &m, const int maxPoCeliji) const
{
    int n = m.size();
    if (n == 0)
        return _sirina;
    int max_po_nivou = 0;
//    for (short i : m)
//    {
//        if (i > max_po_nivou)
//            max_po_nivou = i;//koliko najvise osoba imamo u jednoj generaciji
//    }

    auto it = max_element(std::begin(m), std::end(m)); // c++11
    max_po_nivou = *it;
    return max_po_nivou * maxPoCeliji * _sirina;

}
//jedna celija sluzi da se u nju smeste osoba i njeni supruznici
std::vector<int> *uredjivanje::IzracunajSirinuCelije(const std::vector<int> &m, const int maxPoCeliji) const
{
    std::vector<int> *sirine = new std::vector<int>();
    int w = IzracunajUkupnuSirinu(m, maxPoCeliji);

    for (short i : m)
    {
        sirine->push_back(w / i);//najsira potrebna duzina / broj osoba u nivou
    }
    return sirine;
}


#ifndef UREDJIVANJE_H
#define UREDJIVANJE_H
#include <vector>


class uredjivanje
{
public:
    uredjivanje(int sirina = 120);
    ~uredjivanje();

    std::vector<int> * IzracunajSirinuCelije(const std::vector<int> &m, const int maxPoCeliji) const;


private:
    int _sirina;//neka osnovna sirina za jednu osobu

    //za dat vektor iz engina,
    //koji ima broj krvih srodnika po nivou, racuna sirinu potrebnu da se lepo smeste
    int IzracunajUkupnuSirinu(const std::vector<int> &m, const int maxPoCeliji) const;
};
#endif // UREDJIVANJE_H

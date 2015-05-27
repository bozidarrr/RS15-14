#ifndef UREDJIVANJE_H
#define UREDJIVANJE_H
#include <vector>


class uredjivanje
{
public:
    uredjivanje(int sirina = 170);//ako je osoba sirine 100, damo joj jos 70
    ~uredjivanje();

    std::vector<int> * IzracunajSirinuCelije(std::vector<int> &m, int maxPoCeliji);

    int Sirina();


private:
    int _sirina;//neka osnovna sirina za jednu osobu

    //za dat vektor iz engina,
    //koji ima broj krvih srodnika po nivou, racuna sirinu potrebnu da se lepo smeste
    int IzracunajUkupnuSirinu(std::vector<int> &m, int maxPoCeliji);

    int _ukupnaSirina;
};
#endif // UREDJIVANJE_H

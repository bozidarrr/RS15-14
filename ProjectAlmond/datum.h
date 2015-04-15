#ifndef DATUM
#define DATUM 1

#include <string>
#include <iostream>
#include <regex>
#include <cstdlib>

using namespace std;




/**
 * @brief The Datum class
 * Klasa koja ce omoguciti formatiran prikaz datuma
 * kao i mogucnost da dan ili dan i mesec budu nepoznati
 */
class Datum
{
  public:
    /**
    Konstruktor preko stringa.
    Racuna se da se u unosu preko GUI-a vrsi provera formata datuma!
    **/
    Datum(const string & s);

    /**
     * @brief Datum
     * @param dan
     * @param mesec
     * @param godina
     */

    Datum(int dan, int mesec, int godina)
        : _dan(dan), _mesec(mesec), _godina(godina)
    {}

    /**
     * @brief Datum
     * @param d
     */
    Datum(const Datum & d)
        : _dan(d._dan), _mesec(d._mesec), _godina(d._godina)
    {}

    /**
     * @brief KorektanDatum
     * @param s string koji predstavlja datum
     * @return true ako je dat datum u dobrom obliku
     */
    static bool KorektanDatum(const string & s);

    /**
     * @brief rodjendan
     * @param danas
     * @return true ako se poklapaju dan i mesec
     */
    bool rodjendan(const Datum & danas) const;

    /**
     * @brief PrestupnaGodina
     * @param godina
     * @return true ako je godina prestupna
     */
    static bool PrestupnaGodina(int godina);

  private:
    /* mozda i da se napravi toString umesto ovoga */
    friend ostream & operator<<(ostream & ostr, const Datum & d);


    int _dan;
    int _mesec;
    int _godina;

};

#endif // DATUM_H


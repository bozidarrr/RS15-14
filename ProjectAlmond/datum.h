#ifndef DATUM
#define DATUM 1

#include <string>
#include <iostream>
#include <iomanip>

/**
 * @brief The Datum class
 * Klasa koja ce omoguciti formatiran prikaz datuma
 * kao i mogucnost da dan ili dan i mesec budu nepoznati
 */
class Datum
{
  public:

    /**
     * Prazan konstruktor koji postavlja negativan dan, mesec i godinu, onda kada je podatak o datumu zapravo nepoznat
     * @brief Datum
     */
    Datum();

    /**
    Konstruktor preko stringa.
    Racuna se da se u unosu preko GUI-a vrsi provera formata datuma!
    **/
    Datum(const std::string & s);

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
     * @brief NepoznatDatum
     * @return true ako je vrednost datuma nepoznata, ili false, ako je korektna (posto inace dozvoljavamo samo ili korektan unos, ili nepoznate vrednosti)
     */
    bool NepoznatDatum() const;

    /**
     * @brief KorektanDatum
     * @param s string koji predstavlja datum
     * @return true ako je dat datum u dobrom obliku
     */
    static bool KorektanDatum(const std::string & s);

    /**
     * @brief rodjendan
     * @param danas
     * @return true ako se poklapaju dan i mesec
     */
    bool Rodjendan(const Datum & danas) const;

    /**
     * @brief PrestupnaGodina
     * @param godina
     * @return true ako je godina prestupna
     */
    static bool PrestupnaGodina(int godina);

    bool operator >(const Datum& d) const;
    bool operator <(const Datum& d) const;
    bool operator >=(const Datum& d) const;
    bool operator <=(const Datum& d) const;
    bool operator ==(const Datum& d) const;
    bool operator !=(const Datum& d) const;




  private:
    /* mozda i da se napravi toString umesto ovoga */
    friend std::ostream & operator<<(std::ostream & ostr, const Datum & d);

    void PostaviNepoznat();

    int _dan;
    int _mesec;
    int _godina;

};

#endif // DATUM_H


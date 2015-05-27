#ifndef DETE_H
#define DETE_H
#include <QString>
#include <QDate>

class Dete
{
public:
    Dete();
    Dete(const short sifraOsobe, const short sifraRoditeljskeVeze, const QString &trivija="");
    Dete(const Dete& drugo);
    ~Dete();

    short int Sifra();
    short SifraOsobe();
    short SifraRoditeljskogOdnosa();
    const QString& Trivija() const;
    //  QDate& DatumUsvajanja();

    static void postaviSledecuSifru(int sifra);
    bool VecSeBrisem();
    void PreskociRazvezivanje();

    friend QDataStream& operator<<(QDataStream &out,Dete& dete);
    friend QDataStream& operator>>(QDataStream &in,Dete& dete);

private:
    static short int _sledecaSifra;
    short int _sifra, _sifraOsobe, _sifraRoditeljskeVeze;
    QString _trivija;
    //   QDate _datumUsvajanja;
    bool _vecSeBrisem=false;
    bool _preskociRazvezivanje=false;
};

#endif // DETE_H

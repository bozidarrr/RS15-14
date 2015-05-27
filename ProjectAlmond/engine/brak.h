#ifndef BRAK_H
#define BRAK_H

#include<vector>
#include<QString>
#include<QDate>

class Brak
{
public:
    Brak();
    Brak(const short sifraNase, const short sifraTudje, const QString &trivija);
    Brak(const Brak& drugi);
    ~Brak();

    //----geteri i seteri------//
    short int Sifra();
    short SifraNase();
    short SifraTudje();
    const QString& Trivija() const;/*
    QDate& DatumUpoznavanja();
    QDate& DatumVeze();
    QDate& DatumRaskida();
    QDate& DatumVeridbe();
    QDate& DatumVencanja();
*/
    //----geteri i seteri------//
    static void postaviSledecuSifru(int sifra);

    //---metodi korisni u upotrebi---//

    //OVI JOS NE RADE!!!!
    bool UVezi();
    bool Vereni();
    bool Vencani();
    bool Rastavljeni();
    //---metodi korisni u upotrebi---//

    //----metodi potrebni za brisanje----//
    bool VecSeBrisem();
    void PreskociRazvezivanje();
    //----metodi potrebni za brisanje----//

    //----metodi potrebni za citanje i pisanje----//
    friend QDataStream& operator<<(QDataStream &out,Brak& brak);
    friend QDataStream& operator>>(QDataStream &in,Brak& brak);
    //----metodi potrebni za citanje i pisanje----//

    short Nivo() const;
    void Nivo(short nivo);

private:
    static short int _sledecaSifra;
    short int _sifra;
    short _sifraNase;
    short _sifraTudje;
    QString _trivija;
    /* QDate _datumUpoznavanja;
    QDate _datumVeze;
    QDate _datumVeridbe;
    QDate _datumVencanja;
    QDate _datumRaskida;*/
    bool _vecSeBrisem=false;
    bool _preskociRazvezivanje=false;

    short _nivo = -1;
};

#endif // BRAK_H

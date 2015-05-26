#include "porodicnostablo.h"
#include <QDataStream>
#include <iostream>
#include "alati/trazenjeputa.h"

PorodicnoStablo::PorodicnoStablo()
{
    _kljucnaOsoba = new Osoba();
    InicijalizujSveStrukture();
    (_indeksSifraOsobe[_kljucnaOsoba->Sifra()])=_kljucnaOsoba;
}

PorodicnoStablo::PorodicnoStablo(const QString &ime, const QString &prezime, const QString &pol,
                                 const QDate &rodjenje, const QDate &smrt, bool krvniSrodnik)
{
    _kljucnaOsoba = new Osoba(ime, prezime, pol.at(0), rodjenje, smrt, krvniSrodnik);
    _kljucnaOsoba->Nivo(0);
    _nivoi.push_back(1);
    InicijalizujSveStrukture();
    _indeksIme.insert(std::make_pair(ime,_kljucnaOsoba));
    if (rodjenje.isValid())
    {
        //_indeksRodjenje.insert(std::make_pair(rodjenje, _kljucnaOsoba->Sifra()));//ubacuje pri pravljenju osobe
        _indeksRodjendan.insert(std::make_pair(rodjenje.dayOfYear(), _kljucnaOsoba->Sifra()));//ne azurira pri promeni kasnijoj!
    }
    _indeksSifraOsobe[_kljucnaOsoba->Sifra()]=_kljucnaOsoba;
}

PorodicnoStablo::~PorodicnoStablo()
{
    if (_kljucnaOsoba != nullptr)
        UkloniOsobuSifrom(_kljucnaOsoba->Sifra());
    InicijalizujSveStrukture();
    //SpaliCeloStablo();
}

Osoba * PorodicnoStablo::KljucnaOsoba()
{
    return _kljucnaOsoba;
}


//dodaje novu osobu u stablo,ocekuje se da posle poziva sledi i poziv za dodavanje deteta ili braka, da bi stablo bilo povezano u svakom momentu!!!
short int PorodicnoStablo::DodajNNLice(bool krvniSrodnik)
{
    Osoba *nova=new Osoba(krvniSrodnik);
    _indeksSifraOsobe[nova->Sifra()]=nova;
    return nova->Sifra();
}
short int PorodicnoStablo::DodajOsobu(const QString &ime, const QString &prezime, const QString &pol,
                                      const QDate rodjenje, const QDate smrt, bool krvniSrodnik)
{
    QChar p = pol.at(0);
    Osoba* nova=new Osoba(ime, prezime, p, rodjenje, smrt, krvniSrodnik);
    _indeksIme.insert(std::make_pair(ime, nova));
    if (rodjenje.isValid())
    {
        //_indeksRodjenje.insert(std::make_pair(rodjenje, nova->Sifra()));//ubacuje pri pravljenju osobe
        _indeksRodjendan.insert(std::make_pair(rodjenje.dayOfYear(), nova->Sifra()));//ne azurira pri promeni kasnijoj!
    }
    _indeksSifraOsobe[nova->Sifra()]=nova;
    return nova->Sifra();
}



//dodaje relaciju dete, od braka do osobe
short int PorodicnoStablo::DodajDete(const short int sifraBraka, const short int sifraOsobe, const QString &trivija)
{
    //osoba je dete iz ovog braka, vec kreirana sa vrednoscu -1 za sifru roditeljskog odnosa, pa joj to postavljamo
    _indeksSifraOsobe[sifraOsobe]->PostaviRoditeljskuSifru(sifraBraka);
    //ili si hteo da dodjes do relacije "dete"?
    //osobi, tj detetu dodeljujemo nivo_roditelja + 1
    short noviNivo = _indeksSifraVeza[sifraBraka]->Nivo()+1;
    _indeksSifraOsobe[sifraOsobe]->Nivo(noviNivo);
    //i ubacujemo u brojac
    if (_nivoi.size() <= noviNivo)
        _nivoi.push_back(1);
    else
        _nivoi[noviNivo]++;
    Dete* novo=new Dete(sifraOsobe, sifraBraka, trivija);
    _indeksSifraDete[novo->Sifra()]=novo;
    _indeksBrakDeca.insert(std::make_pair(sifraBraka, sifraOsobe));
    return novo->Sifra();
}

//dodaje relaciju brak izmedju dve osobe date siframa
short int PorodicnoStablo::DodajBrak(const short sifraNaseOsobe, const short sifraTudjeOsobe, const QString &trivija)
{
    Brak *novi = new Brak(sifraNaseOsobe, sifraTudjeOsobe, trivija);
    novi->Nivo(_indeksSifraOsobe[sifraNaseOsobe]->Nivo());//treba nam zbog racunanja nivo deteta
    _indeksSifraVeza[novi->Sifra()]=novi;
    _indeksOsobaBrak.insert(std::make_pair(sifraNaseOsobe, novi->Sifra()));
    _indeksOsobaBrak.insert(std::make_pair(sifraTudjeOsobe, novi->Sifra()));
    return novi->Sifra();
}


Osoba* PorodicnoStablo::NadjiOsobuSifrom(const short sifra)
{
    if(_indeksSifraOsobe.find(sifra)!=_indeksSifraOsobe.end())
        return _indeksSifraOsobe[sifra];
    return nullptr;
}

Dete* PorodicnoStablo::NadjiDeteSifrom(const short sifra)
{
    if(_indeksSifraDete.find(sifra)!=_indeksSifraDete.end())
        return _indeksSifraDete[sifra];
    return nullptr;
}

Brak* PorodicnoStablo::NadjiBrakSifrom(const short sifra)
{
    if(_indeksSifraVeza.find(sifra)!=_indeksSifraVeza.end())
        return _indeksSifraVeza[sifra];
    return nullptr;
}


void PorodicnoStablo::UkloniOsobuSifrom(const short sifra)
{
    /**
        mislim da je dovoljno da PorodicnoStablo brine o tome
        da raskine veze i obrise sve osobe koje treba
        a ne da to rade osobe, relacije...
    **/
    std::map<short, Osoba*>::iterator iter;
    if ((iter = _indeksSifraOsobe.find(sifra)) == _indeksSifraOsobe.end())
    {
        std::cout<<"vec je obrisana"<<std::endl;
        return;
    }
    Osoba *zaBrisanje=_indeksSifraOsobe[sifra];

    if (zaBrisanje->JeKrvniSrodnik())
    {//brisemo njene supruznike
        ObrisiBrakove(sifra, true);
        //i smanjujemo broj ljudi u njenom nivou
        _nivoi[zaBrisanje->Nivo()]--;
        if (_nivoi[zaBrisanje->Nivo()] == 0)
            _nivoi.pop_back();//ako je ovaj nula, moraju i svi posle biti nula
    }
    //to ce obrisati i decu, jer supruznik nece biti krvni srodnik pa ce uci u else granu
    else
    {
        ObrisiDecu(sifra);
        ObrisiBrakove(sifra, false);
    }

    //brise sebe kao dete
    std::map<short, Dete*>::iterator dete_b = _indeksSifraDete.begin();
    std::map<short, Dete*>::iterator dete_e = _indeksSifraDete.end();
    for(; dete_b != dete_e ; dete_b++)
    {
        if (dete_b->second->SifraOsobe() != sifra)
            continue;
        emit obrisanaVezaDete(dete_b->first);
        delete _indeksSifraDete[dete_b->first];
        _indeksSifraDete.erase(dete_b);
    }
    //brisemo je iz indeksa (sifra, osoba)
    _indeksSifraOsobe.erase(iter);
    //mozda bi trebalo i iz ostalih indeksa
    //auto nesto =  _indeksSifraVeza.equal_range(sifra);
    //_indeksSifraVeza.erase(nesto.first, nesto.second);

    emit obrisanaOsoba(sifra);

    if (!zaBrisanje->VecSeBrisem())
        delete zaBrisanje;
}

//ovo sada azurira indekse
void PorodicnoStablo::UkloniBrakSifrom(const short sifra)
{
    if (_indeksSifraVeza.find(sifra) == _indeksSifraVeza.end())
        return;
//brise brak iz indeksa za nasu osobu (pozvan je ako se brise tudja osoba)
    Brak *brak = _indeksSifraVeza[sifra];
    auto brakovi = _indeksOsobaBrak.equal_range(brak->SifraNase());
    for (auto iter = brakovi.first; iter != brakovi.second; iter++)
    {
        if (iter->second == sifra)
            _indeksOsobaBrak.erase(iter);
    }
}

void PorodicnoStablo::UkloniDeteSifrom(const short sifra)
{
    delete NadjiDeteSifrom(sifra);
}

bool PorodicnoStablo::osobaImaBrakove(const short sifra) const
{
    if (_indeksSifraOsobe.find(sifra) == _indeksSifraOsobe.end())
        return false;
    return _indeksOsobaBrak.count(sifra) > 0;
}

bool PorodicnoStablo::ProcitajFajl(const QString &imeFajla)
{
    std::cout << "Citam fajl" << imeFajla.toStdString() << std::endl;
    //otvaramo fajl
    QFile fajl(imeFajla);
    if (!fajl.open(QIODevice::ReadOnly)) {
        std::cout << "Ne moze da iscita fajl" << std::endl; //bice warning
        return false;
    }

    //otvaramo ulazni stream
    QDataStream ulaz(&fajl);

    ulaz.setVersion(QDataStream::Qt_4_1);// DA LI OVAJ, ILI NEKI DRUGI?? iskreno pojma nemam u kojem radimo mi zapravo

    SpaliCeloStablo();

    int maxSifraOsobe=-1;
    int maxSifraBraka=-1;
    int maxSifraDeteta=-1;
    //===========================

    _kljucnaOsoba = new Osoba();
    ulaz >>*_kljucnaOsoba;
    //std::cout<<"Procitala kljucnu\n";
    _indeksSifraOsobe[_kljucnaOsoba->Sifra()] = _kljucnaOsoba;
    _indeksIme.insert(std::make_pair(_kljucnaOsoba->Ime(), _kljucnaOsoba));
    QDate datum = _kljucnaOsoba->DatumRodjenja();
    if (datum.isValid())
    {
        _indeksRodjendan.insert(std::make_pair(datum.dayOfYear(), _kljucnaOsoba->Sifra()));
        //_indeksRodjenje.insert(std::make_pair(datum, _kljucnaOsoba->Sifra()));
    }
    if (_kljucnaOsoba->Sifra() > maxSifraOsobe)
        maxSifraOsobe = _kljucnaOsoba->Sifra();
    //----------------------UCITAVANJE SVIH PODATAKA O OSOBAMA, BEZ VEZIVANJA---------------------------//

    qint32 velicina;
    ulaz>>velicina;
    //std::cout<<"procitala broj osoba"<<(short)velicina <<std::endl;

    for (int i=0;i<(short)velicina;i++){
        Osoba *o=new Osoba();
        ulaz>>*o;
        _indeksSifraOsobe[o->Sifra()]=o;
        _indeksIme.insert(std::make_pair(o->Ime(), o));
        QDate datum = o->DatumRodjenja();
        if (datum.isValid())
        {
            _indeksRodjendan.insert(std::make_pair(datum.dayOfYear(), o->Sifra()));
            //_indeksRodjenje.insert(std::make_pair(datum, o->Sifra()));
        }
        if (o->Sifra() > maxSifraOsobe)
            maxSifraOsobe = o->Sifra();
        //std::cout<<"Procitala osobu" << o->Ime().toStdString() << std::endl;

    }
    //----------------------UCITAVANJE SVIH PODATAKA O OSOBAMA, BEZ VEZIVANJA---------------------------//

    //----------------------UCITAVANJE SVIH PODATAKA O BRAKOVIMA, BEZ VEZIVANJA---------------------------//
    ulaz>>velicina;
    //std::cout<<"procitala broj veza\n"<<(short)velicina;
    for (int i=0;i<(short)velicina;i++){
        Brak *b=new Brak();
        ulaz>>*b;
        _indeksSifraVeza[b->Sifra()]=b;
        //std::cout<<"Procitala vezu\n";
        _indeksOsobaBrak.insert(std::make_pair(b->SifraNase(), b->Sifra()));
        _indeksOsobaBrak.insert(std::make_pair(b->SifraTudje(), b->Sifra()));
        if (b->Sifra() > maxSifraBraka)
            maxSifraBraka = b->Sifra();
    }
    //----------------------UCITAVANJE SVIH PODATAKA O BRAKOVIMA, BEZ VEZIVANJA---------------------------//

    //----------------------UCITAVANJE SVIH PODATAKA O DECI, BEZ VEZIVANJA---------------------------//
    ulaz>>velicina;
    //std::cout<<"procitala broj dece\n"<<(short)velicina;
    for (int i=0;i<(short)velicina;i++){
        Dete *d=new Dete();
        ulaz>>*d;
        _indeksSifraDete[d->Sifra()]=d;
        _indeksBrakDeca.insert(std::make_pair(d->SifraRoditeljskogOdnosa(), d->SifraOsobe()));
         //std::cout<<"Procitala dete\n";
        if (d->Sifra() > maxSifraDeteta)
            maxSifraDeteta = d->Sifra();
    }
    //----------------------UCITAVANJE SVIH PODATAKA O DECI, BEZ VEZIVANJA---------------------------//


    //----------------------POSTAVLJANJE STATICKOG PODATKA ZA DODELU SLEDECE SIFRE NA OSNOVU MAKSIMUMA UCITANIH------------------------//
    Osoba::postaviSledecuSifru(maxSifraOsobe+1);
    Brak::postaviSledecuSifru(maxSifraBraka+1);
    Dete::postaviSledecuSifru(maxSifraDeteta+1);
    //----------------------POSTAVLJANJE STATICKOG PODATKA ZA DODELU SLEDECE SIFRE NA OSNOVU MAKSIMUMA UCITANIH------------------------//

    //-----------------------------POVEZIVANJE OSOBA-----------------------------------//


    //-----------------------------POVEZIVANJE OSOBA-----------------------------------//


    //-----------------------------POVEZIVANJE BRAKOVA-----------------------------------//

    //-----------------------------POVEZIVANJE BRAKOVA-----------------------------------//

    //-----------------------------POVEZIVANJE DECE-----------------------------------//

    //-----------------------------POVEZIVANJE DECE-----------------------------------//

    std::cout<<"Uspesno Procitano"<<std::endl;
    fajl.close();
    return true;
}



bool PorodicnoStablo::IspisiFajl(const QString &imeFajla)//cuvam samo podatke koji su mi potrebni, da bi fajlovi bili manji
{//time gubim na performansama pri ucitavanju, ali posto je cuvanje bitnije od ucitavanja (koje radimo prilicno retko), deluje mi bolje ovako

    std::cout << "Pisem u fajl"<<std::endl;
    QFile fajl(imeFajla);
    if (!fajl.open(QIODevice::WriteOnly)) {
        std::cout << "Ne moze da upise u fajl" << std::endl; //bice warning
        return false;
    }
    QDataStream izlaz(&fajl);
    izlaz.setVersion(QDataStream::Qt_4_1);// DA LI OVAJ, ILI NEKI DRUGI?? iskreno pojma nemam u kojem radimo mi zapravo

    izlaz <<* _kljucnaOsoba;
    std::cout<<"ispisala kjucnu\n";

    //std::cout << "imam osoba " << _indeksSifraOsobe.size() << std::endl;
    //Kljucnu smo vec upisali
    izlaz << (qint32)(_indeksSifraOsobe.size()-1);
   // std::cout<<"ispisala velicinu vektora osoba\n"<<_indeksSifraOsobe.size();

    for(auto osoba :_indeksSifraOsobe)
    {
        if ((osoba.second)->Sifra() != _kljucnaOsoba->Sifra())
            izlaz<<(*(osoba.second));
     //   std::cout<<"ispisala osobu\n";
    }

    izlaz << (qint32)_indeksSifraVeza.size();
    //std::cout<<"ispisala velicinu vektora brak\n"<<_indeksSifraVeza.size();

    for(auto brak :_indeksSifraVeza)
    {
        izlaz<<(*brak.second);
      //  std::cout<<"ispisala vezu\n";

    }

    izlaz << (qint32)_indeksSifraDete.size();

     //std::cout<<"ispisala velicinu vektora Dete\n"<<_indeksSifraDete.size();
    for(auto dete :_indeksSifraDete)
    {
        izlaz<<(*dete.second);
       //  std::cout<<"ispisala decu\n";
    }
      fajl.close();
    std::cout<<"Uspesno ispisano" << std::endl;
    return true;
}

void PorodicnoStablo::InicijalizujSveStrukture()
{
    _indeksIme.clear();
    _indeksSifraDete.clear();
    _indeksSifraOsobe.clear();
    _indeksSifraVeza.clear();
    _indeksBrakDeca.clear();
    _indeksOsobaBrak.clear();
    _indeksRodjendan.clear();
    //_indeksRodjenje.clear();
    _nivoi.clear();
}

void PorodicnoStablo::SpaliCeloStablo()
{
    if (_kljucnaOsoba != nullptr)
        UkloniOsobuSifrom(_kljucnaOsoba->Sifra());
    InicijalizujSveStrukture();
}

void PorodicnoStablo::ObrisiBrakove(short sifra, bool iSupruznike)//brise brakove osobe sa tom sifrom
{
    //ako je true, pozivamo brisanje samog supruznika (koji ce posle obrisati brak)
    //ako je false brisemo samo relaciju brak
    //vrv moze bolje


    if (iSupruznike)
    {
        std::pair <std::multimap<short, short>::iterator, std::multimap<short,short>::iterator> brakovi;
        brakovi = _indeksOsobaBrak.equal_range(sifra);
        std::multimap<short, short>::iterator iter;
        for (iter = brakovi.first; iter != brakovi.second; iter++)
        {
            if (_indeksSifraVeza.find(iter->second) == _indeksSifraVeza.end())
                continue;
            //brisemo samo drugu osobu, ne i veze ovde
            UkloniOsobuSifrom(_indeksSifraVeza[iter->second]->SifraTudje());
        }
    }
    else
    {
        std::pair <std::multimap<short, short>::iterator, std::multimap<short,short>::iterator> brakovi;
        brakovi = _indeksOsobaBrak.equal_range(sifra);
        std::multimap<short, short>::iterator iter;
        for (iter = brakovi.first; iter != brakovi.second; iter++)
        {
            //brisemo brak iz indeksa (sifra, brak) i sam objekat
            short sifraBraka = iter->second;
            if (_indeksSifraVeza.find(sifraBraka) != _indeksSifraVeza.end())
            {
                //UkloniBrakSifrom(sifraBraka);//uklanjamo brak iz indeksa za onu drugu osobu
                delete _indeksSifraVeza[sifraBraka];
                _indeksSifraVeza.erase(sifraBraka);
            }
            emit obrisanaVezaBrak(sifraBraka);
        }
    }
}

void PorodicnoStablo::ObrisiDecu(short sifra)
{
    //samo poziva ukloniOsobu za svako dete, to ce ukloniti i relaciju

    std::pair <std::multimap<short, short>::iterator, std::multimap<short,short>::iterator> brakovi;
    brakovi = _indeksOsobaBrak.equal_range(sifra);//nadjemo brakove osobe koja brise svoju decu
    std::multimap<short, short>::iterator iter;
    for (iter = brakovi.first; iter != brakovi.second; iter++)
    {
        //brisemo brak iz indeksa (sifra, brak) i sam objekat
        short sifraBraka = iter->second;
        if (_indeksSifraVeza.find(sifraBraka) == _indeksSifraVeza.end() )
            continue;
        //ako nije vec obrisan, onda mozda ima neke dece
        std::pair <std::multimap<short, short>::iterator, std::multimap<short,short>::iterator> deca;
        deca = _indeksBrakDeca.equal_range(sifraBraka);//nadjemo sifre dece
        std::multimap<short, short>::iterator iterDeca;
        for (iterDeca = deca.first; iterDeca != deca.second; iterDeca++)
            UkloniOsobuSifrom(iterDeca->second);
    }
}

void PorodicnoStablo::azurirajIndeksRodj(const QDate &stari, const QDate &novi, const short sifra)
{
    //na promeni osobe iz GUI-ja dobijamo signal
    auto dani = _indeksRodjendan.equal_range(stari.dayOfYear());
    auto iter = dani.first;
    for (; iter != dani.second; iter++)
    {
        if (iter->second == sifra)
        {
            _indeksRodjendan.erase(iter);
            _indeksRodjendan.emplace(novi.dayOfYear(), sifra);
            _indeksSifraOsobe[sifra]->PromeniDatumRodjenja(novi);
            break;
        }
    }
}

std::vector<short> *PorodicnoStablo::KomeJeSveRodjendan(const QDate &datum)
{// std::multimap<int, short> _indeksRodjendan;
    std::vector<short> *slavljenici = new std::vector<short>();
    auto sl = _indeksRodjendan.equal_range(datum.dayOfYear());
    auto iter = sl.first;
    for(; iter != sl.second; iter++)
    {
        //proveravam da li osoba postoji
        if (_indeksSifraOsobe.find(iter->second) != _indeksSifraOsobe.end())
                slavljenici->push_back(iter->second);
        else
            //ako je osoba izbrisana u medjuvremenu moze se izbrisati i iz indeksa
            _indeksRodjendan.erase(iter);
    }
    return slavljenici;
}

std::vector<int> PorodicnoStablo::kodiranPutOdOsobeDoOsobe(int sifraPocetne,int sifraTrazene)
{
    TrazenjePuta pretraga(this);
    std::vector<int> Kod(pretraga(sifraPocetne,sifraTrazene));


    return Kod;
}


std::map<short, Osoba*> PorodicnoStablo::Osobe()
{
    return _indeksSifraOsobe;
}
std::map<short, Brak*> PorodicnoStablo::Brakovi()
{
    return _indeksSifraVeza;
}
std::map<short, Dete*> PorodicnoStablo::Deca()
{
    return _indeksSifraDete;
}

const std::multimap<short, short> PorodicnoStablo::OsobaBrak()const
{
    return _indeksOsobaBrak;
}

const std::multimap<short, short> PorodicnoStablo::BrakDeca() const
{
    return _indeksBrakDeca;
}
//std::vector<int> PorodicnoStablo::Nivoi()
//{
//}


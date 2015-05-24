#include "porodicnostablo.h"
#include <QDataStream>
#include <iostream>


PorodicnoStablo::PorodicnoStablo()
{
    _kljucnaOsoba = new Osoba();
    InicijalizujSveStrukture();
    (_indeksSifraOsobe[_kljucnaOsoba->Sifra()])=_kljucnaOsoba;
}

PorodicnoStablo::PorodicnoStablo(const QString &ime, const QString &prezime, const QString &pol,  bool krvniSrodnik)
{
    _kljucnaOsoba = new Osoba(ime, prezime, pol.at(0), QDate::currentDate(), QDate::currentDate(), krvniSrodnik);
    InicijalizujSveStrukture();
    //_indeksIme[_kljucnaOsoba->Ime()]=std::vector<Osoba*>();
    //_indeksIme[_kljucnaOsoba->Ime()].push_back(_kljucnaOsoba);
    /*  _indeksRodjenje[_kljucnaOsoba.DatumRodjenja()]=std::vector<Osoba*>();
    _indeksRodjenje[_kljucnaOsoba.DatumRodjenja()].push_back(&_kljucnaOsoba);
    _indeksRodjendan[_kljucnaOsoba.DatumRodjenja().daysInYear()]=std::vector<Osoba*>();
    _indeksRodjendan[_kljucnaOsoba.DatumRodjenja().daysInYear()].push_back(&_kljucnaOsoba);*/
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
short int PorodicnoStablo::DodajOsobu(const QString &ime, const QString &prezime, const QString &pol, bool krvniSrodnik)
{
    QChar p = pol.at(0);
    Osoba* nova=new Osoba(ime, prezime, p, QDate::currentDate(), QDate::currentDate(), krvniSrodnik);
    ///_indeksIme[ime]=std::vector<Osoba*>();
   // _indeksIme[ime].push_back(nova);
    /*    _indeksRodjenje[datumRodjenja]=std::vector<Osoba*>();
    _indeksRodjenje[datumRodjenja].push_back(nova);
    _indeksRodjendan[datumRodjenja.daysInYear()]=std::vector<Osoba*>();
    _indeksRodjendan[datumRodjenja.daysInYear()].push_back(nova);*/
    _indeksSifraOsobe[nova->Sifra()]=nova;
    return nova->Sifra();
}



//dodaje relaciju dete, od braka do osobe
short int PorodicnoStablo::DodajDete(short int sifraBraka,short int sifraOsobe,std::string trivija)
{
    Dete* novo=new Dete(sifraOsobe, sifraBraka, trivija);
    _indeksSifraDete[novo->Sifra()]=novo;
    _indeksBrakDeca.insert(std::make_pair(sifraBraka, sifraOsobe));
    return novo->Sifra();
}

//dodaje relaciju brak izmedju dve osobe date siframa
short int PorodicnoStablo::DodajBrak(short int sifraNaseOsobe, short int sifraTudjeOsobe, std::string trivija)
{
    Brak *novi = new Brak(sifraNaseOsobe, sifraTudjeOsobe, trivija);
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
        //brisemo njene supruznike
        ObrisiBrakove(sifra, true);
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

    emit obrisanaOsoba(sifra);

    if (!zaBrisanje->VecSeBrisem())
        delete zaBrisanje;
}

void PorodicnoStablo::UkloniBrakSifrom(const short sifra)
{
    std::map<short, Brak*>::iterator iter = _indeksSifraVeza.find(sifra);
    if (iter == _indeksSifraVeza.end())
        return;

    emit obrisanaVezaBrak(sifra);
}

void PorodicnoStablo::UkloniDeteSifrom(const short sifra)
{
    delete NadjiDeteSifrom(sifra);
}

//bool PorodicnoStablo::ProcitajFajl(const QString &imeFajla)
//{
//    return true;
//}
//bool PorodicnoStablo::IspisiFajl(const QString &imeFajla)
//{
//    return true;
//}


bool PorodicnoStablo::ProcitajFajl(const QString &imeFajla)
{
    std::cout << "Citam fajl" << std::endl;
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

    //----------------------UCITAVANJE SVIH PODATAKA O OSOBAMA, BEZ VEZIVANJA---------------------------//
    //int maxSifraOsobe=-1;
    //int maxSifraBraka=-1;
    //int maxSifraDeteta=-1;
    //===========================
   // qint32 sifraKlj;
    //QString ime, prezime;
  //  bool srodnik, nepoznata;
  //  QChar pol;
   // QDate date;
   // ulaz >> sifraKlj;
//    ulaz >> nepoznata;
//    ulaz >> ime;
//    ulaz >> prezime;
//    ulaz >> pol;
//    ulaz >> srodnik;
//    ulaz >> date;
//    ulaz >> date;
//    ulaz >> date;

    //std::cout << sifraKlj << std::endl;// << ime.toStdString() << prezime.toStdString() << pol.toLatin1() << std::endl;

    //=========================

    //ulaz >> *_kljucnaOsoba;

   // int trenInt=0;

   // ulaz >> trenInt;
   // std::cout << "citam " << trenInt << " osoba"<<std::endl;
//    Osoba trenOsoba;
//    Osoba *trenOsobaPokazivac=new Osoba();
//    for(int i=0;i<trenInt;i++)
//    {
//        //std::cout << "citam osobu"<<std::endl;
//        ulaz >> trenOsoba;
//        //trenOsobaPokazivac=new Osoba(trenOsoba);
//        //_sveOsobe.push_back(trenOsobaPokazivac);
//        //if(maxSifraOsobe<trenOsoba.Sifra())maxSifraOsobe=trenOsoba.Sifra();
//       // _indeksIme[trenOsobaPokazivac->Ime()]=std::vector<Osoba*>();
//       // _indeksIme[trenOsobaPokazivac->Ime()].push_back(trenOsobaPokazivac);
//       // _indeksSifraOsobe[trenOsobaPokazivac->Sifra()]=trenOsobaPokazivac;

//    }
    std::cout << "zavrsio sa osobama"<<std::endl;
/*
    //----------------------UCITAVANJE SVIH PODATAKA O OSOBAMA, BEZ VEZIVANJA---------------------------//


    //----------------------UCITAVANJE SVIH PODATAKA O BRAKOVIMA, BEZ VEZIVANJA---------------------------//
    ulaz >> trenInt;
  //  _sveVeze.clear();
    //_sveVeze.resize(trenInt);
    Brak trenBrak;
    Brak *trenBrakPokazivac=nullptr;
    for(int i=0;i<trenInt;i++)
    {
        ulaz >> trenBrak;
        trenBrakPokazivac=new Brak(trenBrak);
     //   _sveVeze.push_back(trenBrakPokazivac);
        if(maxSifraBraka<trenBrak.Sifra())maxSifraBraka=trenBrak.Sifra();
        _indeksSifraVeza[trenBrakPokazivac->Sifra()]=trenBrakPokazivac;
    }
    //----------------------UCITAVANJE SVIH PODATAKA O BRAKOVIMA, BEZ VEZIVANJA---------------------------//


    //----------------------UCITAVANJE SVIH PODATAKA O DECI, BEZ VEZIVANJA---------------------------//
    ulaz >> trenInt;
  //  _svaDeca.clear();
    //_svaDeca.resize(trenInt);
    Dete trenDete;
    Dete *trenDetePokazivac=nullptr;
    for(int i=0;i<trenInt;i++)
    {
        ulaz >> trenDete;
        trenDetePokazivac=new Dete(trenDete);
      //  _svaDeca.push_back(trenDetePokazivac);
        if(maxSifraDeteta<trenDete.Sifra())maxSifraDeteta=trenDete.Sifra();
        _indeksSifraDete[trenDetePokazivac->Sifra()]=trenDetePokazivac;
    }
    //----------------------UCITAVANJE SVIH PODATAKA O DECI, BEZ VEZIVANJA---------------------------//


    //----------------------POSTAVLJANJE STATICKOG PODATKA ZA DODELU SLEDECE SIFRE NA OSNOVU MAKSIMUMA UCITANIH------------------------//
    Osoba::postaviSledecuSifru(maxSifraOsobe+1);
    Brak::postaviSledecuSifru(maxSifraBraka+1);
    Dete::postaviSledecuSifru(maxSifraDeteta+1);
    //----------------------POSTAVLJANJE STATICKOG PODATKA ZA DODELU SLEDECE SIFRE NA OSNOVU MAKSIMUMA UCITANIH------------------------//


    int sifraOsobe=0,sifraPorekla=0,sifraVeze=0,velicina=0;
    trenOsobaPokazivac=nullptr;


    //-----------------------------POVEZIVANJE OSOBA-----------------------------------//
    do
    {
        ulaz  >> sifraOsobe;
        if(sifraOsobe==-1)continue;
        if(sifraOsobe==-100)break;
        trenOsobaPokazivac=NadjiOsobuSifrom(sifraOsobe);
        ulaz >> sifraPorekla;
        if(sifraPorekla!=-1)trenOsobaPokazivac->PostaviPoreklo(NadjiDeteSifrom(sifraPorekla));
        ulaz >> velicina;
        trenOsobaPokazivac->SpisakVeza().clear();//.resize(velicina);
        for(int i=0;i<velicina;i++){
            ulaz >> sifraVeze;
            if(sifraVeze!=-1)
                trenOsobaPokazivac->DodajVezu(NadjiBrakSifrom(sifraVeze));
        }
    }
    while(sifraOsobe != -100);

    //-----------------------------POVEZIVANJE OSOBA-----------------------------------//


    //-----------------------------POVEZIVANJE BRAKOVA-----------------------------------//
    int sifraDeteta=0;

    trenBrakPokazivac=nullptr;
    do
    {
        ulaz  >> sifraVeze;
        if(sifraVeze==-2)continue;
        if(sifraVeze==-200)break;
        trenBrakPokazivac=NadjiBrakSifrom(sifraVeze);
        ulaz >> sifraOsobe;
        //if(sifraOsobe!=-1)trenBrakPokazivac->PostaviNasuOsobu(NadjiOsobuSifrom(sifraOsobe));
        //ulaz >> sifraOsobe;
        //if(sifraOsobe!=-1)trenBrakPokazivac->PostaviTudjuOsobu(NadjiOsobuSifrom(sifraOsobe));

        ulaz >> velicina;
        trenBrakPokazivac->SpisakDece().clear();//.resize(velicina);
        for(int i=0;i<velicina;i++){
            ulaz >> sifraDeteta;
            if(sifraDeteta!=-2)
                trenBrakPokazivac->DodajDete(NadjiDeteSifrom(sifraDeteta));
        }
    }
    while(sifraVeze != -200);
    //-----------------------------POVEZIVANJE BRAKOVA-----------------------------------//

    //-----------------------------POVEZIVANJE DECE-----------------------------------//

    trenBrakPokazivac=nullptr;
    do
    {
        ulaz  >> sifraDeteta;
        if(sifraDeteta==-3)continue;
        if(sifraDeteta==-300)break;
        trenDetePokazivac=NadjiDeteSifrom(sifraDeteta);
        ulaz >> sifraOsobe;
        //if(sifraOsobe!=-1)trenDetePokazivac->PostaviPotomka(NadjiOsobuSifrom(sifraOsobe));
        ulaz >> sifraVeze;
        //if(sifraVeze!=-1)trenDetePokazivac->PostaviRoditeljskiOdnos(NadjiBrakSifrom(sifraVeze));

    }
    while(sifraDeteta != -300);
    //-----------------------------POVEZIVANJE DECE-----------------------------------//

*/
    fajl.close();

    //----------------------------Posto se svakako pozivaju destruktori lokalnih promenljivih, moram da im naglasim pre nego sto budu pozvani
    //----------------------------da ne treba da rade nikakvu vrstu razvezivanja, koje postoji u destruktorima!!!
   // //trenDete.PreskociRazvezivanje();
   // trenOsoba.PreskociRazvezivanje();
   // trenBrak.PreskociRazvezivanje();

    return true;
}



bool PorodicnoStablo::IspisiFajl(const QString &imeFajla)//cuvam samo podatke koji su mi potrebni, da bi fajlovi bili manji
{//time gubim na performansama pri ucitavanju, ali posto je cuvanje bitnije od ucitavanja (koje radimo prilicno retko), deluje mi bolje ovako

    std::cout << "Pisem u fajl" << std::endl;
    QFile fajl(imeFajla);
    if (!fajl.open(QIODevice::WriteOnly)) {
        std::cout << "Ne moze da upise u fajl" << std::endl; //bice warning
        return false;
    }
    QDataStream izlaz(&fajl);
    izlaz.setVersion(QDataStream::Qt_4_1);// DA LI OVAJ, ILI NEKI DRUGI?? iskreno pojma nemam u kojem radimo mi zapravo

    izlaz << _kljucnaOsoba;

    //std::cout << "imam osoba " << _indeksSifraOsobe.size() << std::endl;
    izlaz << qint32(_indeksSifraOsobe.size());
    for(auto osoba :_indeksSifraOsobe)
    {
        izlaz<<(*(osoba.second));
    }

    izlaz << qint32(_indeksSifraVeza.size());
    for(auto brak :_indeksSifraVeza)
    {
        izlaz<<(*brak.second);
    }

    izlaz << qint32(_indeksSifraDete.size());
    for(auto dete :_indeksSifraDete)
    {
        izlaz<<(*dete.second);
    }

   // std::vector<Osoba*>::iterator osoba=_sveOsobe.begin();
  //  std::vector<Osoba*>::iterator eo=_sveOsobe.end();

    //std::vector<Brak*>::iterator brak;
   // std::vector<Brak*>::iterator eb;

    //std::vector<Dete*>::iterator dete;
   // std::vector<Dete*>::iterator ed;

//    for(;osoba!=eo;osoba++){

//        if((*osoba)!=nullptr){
//            izlaz << qint32((*osoba)->Sifra());
//            if((*osoba)->Poreklo()==nullptr)
//                izlaz << -1;
//            else
//                izlaz << qint32((*osoba)->Poreklo()->Sifra());

//            izlaz << qint32((*osoba)->SpisakVeza().size());

//            brak= (*osoba)->SpisakVeza().begin();
//            eb=(*osoba)->SpisakVeza().end();
//            for(;brak!=eb;brak++){
//                if((*brak)!=nullptr)
//                    izlaz << qint32((*brak)->Sifra());
//                else
//                    izlaz << -1;
//            }
//        }
//        else
//            izlaz << -1;
//    }

    izlaz << -100;//da bih znao da sam zavrsio sa ucitavanjem, da sledi ucitavanje brakova

//    brak=_sveVeze.begin();
//    eb=_sveVeze.end();
//    for(;brak!=eb;brak++){
//        if((*brak)!=nullptr){
//            izlaz << qint32((*brak)->Sifra());
//            //if((*brak)->NasaOsoba()==nullptr)izlaz << -1;
//            //else izlaz << qint32((*brak)->NasaOsoba()->Sifra());

//            //if((*brak)->TudjaOsoba()==nullptr)izlaz << -1;
//            //else izlaz << qint32((*brak)->TudjaOsoba()->Sifra());

//            izlaz << qint32((*brak)->SpisakDece().size());
//            dete=(*brak)->SpisakDece().begin();
//            ed=(*brak)->SpisakDece().end();

//            for(;dete!=ed;dete++){
//                if((*dete)!=nullptr)
//                    izlaz << qint32((*dete)->Sifra());
//                else izlaz << -2;
//            }
//        }
//        else
//            izlaz << -2;

//    }

//    izlaz << -200;//da bih znao da sam zavrsio sa ucitavanjem, da predjem na ucitavanje dece

//    dete=_svaDeca.begin();
//    ed=_svaDeca.end();
//    for(;dete!=ed;dete++){
//        if((*dete)!=nullptr){
//            //if((*dete)->Potomak()==nullptr)izlaz << -1;
//            //else izlaz << qint32((*dete)->Potomak()->Sifra());

//            //if((*dete)->RoditeljskiOdnos()==nullptr) izlaz << -1;
//            //else izlaz << qint32((*dete)->RoditeljskiOdnos()->Sifra());
//        }
//        else
//            izlaz << -3;
//    }

    izlaz << -300; //da bih konacno zavrsio sa ucitavanjem i otisao kuci svojoj zeni i deci

    fajl.close();
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
}

void PorodicnoStablo::SpaliCeloStablo()
{

/*
    std::vector<Osoba*>::iterator b=_sveOsobe.begin();
    std::vector<Osoba*>::iterator e=_sveOsobe.end();
    for(;b!=e;b++)
    {

        (*b)->RaskiniSveVeze();
        if((*b)->Sifra()== _kljucnaOsoba->Sifra())continue;
        if(!(*b)->VecSeBrisem())
            delete *b;
    }

    std::vector<Dete*>::iterator b1=_svaDeca.begin();
    std::vector<Dete*>::iterator e1=_svaDeca.end();
    for(;b1!=e1;b1++)
    {
        (*b1)->RaskiniSveVeze();
        if(!(*b1)->VecSeBrisem())
            delete *b1;
    }

    std::vector<Brak*>::iterator b2=_sveVeze.begin();
    std::vector<Brak*>::iterator e2=_sveVeze.end();
    for(;b2!=e2;b2++)
    {
        (*b2)->RaskiniSveVeze();
        if(!(*b2)->VecSeBrisem())
            delete *b2;
    }
*/
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



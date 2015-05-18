#include "porodicnostablo.h"
#include <QDataStream>


/*
Osoba _kljucnaOsoba;//osoba cije se porodicno stablo kreira
std::vector<Osoba*> _sveOsobe;//vektor sa pokazivacima na sve osobe u stablu
std::vector<Dete *> _svaDeca;//vektor sa pokazivacima na sve deca relacije u stablu
std::vector<Brak*> _sveVeze;//vektor sa pokazivacima na sve brak relacije u stablu
std::map<std::string, std::vector<Osoba*> > _indeksIme;//mapa koja vezuje parove ime, vektor svih osoba sa tim imenom
std::map<QDate, std::vector<Osoba*> > _indeksRodjenje;//mapa koja vezuje parove datum rodjenja, vektor svih osoba sa tim datumom rodjenja
std::map<int, std::vector<Osoba*> > _indeksRodjendan;//mapa koja vezuje dan [1,366] u godini, sa osobom kojoj je tog rednog dana u godini rodjendan
std::map<short int, Osoba* > _indeksSifraOsobe;//mapa koja vezuje sifru osobe za tu osobu
std::map<short int, Brak* > _indeksSifraVeza;//mapa koja vezuje sifru braka za taj brak
std::map<short int, Dete* > _indeksSifraDete;//mapa koja vezuje sifru deteta za konkretan relacioni objekat dete
*/


PorodicnoStablo::PorodicnoStablo()
    :_kljucnaOsoba()
{
    InicijalizujSveStrukture();
    _sveOsobe.push_back(&_kljucnaOsoba);

    (_indeksSifraOsobe[_kljucnaOsoba.Sifra()])=&_kljucnaOsoba;


}

PorodicnoStablo::PorodicnoStablo(std::string ime, std::string prezime, char pol,  bool krvniSrodnik)
    :_kljucnaOsoba(ime,prezime,pol,krvniSrodnik)
{
    InicijalizujSveStrukture();
    _sveOsobe.push_back(&_kljucnaOsoba);
    _indeksIme[_kljucnaOsoba.Ime()]=std::vector<Osoba*>();
    _indeksIme[_kljucnaOsoba.Ime()].push_back(&_kljucnaOsoba);
    /*  _indeksRodjenje[_kljucnaOsoba.DatumRodjenja()]=std::vector<Osoba*>();
    _indeksRodjenje[_kljucnaOsoba.DatumRodjenja()].push_back(&_kljucnaOsoba);
    _indeksRodjendan[_kljucnaOsoba.DatumRodjenja().daysInYear()]=std::vector<Osoba*>();
    _indeksRodjendan[_kljucnaOsoba.DatumRodjenja().daysInYear()].push_back(&_kljucnaOsoba);*/
    _indeksSifraOsobe[_kljucnaOsoba.Sifra()]=&_kljucnaOsoba;
}

PorodicnoStablo::~PorodicnoStablo()
{
    std::vector<Osoba*>::iterator b=_sveOsobe.begin();
    std::vector<Osoba*>::iterator e=_sveOsobe.end();
    for(;b!=e;b++)
    {
        (*b)->RaskiniSveVeze();
        delete *b;
    }

    std::vector<Dete*>::iterator b1=_svaDeca.begin();
    std::vector<Dete*>::iterator e1=_svaDeca.end();
    for(;b1!=e1;b1++)
    {
        (*b1)->RaskiniSveVeze();
        delete *b1;
    }

    std::vector<Brak*>::iterator b2=_sveVeze.begin();
    std::vector<Brak*>::iterator e2=_sveVeze.end();
    for(;b2!=e2;b2++)
    {
        (*b2)->RaskiniSveVeze();
        delete *b2;
    }
}

Osoba * PorodicnoStablo::KljucnaOsoba()
{
    return &_kljucnaOsoba;
}


//dodaje novu osobu u stablo,ocekuje se da posle poziva sledi i poziv za dodavanje deteta ili braka, da bi stablo bilo povezano u svakom momentu!!!
short int PorodicnoStablo::DodajNNLice()
{
    Osoba *nova=new Osoba();
    _indeksSifraOsobe[nova->Sifra()]=nova;
    _sveOsobe.push_back(nova);
    return nova->Sifra();
}
short int PorodicnoStablo::DodajOsobu(std::string ime, std::string prezime, char pol, bool krvniSrodnik)
{
    Osoba* nova=new Osoba(ime,prezime,pol,krvniSrodnik);
    _sveOsobe.push_back(nova);
    _indeksIme[ime]=std::vector<Osoba*>();
    _indeksIme[ime].push_back(nova);
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
    Dete* novo=new Dete(NadjiOsobuSifrom(sifraOsobe),NadjiBrakSifrom(sifraBraka),trivija);
    _svaDeca.push_back(novo);
    _indeksSifraDete[novo->Sifra()]=novo;
    NadjiOsobuSifrom(sifraOsobe)->PostaviPoreklo(novo);
    NadjiBrakSifrom(sifraBraka)->DodajDete(novo);
    return novo->Sifra();
}

//dodaje relaciju brak izmedju dve osobe date siframa
short int PorodicnoStablo::DodajBrak(short int sifraNaseOsobe, short int sifraTudjeOsobe, std::string trivija)
{
    Brak* novi=new Brak(NadjiOsobuSifrom(sifraNaseOsobe),NadjiOsobuSifrom(sifraTudjeOsobe),trivija);
    _sveVeze.push_back(novi);
    _indeksSifraVeza[novi->Sifra()]=novi;
    NadjiOsobuSifrom(sifraNaseOsobe)->DodajVezu(novi);
    NadjiOsobuSifrom(sifraTudjeOsobe)->DodajVezu(novi);
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
    Osoba *zaBrisanje=_indeksSifraOsobe[sifra];
    delete zaBrisanje;

}

void PorodicnoStablo::UkloniBrakSifrom(const short sifra)
{
    delete NadjiBrakSifrom(sifra);
}

void PorodicnoStablo::UkloniDeteSifrom(const short sifra)
{
    delete NadjiDeteSifrom(sifra);
}

bool PorodicnoStablo::ProcitajFajl(const QString &imeFajla)
{
    //TO DO
    QFile fajl(imeFajla);
    if (!fajl.open(QIODevice::ReadOnly)) {
        std::cout << "Ne moze da iscita fajl" << std::endl; //bice warning
        return false;
    }

    //---BOZIDARE RADI---//


    //---BOZIDARE RADI---//



    fajl.close();
    return true;
}

bool PorodicnoStablo::IspisiFajl(const QString &imeFajla)//cuvam samo podatke koji su mi potrebni, da bi fajlovi bili manji
{//time gubim na performansama pri ucitavanju, ali posto je cuvanje bitnije od ucitavanja (koje radimo prilicno retko), deluje mi bolje ovako
    /*
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Spreadsheet"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_1);
    out << quint32(MagicNumber);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            QString str = formula(row, column);
            if (!str.isEmpty())
                out << quint16(row) << quint16(column) << str;
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
    */
    //TO CHECK
    QFile fajl(imeFajla);
    if (!fajl.open(QIODevice::WriteOnly)) {
        std::cout << "Ne moze da upise u fajl" << std::endl; //bice warning
        return false;
    }

    QDataStream izlaz(&fajl);
    izlaz.setVersion(QDataStream::Qt_4_1);// DA LI OVAJ, ILI NEKI DRUGI?? iskreno pojma nemam u kojem radimo mi zapravo




    izlaz << _kljucnaOsoba;




    izlaz << qint32(_sveOsobe.size());
    for(Osoba* osoba:_sveOsobe)
    {
        izlaz<<(*osoba);
    }



    izlaz << qint32(_sveVeze.size());
    for(Brak* brak:_sveVeze){
        izlaz<<(*brak);
    }



    izlaz << qint32(_svaDeca.size());
    for(Dete* dete:_svaDeca){
        izlaz<<(*dete);
    }

    std::vector<Osoba*>::iterator osoba=_sveOsobe.begin();

    std::vector<Osoba*>::iterator eo=_sveOsobe.end();

    std::vector<Brak*>::iterator brak;
    std::vector<Brak*>::iterator eb;

    std::vector<Dete*>::iterator dete;
    std::vector<Dete*>::iterator ed;

    for(;osoba!=eo;osoba++){
        if((*osoba)->Poreklo()==nullptr)
            izlaz << -1;
        else
            izlaz << qint32((*osoba)->Poreklo()->Sifra());

        izlaz << qint32((*osoba)->SpisakVeza().size());

        brak= (*osoba)->SpisakVeza().begin();
        eb=(*osoba)->SpisakVeza().end();
        for(;brak!=eb;brak++){
            izlaz << qint32((*brak)->Sifra());
        }
    }

    brak=_sveVeze.begin();
    eb=_sveVeze.end();
    for(;brak!=eb;brak++){
        if((*brak)!=nullptr){

            if((*brak)->NasaOsoba()==nullptr)izlaz << -1;
            else izlaz << qint32((*brak)->NasaOsoba()->Sifra());


            if((*brak)->TudjaOsoba()==nullptr)izlaz << -1;
            else izlaz << qint32((*brak)->TudjaOsoba()->Sifra());

            izlaz << qint32((*brak)->SpisakDece().size());
            dete=(*brak)->SpisakDece().begin();
            ed=(*brak)->SpisakDece().end();

            for(;dete!=ed;dete++){
                if((*dete)!=nullptr)
                    izlaz << qint32((*dete)->Sifra());
            }
        }
    }

    dete=_svaDeca.begin();
    ed=_svaDeca.end();

    for(;dete!=ed;dete++){
        if((*dete)!=nullptr){
            if((*dete)->Potomak()==nullptr)izlaz << -1;
            else izlaz << qint32((*dete)->Potomak()->Sifra());

            if((*dete)->RoditeljskiOdnos()==nullptr) izlaz << -1;
            else izlaz << qint32((*dete)->RoditeljskiOdnos()->Sifra());
        }
    }

    fajl.close();
    return true;
}


void PorodicnoStablo::InicijalizujSveStrukture()
{
    _sveOsobe.clear();
    _svaDeca.clear();
    _sveVeze.clear();
    _indeksIme.clear();
    //  _indeksRodjenje.clear();
    //  _indeksRodjendan.clear();
    _indeksSifraDete.clear();
    _indeksSifraOsobe.clear();
    _indeksSifraVeza.clear();
}



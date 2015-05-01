#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "unetiosobu.h"
#include "widgetosoba.h"
#include <QGraphicsScene>
#include <engine/porodicnostablo.h>


GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    sifra1 = -1;
    sifra2 = -1;

    //i ovo cemo menjati, pravi se kad se unese prva osoba
    stablo = new PorodicnoStablo("pera", "detlic", 'm', "12.04.1963.");


    setAcceptDrops(true);
    ui->setupUi(this);
    osobapix=QPixmap(":/images/images/Ellipse-tool-icon.png");

    mzpix=QPixmap(":/images/images/heart.png");

    bspix=QPixmap(":/images/images/children.png");

    rdpix=QPixmap(":/images/images/index.jpeg");


    QToolBar *toolbar= addToolBar("main toolbar");

    tbOsoba=new QToolButton();
    tbOsoba->setIcon(QIcon(osobapix));
    tbOsoba->setToolTip("Uneti novu osobu u porodicno stablo");
    toolbar->addWidget(tbOsoba);
    toolbar->addSeparator();

    grpRelacije = new QButtonGroup(toolbar);
    rbMuzZena = new QRadioButton("Supruznik");
    rbMuzZena->setChecked(true);
    rbBratSestra = new QRadioButton("Brat/Sestra");
    rbRoditelj = new QRadioButton("Roditelj");
    rbDete = new QRadioButton("Dete");

    grpRelacije->addButton(rbMuzZena);
    grpRelacije->addButton(rbBratSestra);
    grpRelacije->addButton(rbRoditelj);
    grpRelacije->addButton(rbDete);


    toolbar->addWidget(rbMuzZena);
    toolbar->addWidget(rbBratSestra);
    toolbar->addWidget(rbRoditelj);
    toolbar->addWidget(rbDete);

    tbMZ=new QToolButton();
    tbMZ->setIcon(QIcon(mzpix));
    //toolbar->addWidget(tbMZ);
    //toolbar->addSeparator();
    tbBS=new QToolButton();
    tbBS->setIcon(QIcon(bspix));
    //toolbar->addWidget(tbBS);
    //toolbar->addSeparator();
    tbRD=new QToolButton();
    tbRD->setIcon(QIcon(rdpix));
    //toolbar->addWidget(tbRD);
    //toolbar->addSeparator();


    // toolbar->addAction(QIcon(osobapix), "Osoba", ui->Stablo,"");
    //toolbar->addAction(QIcon(mzpix), "Supruznici",ui->Stablo,"");
    //toolbar->addAction(QIcon(bspix), "Brat - Sestra",ui->Stablo,"");
    //toolbar->addAction(QIcon(rdpix), "Roditelj - dete",ui->Stablo,"");

    //toolbar->addSeparator();
    scena=new QGraphicsScene();

    ui->Stablo->setScene(scena);


    connect(tbOsoba,SIGNAL(clicked()),this,SLOT(dodajNovuOsobu()));
    connect(tbOsoba,SIGNAL(pressed()),this,SLOT(postavi_na_0()));
    connect(tbMZ,SIGNAL(pressed()),this,SLOT(postavi_na_1()));
    connect(tbBS,SIGNAL(pressed()),this,SLOT(postavi_na_2()));
    connect(tbRD,SIGNAL(pressed()),this,SLOT(postavi_na_3()));

    //connect(tbOsoba,SIGNAL(released()),this,SLOT(napravi_Osobu()));
    //connect(tbMZ,SIGNAL(released()),this,SLOT(poveziMZ()));
    //connect(tbBS,SIGNAL(released()),this,SLOT(poveziBS()));
    //connect(tbRD,SIGNAL(released()),this,SLOT(poveziRD()));
    //toolbar->addSeparator();

}

void GlavniProzor::startDrag()

{
    WidgetDrag* pDrag;
    if(ind == 0){
        pDrag = new WidgetDrag (tbOsoba);
        pDrag->setWidget(tbOsoba);
        pDrag->setPixmap(osobapix);
        }
        else if(ind == 1){
            pDrag = new WidgetDrag (tbMZ);
            pDrag->setWidget(tbMZ);
            pDrag->setPixmap(mzpix);
            }
        else if(ind == 2){
            pDrag = new WidgetDrag (tbBS);
            pDrag->setWidget(tbBS);
            pDrag->setPixmap(bspix);
            }
        else if(ind == 3){
            pDrag = new WidgetDrag (tbRD);
            pDrag->setWidget(tbRD);
            pDrag->setPixmap(rdpix);
            }
    pDrag->exec(Qt::MoveAction);
}

void GlavniProzor::mousePressEvent(QMouseEvent *pe)
{
    if ((pe->buttons() & Qt::LeftButton))
    {

        startDrag();

    }

    QWidget::mousePressEvent(pe);

}

void GlavniProzor::mouseMoveEvent(QMouseEvent *pe)
{
    if ((pe->buttons() & Qt::LeftButton) )
    {
         startDrag();

    }
    QWidget::mouseMoveEvent(pe);
}

void GlavniProzor::dragEnterEvent(QDragEnterEvent* pe)
{
    if (pe->mimeData()->hasFormat(WidgetMimeData::mimeType()))
    {
        pe->acceptProposedAction();
    }
    QWidget::dragEnterEvent(pe);
}
void GlavniProzor::dropEvent(QDropEvent* pe)
{
    const WidgetMimeData* pmmd =
            dynamic_cast<const WidgetMimeData*>(pe->mimeData());
    if (pmmd)
    {
        //QToolButton* pwgt = pmmd->widget();
        //QString str("Widget is dropped\n ObjectName: %l ");
       // scena->addText(str.arg(pwgt->objectName()));
        m_ptDragPos=pe->pos();
        if(ind==0)
            napravi_Osobu();
        else if(ind==1)
            poveziMZ();
        else if (ind==2)
            poveziBS();
        else if(ind==3)
            poveziRD();

    }
}

void GlavniProzor::napravi_Osobu(){


    u.show();
/*
    WidgetOsoba *novaOsoba = new WidgetOsoba(123);
    novaOsoba->postaviImePrezime("Pera Peric");

    scena->addWidget(novaOsoba);*/


/*
    while(u.m_ime==""){
        continue;
    }
    QString Ime(u.m_ime+u.m_prezime);
    QPushButton Pomocno(Ime);

    scena->addWidget(Pomocno);
    */

   //m_osobePoz.push_back(m_ptDragPos,&Pomocno);

}
void GlavniProzor::poveziMZ(){
    if(postavi==0){
        tbRD->setDisabled(true);
        tbBS->setDisabled(true);
        postavi=1;
        m_pomocna=m_ptDragPos;
    }
    else
    {
        tbRD->setDisabled(false);
        tbBS->setDisabled(false);
        postavi=0;
/*
        int x1,x2,y1,y2;
        QPushButton S1,S2;
        for (int i=0;i<m_osobePoz.length();i++){
            if(m_osobePoz[i][0].x()<=m_pomocna.x() && (m_osobePoz[i][0].x()+m_osobePoz[i][1]->width())>=m_pomocna.x() &&
                    m_osobePoz[i][0].y()<=m_pomocna.y() && (m_osobePoz[i][0].y()+m_osobePoz[i][1]->height())>=m_pomocna.y() )
            {
                x1=m_osobePoz[i][0].x()+m_osobePoz[i][1]->width();
                y1= m_osobePoz[i][0].y()+m_osobePoz[i][1]->height();
                S1=m_osobePoz[i][1];
                continue;
            }
            if(m_osobePoz[i][0].x()<=m_ptDragPos.x() && (m_osobePoz[i][0].x()+m_osobePoz[i][1]->width())>=m_ptDragPos.x() &&
                    m_osobePoz[i][0].y()<=m_ptDragPos.y() && (m_osobePoz[i][0].y()+m_osobePoz[i][1]->height())>=m_ptDragPos.y() )
            {
                x2=m_osobePoz[i][0].x()+m_osobePoz[i][1]->width();
                y2= m_osobePoz[i][0].y()+m_osobePoz[i][1]->height();
                S2=m_osobePoz[i][1];
                continue;
            }

        }
        scena->addLine(x1,y1,x2,y2);
        */
        //signaliziram da se uspostavila veza izmedju supruznika

    }
}
void GlavniProzor::poveziBS(){
    if(postavi==0){
        tbMZ->setDisabled(true);
        tbRD->setDisabled(true);
        postavi=1;
        m_pomocna=m_ptDragPos;
    }
    else
    {
        tbRD->setDisabled(false);
        tbMZ->setDisabled(false);
        postavi=0;
        /*
        int x1,x2,y1,y2;
        QPushButton B1,B2;
        for (int i=0;i<m_osobePoz.length();i++){
            if(m_osobePoz[i][0].x()<=m_pomocna.x() && (m_osobePoz[i][0].x()+m_osobePoz[i][1]->width())>=m_pomocna.x() &&
                    m_osobePoz[i][0].y()<=m_pomocna.y() && (m_osobePoz[i][0].y()+m_osobePoz[i][1]->height())>=m_pomocna.y() )
            {
                x1=m_osobePoz[i][0].x()+m_osobePoz[i][1]->width();
                y1= m_osobePoz[i][0].y()+m_osobePoz[i][1]->height();
                B1=m_osobePoz[i][1];
                continue;
            }
            if(m_osobePoz[i][0].x()<=m_ptDragPos.x() && (m_osobePoz[i][0].x()+m_osobePoz[i][1]->width())>=m_ptDragPos.x() &&
                    m_osobePoz[i][0].y()<=m_ptDragPos.y() && (m_osobePoz[i][0].y()+m_osobePoz[i][1]->height())>=m_ptDragPos.y() )
            {
                x2=m_osobePoz[i][0].x()+m_osobePoz[i][1]->width();
                y2= m_osobePoz[i][0].y()+m_osobePoz[i][1]->height();
                B2=m_osobePoz[i][1];
                continue;
            }

        }
        scena->addLine(x1,y1,x2,y2);
        */
        //signaliziram da se uspostavila veza izmedju brace i sestre
    }
}
void GlavniProzor::poveziRD(){
    if(postavi==0){
        tbMZ->setDisabled(true);
        tbBS->setDisabled(true);
        postavi=1;
        m_pomocna=m_ptDragPos;
    }
    else
    {
        tbMZ->setDisabled(false);
        tbBS->setDisabled(false);
        postavi=0;
        /*
        int x1,x2,y1,y2;
        QPushButton R,D;
        for (int i=0;i<m_osobePoz.length();i++){
            if(m_osobePoz[i][0].x()<=m_pomocna.x() && (m_osobePoz[i][0].x()+m_osobePoz[i][1]->width())>=m_pomocna.x() &&
                    m_osobePoz[i][0].y()<=m_pomocna.y() && (m_osobePoz[i][0].y()+m_osobePoz[i][1]->height())>=m_pomocna.y() )
            {
                x1=m_osobePoz[i][0].x()+m_osobePoz[i][1]->width();
                y1= m_osobePoz[i][0].y()+m_osobePoz[i][1]->height();
                R=m_osobePoz[i][1];
                continue;
            }
            if(m_osobePoz[i][0].x()<=m_ptDragPos.x() && (m_osobePoz[i][0].x()+m_osobePoz[i][1]->width())>=m_ptDragPos.x() &&
                    m_osobePoz[i][0].y()<=m_ptDragPos.y() && (m_osobePoz[i][0].y()+m_osobePoz[i][1]->height())>=m_ptDragPos.y() )
            {
                x2=m_osobePoz[i][0].x()+m_osobePoz[i][1]->width();
                y2= m_osobePoz[i][0].y()+m_osobePoz[i][1]->height();
                D=m_osobePoz[i][1];
                continue;
            }

        }
        scena->addLine(x1,y1,x2,y2);
        */
        //signaliziram da se uspostavila veza izmedju roditelja i deteta
    }
}

void GlavniProzor::dodajNovuOsobu()
{
    //u.show();
    //bice na drag&drop, ne ovako, samo da smislim sve do kraja...

    //iscitamo podatke preko onog dijaloga ili kako vec
    // -> ime, prezime, pol, datume

    // short int sifra = stablo->DodajOsobu(...);

    //onda
    //Widget *novaOsoba = new WidgetOsoba(sifra, this)
    //i negde je smestimo xD

    WidgetOsoba *novaOsoba = new WidgetOsoba(1, this);
    novaOsoba->postaviImePrezime("Pera Peric");

    ui->gridStablo->addWidget(novaOsoba,0,0);
    ui->gridStablo->addWidget(new WidgetOsoba(2, this),1,1);
    ui->gridStablo->addWidget(new WidgetOsoba(3, this),3,6);


}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

void GlavniProzor::promeniSelektovanu(short novaSifra)
{
    //if sifra ok...
    selektovana_sifra = novaSifra;
}

void GlavniProzor::popuniInformacije()
{
    if (selektovana_sifra > 0)
        std::cout<<selektovana_sifra<<std::endl;
    else
        //ui->osobaInfo->setText("Ne postoji treba da bude prazno");
        std::cout<<"ne postoji"<<std::endl;

    //Osoba* osoba = stablo->nadjiOsobuPoSifri(selektovana_sifra);
    // if  == nullptr greska
    //inace pisemo
    //QString tmp = QString::fromStdString(osoba->Ime());
    ui->lineImePrezime->setText("nesto");
    ui->lineRodj->setText("nesto drugo");
    ui->lineSmrt->setText("ubicu se ja sad...");

}

void GlavniProzor::postaviSifru1(short nova)
{
    sifra1 = nova;
}

void GlavniProzor::postaviSifru2(short nova)
{
    sifra2 = nova;
}

void GlavniProzor::povezi()
{
    //ovde pozivamo konstruktor za relaciju
    //prema radio buttonu
    //za sifra1, sifra2
    //ako je sve ok
    //iscrtava se i ta relacija

    //short sifraRelacije = stablo->PoveziOsobe(sifra1, sifra2, Odnos::SUPRUZNIK);
}

short int GlavniProzor::selektovana_sifra = -1;



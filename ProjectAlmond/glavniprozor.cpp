#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "unetiosobu.h"
#include <QGraphicsScene>

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
     setAcceptDrops(true);
    ui->setupUi(this);
    osobapix=QPixmap(":/images/images/Ellipse-tool-icon.png");
     mzpix=QPixmap(":/images/images/heart.png");
      bspix=QPixmap(":/images/images/children.png");
       rdpix=QPixmap(":/images/images/index.jpeg");

      QToolBar *toolbar= addToolBar("main toolbar");
     // QToolBar *toolbar= addToolBar("main toolbar");

           tbOsoba=new QToolButton();
          tbOsoba->setIcon(QIcon(osobapix));
            toolbar->addWidget(tbOsoba);
            toolbar->addSeparator();
           tbMZ=new QToolButton();
          tbMZ->setIcon(QIcon(mzpix));
          toolbar->addWidget(tbMZ);
          toolbar->addSeparator();
          tbBS=new QToolButton();
          tbBS->setIcon(QIcon(bspix));
          toolbar->addWidget(tbBS);
          toolbar->addSeparator();
         tbRD=new QToolButton();
          tbRD->setIcon(QIcon(rdpix));
          toolbar->addWidget(tbRD);
          toolbar->addSeparator();


         // toolbar->addAction(QIcon(osobapix), "Osoba", ui->Stablo,"");
          //toolbar->addAction(QIcon(mzpix), "Supruznici",ui->Stablo,"");
          //toolbar->addAction(QIcon(bspix), "Brat - Sestra",ui->Stablo,"");
          //toolbar->addAction(QIcon(rdpix), "Roditelj - dete",ui->Stablo,"");

          //toolbar->addSeparator();
          scena=new QGraphicsScene();

          ui->Stablo->setScene(scena);

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
        QToolButton* pwgt = pmmd->widget();
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
    scena->addEllipse(m_ptDragPos.x(),m_ptDragPos.y(),100,50);

    u.show();

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
        scena->addLine(m_pomocna.x(),m_pomocna.y(),m_ptDragPos.x(),m_ptDragPos.y());
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
        scena->addLine(m_pomocna.x(),m_pomocna.y(),m_ptDragPos.x(),m_ptDragPos.y());
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
        scena->addLine(m_pomocna.x(),m_pomocna.y(),m_ptDragPos.x(),m_ptDragPos.y());
    }
}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

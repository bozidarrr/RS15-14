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
    QPixmap osobapix(":/images/images/Ellipse-tool-icon.png");
      QPixmap mzpix(":/images/images/heart.png");
      QPixmap bspix(":/images/images/children.png");
       QPixmap rdpix(":/images/images/index.jpeg");

      QToolBar *toolbar= addToolBar("main toolbar");
     // QToolBar *toolbar= addToolBar("main toolbar");
           toolbar->addSeparator();
           tbOsoba=new QToolButton();
          tbOsoba->setIcon(QIcon(osobapix));
            toolbar->addWidget(tbOsoba);
           tbMZ=new QToolButton();
          tbMZ->setIcon(QIcon(mzpix));
          toolbar->addWidget(tbMZ);
          tbBS=new QToolButton();
          tbBS->setIcon(QIcon(bspix));
          toolbar->addWidget(tbBS);
         tbRD=new QToolButton();
          tbRD->setIcon(QIcon(rdpix));
          toolbar->addWidget(tbRD);


         // toolbar->addAction(QIcon(osobapix), "Osoba", ui->Stablo,"");
          //toolbar->addAction(QIcon(mzpix), "Supruznici",ui->Stablo,"");
          //toolbar->addAction(QIcon(bspix), "Brat - Sestra",ui->Stablo,"");
          //toolbar->addAction(QIcon(rdpix), "Roditelj - dete",ui->Stablo,"");

          //toolbar->addSeparator();
          scena=new QGraphicsScene();
          ui->Stablo->setScene(scena);


      //toolbar->addSeparator();
}

void GlavniProzor::startDrag(QToolButton * dugme)

{

    WidgetDrag* pDrag = new WidgetDrag (dugme);
    pDrag->setWidget(dugme);
    pDrag->exec(Qt::MoveAction);
}

void GlavniProzor::mousePressEvent(QMouseEvent *pe)
{
    if ((pe->buttons() & Qt::LeftButton)&& pe->pos()==tbOsoba->pos())
    {

        startDrag(tbOsoba);

    }

    if ((pe->buttons() & Qt::LeftButton) && pe->pos()==tbRD->pos())
    {
       // int distance = (pe->pos() - m_ptDragPos).manhattanLength();
        //if (distance >= QApplication::startDragDistance())
            startDrag(tbRD);
    }
    if ((pe->buttons() & Qt::LeftButton) && pe->pos()==tbMZ->pos())
    {
        //int distance = (pe->pos() - m_ptDragPos).manhattanLength();
        //if (distance >= QApplication::startDragDistance())
           startDrag(tbMZ);
    }
    if ((pe->buttons() & Qt::LeftButton) && pe->pos()==tbBS->pos())
    {
        //int distance = (pe->pos() - m_ptDragPos).manhattanLength();
        //if (distance >= QApplication::startDragDistance())
            startDrag(tbBS);
    }

    QWidget::mousePressEvent(pe);

}

void GlavniProzor::mouseMoveEvent(QMouseEvent *pe)
{
    if ((pe->buttons() & Qt::LeftButton) )
    {
        int distance = (pe->pos() - tbOsoba->pos()).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            startDrag(tbOsoba);
    else
    {
         distance = (pe->pos() - tbRD->pos()).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            startDrag(tbRD);
    else{
         distance = (pe->pos() - tbMZ->pos()).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            startDrag(tbMZ);
    else
        distance = (pe->pos() - tbBS->pos()).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            startDrag(tbBS);
    }
        }
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
        QString str("Widget is dropped\n ObjectName:%l");
        scena->addEllipse(pe->pos().x(),pe->pos().y(),20,50);
        scena->addText(str.arg(pwgt->objectName()));
    }
}
GlavniProzor::~GlavniProzor()
{
    delete ui;
}

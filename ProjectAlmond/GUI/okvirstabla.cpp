/*#include "okvirstabla.h"
#include "ui_okvirstabla.h"
#include <QtGui>
#include<iostream>
okvirStabla::okvirStabla(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::okvirStabla),_prviX(-1),_prviY(-1),_drugiX(-1),_drugiY(-1),zaCrtanje()
{
    ui->setupUi(this);

}

okvirStabla::~okvirStabla()
{
    delete ui;
}

void okvirStabla::mousePressEvent(QMouseEvent *event)
{
      std::cout<<"pritisao misa na okvir"<<std::endl;
    if (event->button() == Qt::LeftButton) {
        _prviX=event->pos().x();
        _prviY=event->pos().y();
    }

}

void okvirStabla::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout<<"pustio misa na okvir"<<std::endl;
    if (event->button() == Qt::LeftButton) {

            _drugiX=event->pos().x();
            _drugiY=event->pos().y();
    }
    emit kliknut();
}

void okvirStabla::paintEvent(QPaintEvent *event)
{
    cetka=new QPainter(this);
    cetka->setPen(QPen(Qt::green, 3, Qt::DashLine, Qt::RoundCap));
    cetka->setBrush(QBrush(Qt::green, Qt::SolidPattern));
    for(QLine* l: zaCrtanje){
        cetka->drawLine(*l);
    }
    delete cetka;
}

  void okvirStabla::povuciLiniju(int x1,int y1,int x2, int y2)
  {
      zaCrtanje.push_back(new QLine(x1,y1,x2,y2));
  }

int okvirStabla::X1()
{
    return _prviX;
}
int okvirStabla::X2()
{
    return _drugiX;
}
int okvirStabla::Y1()
{
    return _prviY;
}
int okvirStabla::Y2()
{
    return _drugiY;
}

void okvirStabla::X1(int x1)
{
    _prviX = x1;
}

void okvirStabla::X2(int x2)
{
    _drugiX = x2;
}

void okvirStabla::Y1(int y1)
{
    _prviY = y1;
}

void okvirStabla::Y2(int y2)
{
    _drugiY = y2;
}
*/

#include "okvirstabla.h"
#include "ui_okvirstabla.h"
#include <QtGui>
#include<iostream>
okvirStabla::okvirStabla(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::okvirStabla),_prviX(-1),_prviY(-1),_drugiX(-1),_drugiY(-1)
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

//void okvirStabla::resetujKoordinate()
//{
//    _prviX = -1;
//    _drugiX = -1;
//    _prviY = -1;
//    _drugiY = -1;
//}

//bool okvirStabla::resetovan()
//{
//    return (_prviX == -1 && _prviY == -1 && _drugiX == -1 && _drugiY == -1);
//}

#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H 1

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QToolButton>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "WidgetDrag.h"
namespace Ui {
class GlavniProzor;
}

class GlavniProzor : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlavniProzor(QWidget *parent = 0);
    ~GlavniProzor();


private:
    QPoint m_ptDragPos;
    Ui::GlavniProzor *ui;
    void startDrag(QToolButton * dugme);
    QToolButton * tbOsoba;
       QToolButton * tbBS;
       QToolButton * tbMZ;
       QToolButton * tbRD;
       QGraphicsScene* scena;
       QDrag *drag;
protected:
    virtual void mouseMoveEvent(QMouseEvent* pe);
    virtual void dragEnterEvent(QDragEnterEvent* pe);
    virtual void dropEvent(QDropEvent* pe);
    virtual void mousePressEvent(QMouseEvent *pe);
};

#endif // GLAVNIPROZOR_H

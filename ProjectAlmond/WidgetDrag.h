#ifndef WIDGETDRAG_H
#define WIDGETDRAG_H

#include <QWidget>
#include <QMimeData>
#include <QToolButton>
#include <QDrag>
#include <QLabel>
#include "glavniprozor.h"

class WidgetMimeData : public QMimeData
{
private:
    QToolButton* m_pwgt;
public:
   WidgetMimeData():QMimeData()

    {
    }
    virtual ~WidgetMimeData()
    {
    }
    static QString mimeType ()
    {
        return "application/widget";
    }

    void setWidget (QToolButton* pwgt)
    {
    m_pwgt = pwgt;
    setData(mimeType(), QByteArray());
    }

    QToolButton* widget() const

    {
    return m_pwgt;
    }
signals:

public slots:

};

class WidgetDrag : public QDrag
{
public:
    WidgetDrag (QWidget* pwgtDragSource =0): QDrag (pwgtDragSource)
  {
  }
    void setWidget (QToolButton* pwgt)
{
   WidgetMimeData* pmd = new WidgetMimeData;
   pmd->setWidget(pwgt);
   setMimeData(pmd);
    }

};
#endif // WIDGETDRAG_H

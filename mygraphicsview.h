#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include "graphe.h"


class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

private:
    Graphe* graphe_;
    QGraphicsScene* scene_;

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);

public:
    MyGraphicsView(QGraphicsScene*& scene, QWidget * parent = 0);
    ~MyGraphicsView();

    Graphe* getGraphe(){return graphe_;}

};

#endif

#include "mygraphicsview.h"
#include <iostream>

MyGraphicsView::MyGraphicsView(QGraphicsScene*& scene, QWidget * parent)
    : QGraphicsView(scene, parent), scene_(scene)
{
    graphe_ = new Graphe();
    //if(graphe_->loadAlphaBeta() == -1)
    if(graphe_->loadMatrice() == -1)
        QMessageBox::critical(parent, "ERROR", "Matrice file not found or invalid");
    graphe_->compute(scene);
    setMouseTracking(true);
}

MyGraphicsView::~MyGraphicsView()
{

}


void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    std::vector<Sommet*> vect = graphe_->getVectSommet();
    float x = event->pos().x();
    float y = event->pos().y();
    if(graphe_->getIsDragging() <= 0)
    {
        for(unsigned int i = 0; i < vect.size(); ++i)
        {
            if(sqrt(pow(x - (vect.at(i)->getX() + 0.5 * vect[i]->getRadius()) ,2) +
                pow(y - (vect.at(i)->getY() + 0.5 * vect[i]->getRadius()),2)) <= vect.at(i)->getRadius()*0.5)
            {
                graphe_->setIsDragging(i);
                break;
            }
        }
    }
    graphe_->compute(scene_);
}
void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    graphe_->setIsDragging(-1);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    std::vector<Sommet*> vect = graphe_->getVectSommet();
    if(graphe_->getIsDragging() >= 0)
    {
        float rad = vect[graphe_->getIsDragging()]->getRadius();
        if(!(event->pos().x() > SCENE_SIZE_X - rad * 0.4 || event->pos().x() < rad * 0.5
             || event->pos().y() > SCENE_SIZE_Y - rad * 2.1 || event->pos().y() < rad * 0.5))
        {
            vect[graphe_->getIsDragging()]->setX(event->pos().x() - 0.5 * vect[graphe_->getIsDragging()]->getRadius());
            vect[graphe_->getIsDragging()]->setY(event->pos().y() - 0.5 * vect[graphe_->getIsDragging()]->getRadius());
            scene_->clear();
            graphe_->compute(scene_);
        }
    }
}





#ifndef SOMMET_H
#define SOMMET_H
#include <QtWidgets>
#include <QtGui>
#include "constantes.h"

class Sommet
{
private:
    int id_;
    float x_;
    float y_;
    float radius_;
    QColor color_;

public:
    static int nb_sommet;


    Sommet(float x = DEFAULT_POS_X, float y = DEFAULT_POS_Y, float radius = 25, QColor color = Qt::blue);
    ~Sommet();

    void  draw(QGraphicsScene* scene);

    int getId() const {return id_;}
    float getX() const {return x_;}
    float getY()const {return y_;}
    float getRadius() const {return radius_;}
    QColor getColor() const {return color_;}

    void setId(int id){id_ = id;}
    void setX(float x){x_ = x;}
    void setY(float y){y_ = y;}
    void setRadius(float radius){radius_ = radius;}
    void setColor(QColor color){color_ = color;}


};


#endif // SOMMET_H

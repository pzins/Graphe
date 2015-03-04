#ifndef ARC_H
#define ARC_H
#include "sommet.h"

class Arc
{

private:
    Sommet* origin_;
    Sommet* dest_;
    float width_;
    float cost_;
    QColor color_;


public:
    Arc(Sommet* origin, Sommet* dest, float width, float cost, QColor color);
    ~Arc();

    void draw(QGraphicsScene* scene);

    Sommet* getOrigin(){return origin_;}
    Sommet* getDest(){return dest_;}
    float getWidth(){return width_;}
    float getCost(){return cost_;}
    QColor getColor(){return color_;}

    void setOrigin(Sommet* s){origin_ = s;}
    void setDest(Sommet* s){dest_ = s;}
    void setWidth(float w){width_ = w;}
    void setCost(float cost){cost_ = cost;}
    void setColor(QColor color){color_ = color;}
};

#endif // ARC_H

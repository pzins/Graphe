#include "arc.h"
#include <cmath>


Arc::Arc(Sommet* origin, Sommet* dest, float width, float cost, QColor color):
    origin_(origin), dest_(dest), width_(width), cost_(cost), color_(color)
{

}

Arc::~Arc()
{

}


void  Arc::draw(QGraphicsScene* scene)
{
    QPen pen(color_, width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QLine line(origin_->getX() + origin_->getRadius()*0.5, origin_->getY() + origin_->getRadius()*0.5,
               dest_->getX() + dest_->getRadius()*0.5, dest_->getY() + dest_->getRadius()*0.5);
    scene->addLine(line, pen);

    QGraphicsTextItem * io = new QGraphicsTextItem;

    QVector2D vect(-(dest_->getY() - origin_->getY()),
                                   (dest_->getX() - origin_->getX())); //vect orthogonal
    QPoint pt((origin_->getX() + dest_->getX()) * 0.5,
              (origin_->getY() + dest_->getY()) * 0.5 );

    pt.setX(pt.x() + COEFF_COST_POSITION * vect.x());
    pt.setY(pt.y() + COEFF_COST_POSITION * vect.y());


    QFont font("arial", SIZE_FONT_COST);
    font.setBold(true);

    io->setPos(pt);
    io->setPlainText(QString::number(cost_));
    io->setDefaultTextColor(origin_->getColor());
    io->setFont(font);
    scene->addItem(io);

}



